#ifndef _UBQ_GAME_APPLET_H_
#define _UBQ_GAME_APPLET_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

// see ImageDef.h for the similar definitions
#ifndef __HUGE
#ifdef WIN32
#define __HUGE
#else
#define __HUGE  huge
#endif // WIN32
#endif // __HUGE

class CServiceMessage : public CObject
{
  public:
    CString m_sString;
    long    m_nLen;
    long    m_nID;
    DWORD   m_pData[6];
};

class CUbqGameBoardArea;
class CUbqGameBoardSlot;
class CUbqGameApplet : public CCmdTarget
{
  // construction
public:
  CUbqGameApplet();
  virtual ~CUbqGameApplet();

  // methods
public:
  class CUbqGameImage* GetSynchImageFromFile(const CString& cFileName);
  class CUbqGameImage* GetSynchImageFromFile(const CString& cFileName, COLORREF clTransparent);
  class CUbqGameImage* GetSynchImageFromResources(const CString& cRCName);
	class CUbqGameImage* GetSynchImageFromResources(const CString& cRCName, COLORREF clTransparent);
	class CUbqGameImage* GetSynchImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize, COLORREF clTransparent);
  class CUbqGameImage* GetSynchImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize);

  void DrawImage(class CUbqGameImage* pImage, CPoint Point, CDC& dc);
  void DrawImage(CBitmap* pImage, CPoint Point, CSize Size, CDC& dc);

  // Mouse handling
  virtual void OnMouseMove			(CPoint Point) {}
  virtual void OnLButtonDown		(CPoint Point) {}
  virtual void OnRButtonDown     	(CPoint Point) {}
  virtual void OnLButtonUp   		(CPoint Point) {}
  virtual void OnRButtonUp      	(CPoint Point) {}

  virtual void InitInstance(class CUbqGameCommunication* pComm, BOOL IsLeader);
  virtual void ExitInstance();

  // Communication messages handler
  virtual void OnGameMessage(BYTE* byData, DWORD dwLen, DWORD dwMsgID, DWORD dwSenderID) {}

  virtual void  OnNewGame() {}
  class   CUbqGameBoard*  GetGameBoard() { return m_pBoard;}
  virtual void  OnButtonClicked(int btnID) {}

  virtual void OnGameTextMsg(CString& msg);
  
#define ROBOT_CAPABLE 0


  // NEW GAME MSGs
  virtual void OnNewGameRequest(DWORD dwUserID) {}
  virtual void OnNewGameReject() {}
  virtual void OnNewGameDispatch(BYTE* byData, DWORD dwLen) {}
  // STATE MSGs
  virtual void OnStateRequest(DWORD dwUserID, DWORD version) {}
  virtual void OnStateDispatch(BYTE* byData, DWORD dwLen) {}
  // PIECE DRAGGING-MOVING MSGs
  // callbacks upon board changes
  virtual BOOL OnPieceMouseDown(class CUbqGamePiece* Piece, CPoint Point) { return TRUE;}
  virtual BOOL OnPieceRMouseDown(CUbqGamePiece* Piece, CPoint Point) { return TRUE;}
  virtual BOOL OnPieceDoubleClick(CUbqGamePiece* Piece, CPoint Point) { return TRUE;}
  virtual BOOL OnPieceDuringDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point) { return TRUE;}
  virtual BOOL OnPieceEndDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point) { return TRUE;}

  virtual void OnMovePieceDispatch(BYTE* byData, DWORD dwLen) {}
  virtual void OnMovePieceRequest(DWORD dwUserID, BYTE* byData, DWORD dwLen) {}
  virtual void OnMovePieceReject(BYTE* byData, DWORD dwLen) {}

  virtual void OnLeaveGroup(DWORD leaderId, DWORD presenceId);
  virtual void OnJoinGroup(DWORD presenceId, DWORD SlotId);
  virtual void OnEnumMembers(long nSlot, long lMemberID);


  virtual void LoadMenu(CPoint point) {}

  virtual LPBYTE GetGameGroupGifFromResources(DWORD& dwLength) { return NULL;}
  virtual LPBYTE GetGameGroupSlotList() { return NULL;}

  virtual BOOL IsRemovalSuspended() { return m_bNeedDelete; }//xxx - start
  virtual void SuspendRemoval()     { m_bNeedDelete = TRUE; }
  virtual BOOL IsOpenMenu() {return ( m_hMenu!=NULL); }      //xxx - end

  virtual LRESULT OnMMNotify(WPARAM wParam,LPARAM lParam) {return 0;}
  virtual void OnTimer() {}
  virtual void OnSize() {}


  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUbqGameApplet)
  public:
  //virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	//}}AFX_VIRTUAL

//protected:
  //DECLARE_MESSAGE_MAP() // base class - no {{ }} macros

  // members
//protected:
  class CUbqGameCommunication* m_pComm;
  class CUbqGameBoard* m_pBoard;
  HMENU   m_hMenu;      //xxx
  BOOL    m_bNeedDelete;//xxx


  //service veriables
  long      m_nServiceGameID;
  long      m_nServiceID;
  int       m_nClubGame; // 0-no 1 yes 2 unknown
  BOOL      m_bServiceGameStart;
  BOOL      m_bServiceStartAfterResult;
  BOOL      m_bServiceSignAfterStart;
  CObArray  m_vecServiceMessages;

  //service functions
  BOOL ServiceOpenGame(DWORD GameTypeId,CString& Url, long Version);
  void ServiceJoinGame(DWORD Slot,CString& PlayerName);
  void ServiceStartGame();
  void ServiceLeaveGame(DWORD Slot);
  void ServiceResultGame(DWORD NumPlayers,DWORD* Results);
  void SendFromService(long Id, long SrvSendType,const void* Data, long len);
};

extern CUbqGameApplet* GetApplet();

#endif // _UBQ_GAME_APPLET_H_
