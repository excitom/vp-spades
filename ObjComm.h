#ifndef __OBJECTCOMM_H__
#define __OBJECTCOMM_H__

#include "vpole.h"

#define CLASS_OBJECT_COMM  CUbqGameCommunication

class CVctCtrl;

class CObjectBase
{
protected:
  CVctCtrl* m_pCtrl;
  IVpComm* m_pVpComm;

public:
  CObjectBase();
  virtual ~CObjectBase();

public:
  void   Advise(CVctCtrl* pCtrl);
  void   Advise(IVpComm* pVpComm);
  void   Unadvise();
  void   VpUnadvise();
  BSTR   DataToBSTR(void* pMsg, long len);
  void*  DataFromBSTR(BSTR bstrData, long& len);
  BOOL   DataToBSTR(BSTR* Data, const char* pMsg, long len);
  BOOL   IsReady();

// Notifications from VP
public:
	// VP notifications
  virtual void vpStartGame(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName, 
                           long LeaderId, short Capacity, long Seat) {}
	virtual void vpEndGame() {}

  // VPKernel(IAPI) notifications
	virtual void vpJoinGroup(long Id, LPCTSTR Name, long X, long Y, 
                           long GroupId, LPCTSTR GroupName) {}
	virtual void vpSend(long Id, LPCTSTR Name, short Type, long ToID, short SendType, 
                      LPCTSTR Message, const void* Data, long len){}
	virtual void vpLeaveGroup(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName) {}

  // EnumMembers request notification
	virtual void vpEnumMembers(long Current, short Level, long Id, 
                             LPCTSTR Name, short Type, long X, long Y) {}
  // Service notifications
	virtual void vpSendFromService(long Id, short Type, long SrvSendType, 
                                 LPCTSTR Message, const void* Data, long len, long ReqId){}

  // Request from VP
  virtual void vpGetGameDetails(CString& Name, CString& Info, CString& SeatList,
                                 CString& CanChangeSeat, CString& CanSelectSeat,
                                 short& MinParticipants, short& MaxParticipants,
                                 char*& pAvatar, long& len) {}

public:
  // Commands & Requests from objects to VP
  short send(long Id, short SendType, LPCTSTR Msg, void* Data, long len);
  short leaveGroup();
  short enumMembers(long Id, short MaxLevel = 1);

  short sendToService(long ServiceId, long SrvSendType,
                      LPCTSTR Message, void* Data, long len, long ReqId);
  short queryService(long& Id, short& Type);
  short getPresenceInfo(long Id, CString& Name, CString& Fullname, 
                        CString& Location, CString& Email);
  CString getPlaceName();

  // VP service methods
  HWND getParentWnd();
  void setGameWnd(HWND hWnd);
  void dupAvatar(HWND ParentWnd, short Seat);
  void setAvatarPos(short Seat, short Left, short Top, short Width, short Height);
};

#endif // __OBJECTCOMM_H__



