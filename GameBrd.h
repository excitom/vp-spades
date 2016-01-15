// GameBrd.h : header file
//

#ifndef _UBQ_GAME_BOARD_H_
#define _UBQ_GAME_BOARD_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

#define SHOW_ANIMATE           TRUE
#define SHOW_NONE              FALSE
#define MOVE_TO_TOP            TRUE
#define MOVE_NO_Z_ORDER_CHANGE FALSE

#define  MAX_CURSORS 5

#define G_BOARD_WIDTH	500
#define G_BOARD_HEIGHT	320

/////////////////////////////////////////////////////////////////////////////
// CUbqGameBoard window

class CUbqGameBoard : public CWnd
{
  // Construction
public:
	CUbqGameBoard(class CUbqGameApplet* pGameApp, CWnd* pParent, CRect rGame,
    UINT BoardBmpName, CRect rBoard, BOOL bEmphasizeSlots = FALSE,
    BOOL bShowScrollBar = TRUE, BOOL bShowPopupMenu = TRUE);
	virtual ~CUbqGameBoard();

  // Methods
public:
  // Areas handling
	void AddArea(class CUbqGameBoardArea* ar);
	BOOL RemoveArea(int id);
	void RemoveAllAreas();
	class CUbqGameBoardArea* GetArea(CRect rArea);

	// Buttons handling
	void AddButton(class CUbqGameButton* pButton);
	BOOL RemoveButton(int id);
	void RemoveAllButtons();
	class CUbqGameButton* GetButton(CPoint Point);
	class CUbqGameButton* GetButtonByID(int id);
	void SetButtonDisabled(int id);
	void SetButtonEnabled(int id);
  void OnButtonStatusChange();

	// Multiple Images handling
  void AddMultiImage(class CUbqMultImage* pMultiImage);
  void RemoveMultiImage(class CUbqMultImage* pMultiImage);
  void RemoveAllMultiImages();
  void OnMultiImageChange(class CUbqMultImage* pImage);

  // Board handling
	void OnNewGame();
  virtual void DrawBoardAndPieces(CDC& dc, CRect& rcPaint);
	void SetViewPoint(BOOL bFlipV, BOOL bFlipH);
	void Lock(BOOL bIsLocked);
	BOOL IsLocked() { return m_bIsLocked; };

	DWORD GetState(BYTE* buf, DWORD bufLen);
	BOOL  SetState(BYTE* buf, DWORD bufLen);

  // Pieces handling
  void AddPiece(class CUbqGamePiece* pPiece);
	void RemovePiece(int id);
  void RemoveAllPieces();
	void MovePiece(class CUbqGamePiece* piece, CPoint newPoint, BOOL bAnimate, BOOL toTop);
  void RejectMovePiece(class CUbqGamePiece* pPiece, CPoint destPoint);
	class CUbqGamePiece* GetPieceByID(int ID);
	void SetPieceImage(int id,CUbqGameImage* pImage);
  void SetPieceAttribute(CUbqGamePiece* pPiece, int iAttr);
  void DeleteWindow(); //xxx

  // Scrollbar methods and members
private:
  void SetVScrollBar();
  void SetHScrollBar();
  BOOL IsRemovalSuspended();//xxx

private:
  CRect m_RectScroll;
  int VSPos;
  int VSRange;
  int HSPos;
  int HSRange;
  CPoint m_cOffsetPoint;

public:
  void DoLoadCursor(int where,UINT cursor);
  void DoLoadOEMCursor(int where,UINT cursor);
  void ChangeCursor(long cursor);
  void DisableCursor();
  void EnableCursor();

	// Attributes

  //text handling
  void AddText(class CCmgTextArea* pText);
  void RemoveText(int ID);
  void SetText(int ID,CString text);
  void SetTextColors(int ID,COLORREF bg,COLORREF fg);
  CCmgTextArea* GetTextByID(int ID);
  void RemoveRemoveAllTexts();

  // Attributes
private:
  CWnd* m_pParent;
  BOOL m_bEmphasizeSlots;
  BOOL m_bShowScrollBar;
  BOOL m_bShowPopupMenu;
  BOOL m_bSuspend; //xxx

public:
	class CUbqGameApplet* m_pApplet;

  CRect m_rBoard;
  CRect m_rGame;

  CObArray m_vecButtons;
	CObArray m_vecMultipleImages;
	CObArray m_vecPieces;
	CObArray m_vecAreas;
	CObArray m_vecTexts;

	BOOL   m_bViewFlipV;
	BOOL   m_bViewFlipH;
	BOOL   m_bIsLocked;
	BOOL   m_bCaptureSet;

	class CUbqGameBoardArea* m_pDragLastArea;
	class CUbqGameBoardSlot* m_pDragLastSlot;
	class CUbqGameButton* m_pCurrFocusedButton;
	class CUbqGameButton* m_pCurrClickedButton;

	class CUbqGamePiece* m_pDraggedPiece;
  CPoint m_ptDragPieceDest;
  CPoint m_ptRejectPiece;
  class CUbqGamePiece* m_pRejectPiece;

  CBitmap m_cBoardBmp;
  int     m_nBpp;
  UINT    m_nBoardBmpName;

  HCURSOR m_hCursors[MAX_CURSORS];
  HCURSOR m_hCurrentCursor;
  BOOL m_bDisableCursor;
	// Operations
public:
	void Init();
	CRect  GetScrollRect() {return m_RectScroll;}
    CPoint GetOffsetPoint(){return m_cOffsetPoint;}

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUbqGameBoard)
  public:
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
	//}}AFX_VIRTUAL

	// Implementation
  //protected:
public:
	void AdjustPoint(CPoint Point, CPoint& pt);
	void AdjustPoint(CRect Rect, CPoint& pt);
	void PostPaintEvent(CRect& rc);
	BOOL MouseDown(CPoint Point);
	BOOL MouseDrag(CPoint Point);
	BOOL MouseUp(CPoint Point);
  void DoMoveAnimation(CUbqGamePiece* piece, CPoint Point, BOOL bAccept, BOOL bToTop, int iMaxSteps);



	// Generated message map functions
//protected:
public:
	//{{AFX_MSG(CUbqGameBoard)
  afx_msg void OnPaint();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg LRESULT OnMMNotify(WPARAM wParam,LPARAM lParam);
  afx_msg void OnTimer(UINT nIDEvent);
  //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _UBQ_GAME_BOARD_H_

