// Game Applet base class

#include "stdafx.h"
#include "GameApp.h"
#include "GameBrd.h"
#include "VctComm.h"
#include "GameImg.h"
#include "picture.h"
//#include <Winsock.h>
#include "vpclbset.h"
#include "ubique.h"
#include "LightNdr.h"

CUbqGameApplet::CUbqGameApplet()
{
  m_pBoard = NULL;
  m_pComm = NULL;
  m_hMenu  = NULL;       //xxx
  m_bNeedDelete = FALSE; //xxx
}


CUbqGameApplet::~CUbqGameApplet()
{
  if(m_hMenu) ::DestroyMenu(m_hMenu); //xxx
}


CUbqGameImage* CUbqGameApplet::GetSynchImageFromFile(const CString& cFileName)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromFile(cFileName);
  return (im);
}

CUbqGameImage* CUbqGameApplet::GetSynchImageFromFile(const CString& cFileName, COLORREF clTransparent)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromFile(cFileName, clTransparent);
  return (im);
}

CUbqGameImage* CUbqGameApplet::GetSynchImageFromResources(const CString& cRCName)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromResources(cRCName);
  return (im);
}

CUbqGameImage* CUbqGameApplet::GetSynchImageFromResources(const CString& cRCName, COLORREF clTransparent)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromResources(cRCName, clTransparent);
  return (im);
}

CUbqGameImage* CUbqGameApplet::GetSynchImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize, COLORREF clTransparent)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromBuffer(lpBuffer, dwSize, clTransparent);
  return (im);
}

CUbqGameImage* CUbqGameApplet::GetSynchImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize)
{
  CUbqGameImage* im = new CUbqGameImage;
  im->LoadImageFromBuffer(lpBuffer, dwSize);
  return (im);
}

void CUbqGameApplet::DrawImage(CUbqGameImage* pImage, CPoint Point, CDC& dc)
{
  if (pImage==NULL)
    return;
  pImage->DrawImage(dc, CRect(Point, CSize(pImage->GetWidth(),pImage->GetHeight())));
}

