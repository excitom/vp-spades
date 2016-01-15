#if !defined(AFX_VCTCTL_H__DD74051E_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_)
#define AFX_VCTCTL_H__DD74051E_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VctCtl.h : Declaration of the CVctCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CVctCtrl : See VctCtl.cpp for implementation.

// VP ADDIN
class CObjectBase;
// END VP ADDIN

class CVctCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVctCtrl)

// VP ADDIN
	friend CObjectBase;
private:
	static CObjectBase* m_pObjectComm;
	static long         m_cConnections;
// END VP ADDIN

// Constructor
public:
	CVctCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVctCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnEventAdvise(BOOL bAdvise);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CVctCtrl();

	DECLARE_OLECREATE_EX(CVctCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CVctCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVctCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CVctCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CVctCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CVctCtrl)
	afx_msg void vpEndGame();
	afx_msg void vpEnumMembers(long Current, short Level, long Id, LPCTSTR Name, short Type, long X, long Y);
	afx_msg BSTR vpGetClassID();
	afx_msg void vpGetGameDetails(BSTR FAR* Name, BSTR FAR* Info, BSTR FAR* SeatList, BSTR FAR* CanChangeSeat, BSTR FAR* CanSelectSeat, short FAR* MinParticipants, short FAR* MaxParticipants, BSTR FAR* Avatar);
	afx_msg void vpJoinGroup(long Id, LPCTSTR Name, long X, long Y, long GroupId, LPCTSTR GroupName);
	afx_msg void vpLeaveGroup(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName);
	afx_msg void vpSend(long Id, LPCTSTR Name, short Type, long ToId, short SendType, LPCTSTR Message, BSTR FAR* Data);
	afx_msg void vpSendFromService(long Id, short Type, long SrvSendType, LPCTSTR Message, BSTR FAR* Data, long ReqId);
	afx_msg void vpStartGame(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName, long LeaderId, short Capacity, long Seat);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CVctCtrl)
	void e_DupAvatar(long ParentWnd, long Seat)
		{FireEvent(eventidDupAvatar,EVENT_PARAM(VTS_I4  VTS_I4), ParentWnd, Seat);}
	void e_EnumMembers(long id, short MaxLevel)
		{FireEvent(eventidEnumMembers,EVENT_PARAM(VTS_I4  VTS_I2), id, MaxLevel);}
	void e_GetParentWnd(long FAR* hWnd)
		{FireEvent(eventidGetParentWnd,EVENT_PARAM(VTS_PI4), hWnd);}
	void e_GetPresenceInfo(long id, BSTR FAR* Nickname, BSTR FAR* Fullname, BSTR FAR* Location, BSTR FAR* Email)
		{FireEvent(eventidGetPresenceInfo,EVENT_PARAM(VTS_I4  VTS_PBSTR  VTS_PBSTR  VTS_PBSTR  VTS_PBSTR), id, Nickname, Fullname, Location, Email);}
	void e_LeaveGroup()
		{FireEvent(eventidLeaveGroup,EVENT_PARAM(VTS_NONE));}
	void e_QueryService(long FAR* Id, short FAR* Type)
		{FireEvent(eventidQueryService,EVENT_PARAM(VTS_PI4  VTS_PI2), Id, Type);}
	void e_Send(long Id, short SendType, LPCTSTR Message, BSTR FAR* Data)
		{FireEvent(eventidSend,EVENT_PARAM(VTS_I4  VTS_I2  VTS_BSTR  VTS_PBSTR), Id, SendType, Message, Data);}
	void e_SendToService(long ServiceId, long SrvSendType, LPCTSTR Message, BSTR FAR* Data, long ReqId)
		{FireEvent(eventidSendToService,EVENT_PARAM(VTS_I4  VTS_I4  VTS_BSTR  VTS_PBSTR  VTS_I4), ServiceId, SrvSendType, Message, Data, ReqId);}
	void e_SetAvatarPos(long Seat, short Left, short Top, short Width, short Height)
		{FireEvent(eventidSetAvatarPos,EVENT_PARAM(VTS_I4  VTS_I2  VTS_I2  VTS_I2  VTS_I2), Seat, Left, Top, Width, Height);}
	void e_SetGameWnd(long hWnd)
		{FireEvent(eventidSetGameWnd,EVENT_PARAM(VTS_I4), hWnd);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

//BEGIN_VP
  // Connection point for Vp interface
  class VpConnPt : public CConnectionPoint {};

  BEGIN_CONNECTION_PART(CVctCtrl, VpConnPt)
    virtual void   OnAdvise(BOOL bAdvise);
		virtual REFIID GetIID();
  END_CONNECTION_PART(VpConnPt)

  DECLARE_CONNECTION_MAP()

  static void UpdateVpRegistry(BOOL, CLSID);
//END_VP

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CVctCtrl)
	dispidEndGame = 1L,
	dispidEnumMembers = 2L,
	dispidGetClassID = 3L,
	dispidGetGameDetails = 4L,
	dispidJoinGroup = 5L,
	dispidLeaveGroup = 6L,
	dispidSend = 7L,
	dispidSendFromService = 8L,
	dispidStartGame = 9L,
	eventidDupAvatar = 1L,
	eventidEnumMembers = 2L,
	eventidGetParentWnd = 3L,
	eventidGetPresenceInfo = 4L,
	eventidLeaveGroup = 5L,
	eventidQueryService = 6L,
	eventidSend = 7L,
	eventidSendToService = 8L,
	eventidSetAvatarPos = 9L,
	eventidSetGameWnd = 10L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTCTL_H__DD74051E_69DF_11D6_97C7_00C04F0E8AAD__INCLUDED)
