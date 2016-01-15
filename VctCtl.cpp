// VctCtl.cpp : Implementation of the CVctCtrl ActiveX Control class.

#include "stdafx.h"
#include "Vct.h"
#include "VctCtl.h"
#include "VctPpg.h"

#include "ObjComm.h"
#include "VctComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CVctCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CVctCtrl, COleControl)
	//{{AFX_MSG_MAP(CVctCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CVctCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CVctCtrl)
	DISP_FUNCTION(CVctCtrl, "EndGame", vpEndGame, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CVctCtrl, "EnumMembers", vpEnumMembers, VT_EMPTY, VTS_I4 VTS_I2 VTS_I4 VTS_BSTR VTS_I2 VTS_I4 VTS_I4)
	DISP_FUNCTION(CVctCtrl, "GetClassID", vpGetClassID, VT_BSTR, VTS_NONE)
	DISP_FUNCTION(CVctCtrl, "GetGameDetails", vpGetGameDetails, VT_EMPTY, VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PI2 VTS_PI2 VTS_PBSTR)
	DISP_FUNCTION(CVctCtrl, "JoinGroup", vpJoinGroup, VT_EMPTY, VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CVctCtrl, "LeaveGroup", vpLeaveGroup, VT_EMPTY, VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CVctCtrl, "Send", vpSend, VT_EMPTY, VTS_I4 VTS_BSTR VTS_I2 VTS_I4 VTS_I2 VTS_BSTR VTS_PBSTR)
	DISP_FUNCTION(CVctCtrl, "SendFromService", vpSendFromService, VT_EMPTY, VTS_I4 VTS_I2 VTS_I4 VTS_BSTR VTS_PBSTR VTS_I4)
	DISP_FUNCTION(CVctCtrl, "StartGame", vpStartGame, VT_EMPTY, VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_I4 VTS_I2 VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CVctCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CVctCtrl, COleControl)
	//{{AFX_EVENT_MAP(CVctCtrl)
	EVENT_CUSTOM("DupAvatar", e_DupAvatar, VTS_I4  VTS_I4)
	EVENT_CUSTOM("EnumMembers", e_EnumMembers, VTS_I4  VTS_I2)
	EVENT_CUSTOM("GetParentWnd", e_GetParentWnd, VTS_PI4)
	EVENT_CUSTOM("GetPresenceInfo", e_GetPresenceInfo, VTS_I4  VTS_PBSTR  VTS_PBSTR  VTS_PBSTR  VTS_PBSTR)
	EVENT_CUSTOM("LeaveGroup", e_LeaveGroup, VTS_NONE)
	EVENT_CUSTOM("QueryService", e_QueryService, VTS_PI4  VTS_PI2)
	EVENT_CUSTOM("Send", e_Send, VTS_I4  VTS_I2  VTS_BSTR  VTS_PBSTR)
	EVENT_CUSTOM("SendToService", e_SendToService, VTS_I4  VTS_I4  VTS_BSTR  VTS_PBSTR  VTS_I4)
	EVENT_CUSTOM("SetAvatarPos", e_SetAvatarPos, VTS_I4  VTS_I2  VTS_I2  VTS_I2  VTS_I2)
	EVENT_CUSTOM("SetGameWnd", e_SetGameWnd, VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CVctCtrl, 1)
	PROPPAGEID(CVctPropPage::guid)
END_PROPPAGEIDS(CVctCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CVctCtrl, "VCT.VctCtrl.1",
	0x9cd39e03, 0x6612, 0x47b5, 0xaa, 0xe2, 0x89, 0xb, 0x5c, 0x95, 0xf4, 0x1b)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CVctCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DVct =
		{ 0x74c96e7b, 0x5049, 0x4b19, { 0xbc, 0x4a, 0x81, 0x5d, 0x80, 0x83, 0x1c, 0x79 } };