void CUbqGameApplet::DrawImage(CBitmap* pImage, CPoint Point,CSize Size, CDC& dc)
{
  CDC BoardDC;
  BoardDC.CreateCompatibleDC(&dc);
  CBitmap* oldBoard=BoardDC.SelectObject(pImage);
  dc.BitBlt(Point.x,Point.y,Size.cx,Size.cy,&BoardDC,0,0,SRCCOPY);
  BoardDC.SelectObject(oldBoard);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Communication to Virtual Places
//////////////////////////////////////////////////////////////////////////////////////////

void CUbqGameApplet::OnLeaveGroup(DWORD leaderId, DWORD presenceId)
{
  int xxx=FALSE;
}

void CUbqGameApplet::OnJoinGroup(DWORD presenceId, DWORD slot)
{
}

void CUbqGameApplet::InitInstance(CUbqGameCommunication* pComm, BOOL IsLeader)
{
  m_pComm = pComm;
}

void CUbqGameApplet::ExitInstance()
{
  CServiceMessage* o;

  while (m_vecServiceMessages.GetSize())
  {
    o=(CServiceMessage*)m_vecServiceMessages.GetAt(0);
    m_vecServiceMessages.RemoveAt(0);
    delete(o);
  }
}

void CUbqGameApplet::OnEnumMembers(long nSlot, long lMemberID)
{
}


  //service functions
BOOL CUbqGameApplet::ServiceOpenGame(DWORD GameTypeId,CString& Url, long Version)
{
  CObject* o;

  m_nClubGame=2;

  m_bServiceGameStart=TRUE;
  m_bServiceSignAfterStart=FALSE;
  m_bServiceStartAfterResult=FALSE;

  short Type=CLB_ID;
  m_pComm->queryService(m_nServiceID,Type);
  if (!m_nServiceID)  //no club found !!
  {
    m_nClubGame=0;
    return FALSE;
  }

  while (m_vecServiceMessages.GetSize())
  {
    o=m_vecServiceMessages.GetAt(0);
    m_vecServiceMessages.RemoveAt(0);
    delete(o);
  }

  UbqNdr ndrSend;
  UbqUlong GTI=GameTypeId;
  ndrSend.dump( GTI );
  ndrSend.dump((UbqUlong)Version);

  m_pComm->sendToService(m_nServiceID,CLB_OPEN_GAME,LPCTSTR(Url),
                         (void*)ndrSend.getData(), ndrSend.getLength(),1);

  return TRUE;
}
void CUbqGameApplet::ServiceJoinGame(DWORD Slot,CString& PlayerName)
{
  if (m_nClubGame==0)
    return;

  m_bServiceGameStart=TRUE;

  if (m_nClubGame==1)
  {
    UbqNdr ndrSend;
    ndrSend.dump((UbqUlong)m_nServiceGameID);
    ndrSend.dump((UbqUlong)Slot);
    m_pComm->sendToService(m_nServiceID,CLB_JOIN_GAME,LPCTSTR(PlayerName),
                           (void*)ndrSend.getData(), ndrSend.getLength(),1);
  }
  else
  {
    CServiceMessage* p;

    p=new(CServiceMessage);
    ASSERT(p);
    p->m_sString=PlayerName;
    p->m_nLen=2*sizeof(DWORD);
    p->m_nID=CLB_JOIN_GAME;
    p->m_pData[1]=Slot;
    m_vecServiceMessages.Add(p);
  }
}
void CUbqGameApplet::ServiceStartGame()
{
  if (m_nClubGame==0)
    return;

  if (m_nClubGame==1)
  {
    UbqNdr ndrSend;
    ndrSend.dump((UbqUlong)m_nServiceGameID);
    m_pComm->sendToService(m_nServiceID,CLB_START_GAME,NULL,
                           (void*)ndrSend.getData(), ndrSend.getLength(),1);
  }
  else
  {
    CServiceMessage* p;

    p=new(CServiceMessage);
    ASSERT(p);
    p->m_sString="";
    p->m_nLen=sizeof(DWORD);
    p->m_nID=CLB_START_GAME;
    p->m_pData[0]=m_nServiceGameID;
    m_vecServiceMessages.Add(p);
  }

  if (m_bServiceStartAfterResult)
  {
    m_bServiceStartAfterResult=FALSE;
    m_bServiceGameStart=TRUE;
    //m_nClubGame=2;
  }

}
void CUbqGameApplet::ServiceLeaveGame(DWORD Slot)
{
  if (m_nClubGame==0)
    return;
  if (Slot ==1) //leader
    m_bServiceGameStart=FALSE;

  if (m_nClubGame==1)
  {
    UbqNdr ndrSend;
    ndrSend.dump((UbqUlong)m_nServiceGameID);
    ndrSend.dump((UbqUlong)Slot);
    m_pComm->sendToService(m_nServiceID,CLB_LEAVE_GAME,NULL,
                           (void*)ndrSend.getData(), ndrSend.getLength(),1);
  }
  else
  {
    CServiceMessage* p;

    p=new(CServiceMessage);
    ASSERT(p);
    p->m_sString="";
    p->m_nLen=2*sizeof(DWORD);
    p->m_nID=CLB_LEAVE_GAME;
    p->m_pData[1]=Slot;
    m_vecServiceMessages.Add(p);
  }
}
void CUbqGameApplet::ServiceResultGame(DWORD NumPlayers,DWORD* Results)
{
  if (m_nClubGame==0)
    return;

  //m_bServiceGameStart=FALSE;
  m_bServiceStartAfterResult=TRUE;

  if (m_nClubGame==1)
  {
    UbqNdr ndrSend;

    ndrSend.dump((UbqUlong)m_nServiceGameID);
    ndrSend.dump((UbqUlong)NumPlayers);
    ndrSend.dump((UbqUlong)Results[0]);
    ndrSend.dump((UbqUlong)Results[1]);

    if (NumPlayers>2)
    {
      ndrSend.dump((UbqUlong)Results[2]);
      ndrSend.dump((UbqUlong)Results[3]);
    }
    m_pComm->sendToService(m_nServiceID,CLB_RESULT_GAME,NULL,
                           (void*)ndrSend.getData(), ndrSend.getLength(),1);
  }
  else
  {
    CServiceMessage* p;

    p=new(CServiceMessage);
    ASSERT(p);
    p->m_sString="";
    p->m_nLen=2*sizeof(DWORD);
    p->m_nID=CLB_RESULT_GAME;
    p->m_pData[1]=NumPlayers;
    p->m_pData[2]=Results[0];
    p->m_pData[3]=Results[1];
    if (NumPlayers>2)
    {
      p->m_pData[4]=Results[2];
      p->m_pData[5]=Results[3];
    }
    m_vecServiceMessages.Add(p);
  }

  m_nClubGame=2;  //we need to get new id .....
}

void CUbqGameApplet::SendFromService(long Id, long SrvSendType,const void* Data, long len)
{
  if (m_nClubGame==0)
    return;

  if ((SrvSendType < CLB_OPEN_GAME) || (SrvSendType > CLB_TEXT_MSG))		// tom lang 10/04
	return;

  CServiceMessage* o;

  UbqNdr ndrGet( len, (const char*)Data );
  UbqUlong tmp;
  ndrGet.load( tmp );
  m_nServiceGameID=tmp;
  ndrGet.load( tmp );
  m_nClubGame=tmp;

  if (SrvSendType == CLB_TEXT_MSG) {
	CString textMsg;
	ndrGet.load(textMsg);
	DWORD len = textMsg.GetLength();
	char* b = (char *)malloc(len+sizeof(len));
	*((DWORD*)b) = len;
	memcpy(b+sizeof(len), (const char *)textMsg, len);
	m_pComm->SendGameMessage((unsigned char*)b, len+sizeof(len), MSG_GAME_TEXT_MSG,
       			 	 	 	   m_pComm->GetGameInstance()->GetGroupID());
	free(b);
	return;
  }

  if (m_nClubGame)
  {
    //send the sign game message
    UbqNdr ndrSend;
    ndrSend.dump((UbqUlong)m_nServiceGameID);
    ndrSend.dump((UbqUlong)m_bServiceSignAfterStart);
    m_bServiceSignAfterStart=TRUE;
    m_pComm->sendToService(m_nServiceID,CLB_SIGN_GAME,NULL,
                           (void*)ndrSend.getData(), ndrSend.getLength(),1);

    while (m_vecServiceMessages.GetSize())
    {
      o=(CServiceMessage*)m_vecServiceMessages.GetAt(0);
      m_vecServiceMessages.RemoveAt(0);

      UbqNdr ndrSend;
      ndrSend.dump((UbqUlong)m_nServiceGameID);
      for (int i=1;i<o->m_nLen;i++)

        ndrSend.dump((UbqUlong)o->m_pData[i]);

      m_pComm->sendToService(m_nServiceID,o->m_nID,LPCTSTR(o->m_sString),
                             (void*)ndrSend.getData(), ndrSend.getLength(),1);
      delete(o);
    }
  }
}

void CUbqGameApplet::OnGameTextMsg(CString& msg)
{
	AfxMessageBox(msg);
}