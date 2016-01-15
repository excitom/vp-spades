#include "stdafx.h"
#include "Vct.h"
#include "VctCtl.h"
#include "objcomm.h"

/************************************************************/
//  CObjectBase base class implementation
/************************************************************/

CObjectBase::CObjectBase(){
	m_pCtrl = NULL;
	m_pVpComm = NULL;
}

CObjectBase::~CObjectBase(){
}

void CObjectBase::Advise(CVctCtrl* pCtrl){
	m_pCtrl = pCtrl;
	ASSERT(m_pCtrl);
}

void CObjectBase::Unadvise(){
	m_pCtrl = NULL;
}

void CObjectBase::Advise(IVpComm* pVpComm){
	if(!m_pVpComm){
		m_pVpComm = pVpComm;
		ASSERT(m_pVpComm);
	}
}

void CObjectBase::VpUnadvise(){
	m_pVpComm = NULL;
}

// Helper function for work with OLESTR

BSTR CObjectBase::DataToBSTR(void* pMsg, long len){
	int iLen = (int)len;
	return SysAllocStringLen(String16((char*)pMsg, iLen), iLen);
}

BOOL CObjectBase::DataToBSTR(BSTR* Data, const char* pMsg, long len){
	int iLen = (int)len;
	BOOL fl = SysReAllocStringLen(Data, String16(pMsg, iLen), iLen);
	return fl;
}

void* CObjectBase::DataFromBSTR(BSTR bstrData, long& len){
	len = SysStringLen(bstrData);
	int iLen = (int)len;
	String8 str8(bstrData, iLen);
	char* pData = new char[iLen];
	memcpy(pData, (char*)str8, iLen);
	return (void*)pData;
}

BOOL CObjectBase::IsReady(){
	return (m_pCtrl || m_pVpComm) ? TRUE : FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Commands & Requests from objects to VP
/////////////////////////////////////////////////////////////////////////////

short CObjectBase::send(long Id, short SendType, LPCTSTR Message, void* Data, long len){
	if(!IsReady()) return -1;
	BSTR bstrData = DataToBSTR(Data, len);
	if(m_pCtrl)
		m_pCtrl->e_Send(Id, SendType, Message, &bstrData);
	else if(m_pVpComm)
		m_pVpComm->Send(Id, SendType, Message, &bstrData);
	::SysFreeString(bstrData);
	return 0;
}

short CObjectBase::leaveGroup(){
	if(!IsReady()) return -1;
	if(m_pCtrl)
		m_pCtrl->e_LeaveGroup();
	else if(m_pVpComm)
		m_pVpComm->LeaveGroup();
	return 0;
}

short CObjectBase::enumMembers(long Id, short MaxLevel /*= 1*/){
	if(!IsReady()) return -1;
	if(m_pCtrl)
		m_pCtrl->e_EnumMembers(Id, MaxLevel);
	else if(m_pVpComm)
		m_pVpComm->EnumMembers(Id, MaxLevel);
	return 0;
}

short CObjectBase::sendToService(long ServiceId, long SrvSendType,
                                 LPCTSTR Message, void* Data, long len, long ReqId){
	if(!IsReady()) return -1;
	BSTR bstrData = DataToBSTR(Data, len);
	if(m_pCtrl)
		m_pCtrl->e_SendToService(ServiceId, SrvSendType, Message, &bstrData, ReqId);
	else if(m_pVpComm)
		m_pVpComm->SendToService(ServiceId, SrvSendType, Message, &bstrData, ReqId);
	::SysFreeString(bstrData);
	return 0;
}

short CObjectBase::queryService(long& Id, short& Type){
	if(!IsReady()) return -1;
	if(m_pCtrl)
		m_pCtrl->e_QueryService(&Id, &Type);
	else if(m_pVpComm)
		m_pVpComm->QueryService(&Id, &Type);
	return 0;
}

short CObjectBase::getPresenceInfo(long Id, CString& Name, CString& Fullname, 
                                   CString& Location, CString& Email){
  if(!IsReady()) return -1;

  // Observation: Could this be any more fucking inefficient?

  char* empty = "";
  BSTR bstrName = DataToBSTR(empty, 1);
  BSTR bstrFullname = DataToBSTR(empty, 1);
  BSTR bstrLocation = DataToBSTR(empty, 1);
  BSTR bstrEmail = DataToBSTR(empty, 1);

  if(m_pCtrl) 
	  m_pCtrl->e_GetPresenceInfo(Id, &bstrName, &bstrFullname, &bstrLocation, &bstrEmail);
  else if(m_pVpComm) 
	  m_pVpComm->GetPresenceInfo(Id, &bstrName, &bstrFullname, &bstrLocation, &bstrEmail);
  
  long len;
  char *p;
  p = (char*)DataFromBSTR(bstrName, len);
  Name = p;
  delete p;
  p = (char*)DataFromBSTR(bstrFullname, len);
  Fullname = p;
  delete p;
  p = (char*)DataFromBSTR(bstrLocation, len);
  Location = p;
  delete p;
  p = (char*)DataFromBSTR(bstrEmail, len);
  Email = p;
  delete p;

  ::SysFreeString(bstrName);
  ::SysFreeString(bstrFullname);
  ::SysFreeString(bstrLocation);
  ::SysFreeString(bstrEmail);

  return 0;
}

CString CObjectBase::getPlaceName(){
	if(!IsReady()) return "";
	CString szURL;
	if(m_pVpComm)
		szURL = m_pVpComm->GetPlaceName();
	return szURL;
}

/////////////////////////////////////////////////////////////////////////////
// VP service methods
/////////////////////////////////////////////////////////////////////////////

HWND CObjectBase::getParentWnd(){
	if(!IsReady()) return NULL;
	long hWnd = 0;
	if(m_pCtrl)
		m_pCtrl->e_GetParentWnd(&hWnd);
	else if(m_pVpComm)
		m_pVpComm->GetParentWnd(&hWnd);
	return hWnd ? (HWND)hWnd : NULL;
}

void CObjectBase::setGameWnd(HWND hWnd){
	if(!IsReady()) return;
	if(m_pCtrl)
		m_pCtrl->e_SetGameWnd((long)((int)hWnd));
	else if(m_pVpComm)
		m_pVpComm->SetGameWnd((long)((int)hWnd));
}

void CObjectBase::dupAvatar(HWND ParentWnd, short nSeat){
	if(!IsReady()) return;
	if(m_pCtrl)
		m_pCtrl->e_DupAvatar((long)((int)ParentWnd), nSeat);
	else if(m_pVpComm)
		m_pVpComm->DupAvatar((long)((int)ParentWnd), nSeat);
}

void CObjectBase::setAvatarPos(short Seat, short Left, short Top, short Width, short Height){
	if(!IsReady()) return;
	if(m_pCtrl)
		m_pCtrl->e_SetAvatarPos(Seat, Left, Top, Width, Height);
	else if(m_pVpComm)
		m_pVpComm->SetAvatarPos(Seat, Left, Top, Width, Height);
}