const IID BASED_CODE IID_DVctEvents =
		{ 0x730430ff, 0x3ead, 0x41bf, { 0x98, 0xf2, 0xb4, 0x64, 0xd4, 0xc8, 0x22, 0x59 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwVctOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CVctCtrl, IDS_VCT, _dwVctOleMisc)

/////////////////////////////////////////////////////////////////////////////
// Connection point for geting VP interface

const IID BASED_CODE IID_IVpComm =
	  { 0xB196B283, 0xBAB4, 0x101A, { 0xB6, 0x9C, 0x00, 0xAA, 0x00, 0x34, 0x1D, 0x05 } };

CObjectBase* CVctCtrl::m_pObjectComm = NULL; 
long CVctCtrl::m_cConnections = 0; 

BEGIN_CONNECTION_MAP(CVctCtrl, COleControl)
  CONNECTION_PART(CVctCtrl, IID_IVpComm, VpConnPt)
END_CONNECTION_MAP()

void CVctCtrl::XVpConnPt::OnAdvise(BOOL bAdvise){
	if(bAdvise){
		const CPtrArray* pConn = GetConnections();
		ASSERT(pConn);
		ASSERT(pConn->GetSize() == 1);  // only single connection is supported
		IVpComm* pVpComm = (IVpComm*)pConn->GetAt(0);
		CVctCtrl::m_cConnections++;
		if(CVctCtrl::m_pObjectComm == NULL){
			CVctCtrl::m_pObjectComm = new CLASS_OBJECT_COMM();
		}
		CVctCtrl::m_pObjectComm->Advise(pVpComm);
	}else{
		CVctCtrl::m_pObjectComm->VpUnadvise();
		CVctCtrl::m_cConnections--;
		if(CVctCtrl::m_cConnections == 0){
			delete CVctCtrl::m_pObjectComm;
			CVctCtrl::m_pObjectComm = NULL;
		}
	}
}

REFIID CVctCtrl::XVpConnPt::GetIID(){
	return IID_IVpComm;
}

void CVctCtrl::OnEventAdvise( BOOL bAdvise ){
	if(bAdvise){
		CVctCtrl::m_cConnections++;
		if(CVctCtrl::m_pObjectComm == NULL){
			CVctCtrl::m_pObjectComm = new CLASS_OBJECT_COMM();
		}
		CVctCtrl::m_pObjectComm->Advise(this);
	}else{
		CVctCtrl::m_pObjectComm->Unadvise();
		CVctCtrl::m_cConnections--;
		if(CVctCtrl::m_cConnections == 0){
			delete CVctCtrl::m_pObjectComm;
			CVctCtrl::m_pObjectComm = NULL;
		}
	}
}

// Registrating object into Vp entry
void CVctCtrl::UpdateVpRegistry(BOOL bRegister, CLSID clsid)
{
	CString szTitle;
	if(!szTitle.LoadString(IDS_GAME_TITLE) || szTitle.IsEmpty())
		return;
	CString szSubKey = CString(SUBKEY_VPGAME_REG) + "\\" + szTitle;
	if(bRegister){
		BSTR bstrClsid;
		StringFromCLSID(clsid, &bstrClsid);
		CString szClsid(bstrClsid);
		::SysFreeString(bstrClsid);
		HKEY phkEntry;
		LONG result = RegCreateKey(HKEY_CLASSES_ROOT, szSubKey, &phkEntry);
		result = RegSetValue(phkEntry, "", REG_SZ, szClsid, szClsid.GetLength());
		result = RegFlushKey(phkEntry);
		result = RegCloseKey(phkEntry);
	}else{
		LONG result = RegDeleteKey(HKEY_CLASSES_ROOT, szSubKey);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::CVctCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CVctCtrl

BOOL CVctCtrl::CVctCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegInsertable | afxRegApartmentThreading to afxRegInsertable.

	UpdateVpRegistry(bRegister, m_clsid);

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_VCT,
			IDB_VCT,
			afxRegInsertable | afxRegApartmentThreading,
			_dwVctOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::CVctCtrl - Constructor

CVctCtrl::CVctCtrl()
{
	InitializeIIDs(&IID_DVct, &IID_DVctEvents);
	m_bInitialized  = TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::~CVctCtrl - Destructor

CVctCtrl::~CVctCtrl()
{
	ASSERT(m_pObjectComm == NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::OnDraw - Drawing function

void CVctCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::DoPropExchange - Persistence support

void CVctCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::OnResetState - Reset control to default state

void CVctCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl::AboutBox - Display an "About" box to the user

void CVctCtrl::AboutBox()
{
	CDialog dlg(IDD_ABOUTBOX_VCT);
	dlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CVctCtrl message handlers

void CVctCtrl::vpEndGame(){
	if(!m_pObjectComm) return;
	m_pObjectComm->vpEndGame();
}

void CVctCtrl::vpEnumMembers(long Current, short Level, long Id, LPCTSTR Name, short Type, long X, long Y){
	if(!m_pObjectComm) return;
	m_pObjectComm->vpEnumMembers(Current, Level, Id, Name, Type, X, Y);
}

BSTR CVctCtrl::vpGetClassID(){
	CLSID clsid;
	GetClassID(&clsid);
	CString strResult; 
	BSTR bstrClsid = strResult.AllocSysString();
	StringFromCLSID(clsid, &bstrClsid);
	return bstrClsid;
}

void CVctCtrl::vpGetGameDetails(BSTR FAR* Name, BSTR FAR* Info, BSTR FAR* SeatList, BSTR FAR* CanChangeSeat, BSTR FAR* CanSelectSeat, short FAR* MinParticipants, short FAR* MaxParticipants, BSTR FAR* Avatar){
	if(!m_pObjectComm) return;
	CString szName;
	CString szInfo;
	CString szSeatList;
	CString szCanChangeSeat;
	CString szCanSelectSeat;
	long    len = 0;
	char*   pAvatar = NULL;
	m_pObjectComm->vpGetGameDetails(szName, szInfo, szSeatList, szCanChangeSeat, szCanSelectSeat, 
									*MinParticipants, *MaxParticipants, pAvatar, len);
	m_pObjectComm->DataToBSTR(Name, szName, szName.GetLength() + 1);
	m_pObjectComm->DataToBSTR(Info, szInfo, szInfo.GetLength() + 1);
	m_pObjectComm->DataToBSTR(SeatList, szSeatList, szSeatList.GetLength() + 1);
	m_pObjectComm->DataToBSTR(CanChangeSeat, szCanChangeSeat, szCanChangeSeat.GetLength() + 1);
	m_pObjectComm->DataToBSTR(CanSelectSeat, szCanSelectSeat, szCanSelectSeat.GetLength() + 1);
	m_pObjectComm->DataToBSTR(Avatar, pAvatar, len);
}

void CVctCtrl::vpJoinGroup(long Id, LPCTSTR Name, long X, long Y, long GroupId, LPCTSTR GroupName){
	if(!m_pObjectComm) return;
	m_pObjectComm->vpJoinGroup(Id, Name, X, Y, GroupId, GroupName);
}

void CVctCtrl::vpLeaveGroup(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName){
	if(!m_pObjectComm) return;
	m_pObjectComm->vpLeaveGroup(Id, Name, GroupId, GroupName);
}

void CVctCtrl::vpSend(long Id, LPCTSTR Name, short Type, long ToId, short SendType, LPCTSTR Message, BSTR FAR* Data){
	if(!m_pObjectComm) return;
	long len = 0;
	void* pData = m_pObjectComm->DataFromBSTR(*Data, len);
	m_pObjectComm->vpSend(Id, Name, Type, ToId, SendType, Message, pData, len);
	delete pData;
}

void CVctCtrl::vpSendFromService(long Id, short Type, long SrvSendType, LPCTSTR Message, BSTR FAR* Data, long ReqId){
	if(!m_pObjectComm) return;
	long len = 0;
	void* pData = m_pObjectComm->DataFromBSTR(*Data, len);
	m_pObjectComm->vpSendFromService(Id, Type, SrvSendType, Message, pData, len, ReqId) ;
	delete pData;
}

void CVctCtrl::vpStartGame(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName, long LeaderId, short Capacity, long Seat){
	m_pObjectComm->vpStartGame(Id, Name, GroupId, GroupName, LeaderId, Capacity, Seat);
}

