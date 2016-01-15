// GameBrd.cpp : implementation file
//

#include "stdafx.h"
#include "GameImg.h"
#include "GamePce.h"
#include "GameSlot.h"
#include "GameArea.h"
#include "GameBrd.h"
#include "GameApp.h"
#include "GameMIm.h"
#include "GameBtn.h"
#include "GameText.h"
#include "VctComm.h" // GetState needs some of the defines there
#include "Picture.h"
//#include <Winsock.h>
#include <mmsystem.h>
#include "resource.h"
#include "canim.h"
#include "bmp.h"

// ScrollBar stuff
#ifdef WIN32
SCROLLINFO HSi;
SCROLLINFO VSi;
#endif // WIN32

BOOL IsWin95()
{
#ifdef WIN32
  return TRUE;
#else
  return (HIBYTE(LOWORD(GetVersion())) == 95);
#endif // WIN32
}

#ifdef WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif //WIN32

/////////////////////////////////////////////////////////////////////////////
// CUbqGameBoard

BEGIN_MESSAGE_MAP(CUbqGameBoard, CWnd)
  //{{AFX_MSG_MAP(CUbqGameBoard)
  ON_WM_PAINT()
  ON_WM_LBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  ON_WM_HSCROLL()
  ON_WM_VSCROLL()
  ON_WM_SIZE()
  ON_WM_LBUTTONDBLCLK()
  ON_WM_RBUTTONUP()
  ON_MESSAGE(MM_MCINOTIFY,OnMMNotify)
  ON_WM_TIMER()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CUbqGameBoard::CUbqGameBoard(class CUbqGameApplet* pGameApp, CWnd* pParent, CRect rGame,
                             UINT BoardBmpName, CRect rBoard, BOOL bEmphSlts,
                             BOOL bShowScrollBar, BOOL bShowPopupMenu)
{
  m_pApplet = pGameApp;

  m_rGame   = rGame;
  m_rBoard  = rBoard;

  m_bSuspend            = FALSE; //xxx
  m_bIsLocked           = FALSE;

  m_pDraggedPiece       = NULL;
  m_pRejectPiece        = NULL;
  m_pDragLastArea       = NULL;
  m_pDragLastSlot       = NULL;
  m_pCurrFocusedButton  = NULL;
  m_pCurrClickedButton  = NULL;
  m_bCaptureSet = FALSE;
  m_bEmphasizeSlots = bEmphSlts;
  m_bShowScrollBar = bShowScrollBar;
  m_bShowPopupMenu = bShowPopupMenu;

  #ifndef WIN32
  #define WS_EX_TOOLWINDOW 0
  #endif
  CString strClassName = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, LoadCursor(NULL,IDC_ARROW),
                                             (HBRUSH)GetStockObject(LTGRAY_BRUSH));

  if (!strClassName.IsEmpty())
  {
    m_pParent = pParent;

    CreateEx(WS_EX_TOOLWINDOW, strClassName, "GameBoard", WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, m_rGame.left, m_rGame.top, m_rGame.Width(), m_rGame.Height(),
        m_pParent->m_hWnd, NULL);
  }

  m_bViewFlipV = m_bViewFlipH = FALSE;
  // ScrollBar stuff
  m_RectScroll.SetRectEmpty();

  for (int i=0;i<MAX_CURSORS;i++)
    m_hCursors[i]=NULL;

  m_bDisableCursor=FALSE;

  CBmp::Init();
  m_nBoardBmpName=BoardBmpName;
  m_nBpp=CBmp::ReadBmp(&m_cBoardBmp,m_nBoardBmpName,this);
}

CUbqGameBoard::~CUbqGameBoard()
{
  RemoveAllPieces();
  RemoveAllAreas();
  RemoveAllMultiImages();
  RemoveAllButtons();
  RemoveRemoveAllTexts();

  m_cBoardBmp.DeleteObject();

  CBmp::UnInit();
  m_bSuspend = TRUE;
}

void CUbqGameBoard::Init()
{
  PostPaintEvent(m_rGame);
}

void CUbqGameBoard::Lock(BOOL isLocked)
{
  m_bIsLocked = isLocked;
}


  /**
  * Move a piece on the board
  * @param piece The game piece that should be moved.
  * @param newX The new board X position
  * @param newY The new board Y position
  * @param Indicate if you want a line connecting the old position and
  * the new position flashing briefly before the piece is moved. Select one
  * of the following values:
  * <pre>
  *   SHOW_ANIMATE  To show the animated move of the piece
  *   SHOW_NONE     Not to show the connecting line
  * </pre>
  * @param toTop Indicates if you want the piece Z order to be changed.
  * Select one of the following values:
  * <pre>
  *   MOVE_TO_TOP             To move the piece to the top of the Z order
  *   MOVE_NO_Z_ORDER_CHANGE  No change in the Z order
  * </pre>
  */
void CUbqGameBoard::MovePiece(CUbqGamePiece* piece, CPoint NewPoint, BOOL bAnimate, BOOL bToTop)
{
  int iMaxSteps;

  if (!bAnimate)
    iMaxSteps = 1;
  else
    iMaxSteps = IsWin95() ? 50 : 5;

  DoMoveAnimation(piece, NewPoint, TRUE, bToTop, iMaxSteps);
}

void CUbqGameBoard::RejectMovePiece(CUbqGamePiece* piece, CPoint DestPoint)
{
  DWORD ver = GetVersion();
  int iMaxSteps = IsWin95() ? 50 : 5;

  DoMoveAnimation(piece, DestPoint, FALSE, FALSE, iMaxSteps);
}


void CUbqGameBoard::DoMoveAnimation(CUbqGamePiece* piece, CPoint Point, BOOL bAccept, BOOL bToTop, int iMaxSteps)
{
  CObject* o;
  CUbqGamePiece* p;
  CPoint ap;

  if (iMaxSteps <= 0)
    iMaxSteps = 10;

  int size = m_vecPieces.GetSize();
  for (int i=0; i<size; i++)
  {
    o = m_vecPieces.GetAt(i);
    p = (CUbqGamePiece*) o;
    if (p == piece)
    {
      if (p == m_pDraggedPiece)  // being currently dragged, so release drag
      {
        Point = CPoint(m_pDraggedPiece->m_rArea.TopLeft());
        CSize Size = m_pDraggedPiece->m_rArea.Size();
        CRect Rect = m_pDraggedPiece->m_rArea;

        AdjustPoint(CRect(m_ptDragPieceDest, Size), ap);
        //m_pDraggedPiece = NULL;    // release my piece (My operation is ignored)
        PostPaintEvent(CRect(ap, Size));
        AdjustPoint(Rect, ap);
        PostPaintEvent(CRect(ap, Size));
      }

      CPoint CurrPoint, NextPoint, StartPoint, EndPoint;

      float dx, dy;

      if (bAccept) // accept move from piece current to (x,y)
      {
        StartPoint = p->m_rArea.TopLeft();
        EndPoint = Point;
      }
      else  // Reject
      {
        StartPoint = Point;
        EndPoint = p->m_rArea.TopLeft();
        m_pRejectPiece = p;
      }

      int iSteps;
      // make steps proportional to distance
      CPoint DiffPoint = CPoint(abs(EndPoint.x-StartPoint.x), abs(EndPoint.y-StartPoint.y));

      int d = DiffPoint.x+DiffPoint.y;
      iSteps = d / 5;
      if (iSteps > iMaxSteps) iSteps = iMaxSteps;
      if (iSteps < 1) iSteps = 1;

      dx = (float)(EndPoint.x-StartPoint.x) / (float)iSteps;
      dy = (float)(EndPoint.y-StartPoint.y) / (float)iSteps;

      CurrPoint = StartPoint;

      for (int s = (bAccept ? 1 : 0); s <= iSteps; s++)  // if reject - start from actual end point
      {
        if (s == iSteps)  // make sure last move is to exact point, no truncation
          NextPoint = EndPoint;
        else
          NextPoint = CPoint((int)((float)StartPoint.x+(dx*s)), (int)((float)StartPoint.y+(dy*s)));

        if (bAccept)
        {
          p->m_rArea.OffsetRect(NextPoint-p->m_rArea.TopLeft());
          if (bToTop && s==1)           // do to-top only on first section
          {
            m_vecPieces.RemoveAt(i);
            m_vecPieces.Add(p);        // last element is on the top of the Z order
          }
        }
        else // Reject
          m_ptRejectPiece = NextPoint;

        // destination point
        AdjustPoint(CRect(NextPoint, p->m_rArea.Size()), ap);
        CRect r1(ap + CSize(-1,-1), p->m_rArea.Size()+CSize(1,1));
        // source point
        AdjustPoint(CRect(CurrPoint, p->m_rArea.Size()), ap);
        CRect r2(ap + CSize(-1,-1), p->m_rArea.Size()+CSize(1,1));
        r1.UnionRect(r1,r2);
        PostPaintEvent(r1);
        CurrPoint = NextPoint;
      }

      if (!bAccept)  // remove last frame of rejection picture
      {
        m_pRejectPiece = NULL;
        AdjustPoint(CRect(CurrPoint, p->m_rArea.Size()), ap);
        CRect r(ap + CSize(-1,-1), p->m_rArea.Size()+CSize(1,1));
        PostPaintEvent(r);
      }

      break;
    }
  }
}

  /**
  * Find a game piece
  * @param ID The piece ID to find.
  *   The method finds the first piece that has the specified ID.
  * @return The requested piece (null if not found)
  */
CUbqGamePiece* CUbqGameBoard::GetPieceByID(int ID)
{
  CObject* o = NULL;
  CUbqGamePiece* p = NULL;
  int size = m_vecPieces.GetSize();

  for (int i=0; i<size; i++)
  {
    o = m_vecPieces.GetAt(i);
    p = (CUbqGamePiece*) o;
    if (ID == p->id)
      return p;
  }

  return NULL;
}

void CUbqGameBoard::RemovePiece(int id)
{
  CUbqGamePiece* piece = GetPieceByID(id);
  CObject* o;
  CUbqGamePiece* p;

  int size = m_vecPieces.GetSize();
  for (int i=0; i<size; i++)
  {
    o = m_vecPieces.GetAt(i);
    p = (CUbqGamePiece*) o;
    if (p == piece)
    {
      m_vecPieces.RemoveAt(i);

      CPoint pa;
      AdjustPoint(p->m_rArea, pa);
      PostPaintEvent(CRect(pa, p->m_rArea.Size()));
      delete p;
      return;
    }
  }
}

//
// adjust a point from absolute position to the view-point position,
// and the other way around
//
void CUbqGameBoard::AdjustPoint(CPoint Point, CPoint& pt)
{
  AdjustPoint(CRect(Point, CSize(0,0)), pt);
}

void CUbqGameBoard::AdjustPoint(CRect Rect, CPoint& pt)
{
  int x = Rect.left;
  int y = Rect.top;

  if (m_bViewFlipH)
    x = m_rBoard.right - (x - m_rBoard.left) - Rect.Width();

  if (m_bViewFlipV)
    y = m_rBoard.bottom - (y - m_rBoard.top) - Rect.Height();

  pt = CPoint(x, y);
}

void CUbqGameBoard::SetViewPoint(BOOL bFlipV, BOOL bFlipH)
{
  m_bViewFlipV = bFlipV;
  m_bViewFlipH = bFlipH;
  PostPaintEvent(m_rBoard);// Invalidate();
}

void CUbqGameBoard::PostPaintEvent(CRect& rc)
{
  // rect in the board coordinates
  CRect Rect(rc);
  // rect in the client area coordinates
  Rect.OffsetRect(m_RectScroll.TopLeft());
  Rect.OffsetRect(m_cOffsetPoint);
  InvalidateRect(Rect, FALSE);
  //UpdateWindow();
}

// We get an absolute coordinates.
void CUbqGameBoard::DrawBoardAndPieces(CDC& dc, CRect& rcPaint)
{
  CDC* pDC = (CDC*) &dc;
  CDC dcBuf;

  dcBuf.CreateCompatibleDC(pDC);
  CBitmap bmBuf;
  bmBuf.CreateCompatibleBitmap(pDC, rcPaint.Width(), rcPaint.Height());
  CBitmap* bmOld = (CBitmap*) dcBuf.SelectObject(&bmBuf);

  rcPaint.OffsetRect(-m_cOffsetPoint);

  m_pApplet->DrawImage(&m_cBoardBmp,-rcPaint.TopLeft(),/*rcPaint.Size()*/CSize(G_BOARD_WIDTH,G_BOARD_HEIGHT), dcBuf);

  CUbqGamePiece* p;
  CObject* o;

  // Draw all pieces
  int size = m_vecPieces.GetSize();
  for (int i = 0; i < size; i++)  // bottom to top to preserve Z order
  {
    o = m_vecPieces.GetAt(i);
    p = (CUbqGamePiece*) o;

    if ((p->GetAttribute() & PA_INVISIBLE) == 0 && ( p != m_pDraggedPiece ))
    {
      CPoint ap;
      AdjustPoint(p->m_rArea, ap);
      CRect r1(ap, p->m_rArea.Size());
      if (r1.IntersectRect(r1, rcPaint)) // intersection is not empty
        m_pApplet->DrawImage(p->m_pImage, CPoint(CPoint(ap.x, ap.y) - rcPaint.TopLeft()), dcBuf);
    }
  }


  // draw all buttons and multiple-images
  size = m_vecMultipleImages.GetSize();
  for (i = 0; i < size; i++)  // list of buttons to be redrawn
  {
    CUbqMultImage* m = (CUbqMultImage*)(m_vecMultipleImages.GetAt(i));
    CRect r1(m->m_rArea);
    if (r1.IntersectRect(r1, rcPaint))  // intersection is not empty
      m_pApplet->DrawImage(m->GetCurrImage(), CPoint(m->m_rArea.TopLeft()- rcPaint.TopLeft()), dcBuf);
  }


  // Circle around dragged piece - destination
  if (m_pDraggedPiece != NULL)
  {
    CPoint ap;
    AdjustPoint(CRect(m_ptDragPieceDest, m_pDraggedPiece->m_rArea.Size()), ap);
    CRect r1(ap, m_pDraggedPiece->m_rArea.Size());
    CRect rtemp;
    if (rtemp.IntersectRect(r1,rcPaint))  // intersection is not empty
    {
      if (m_bEmphasizeSlots)
      {
        r1.OffsetRect(-rcPaint.left, -rcPaint.top);

#ifndef WIN32
        // Draw a 3-dimentional rectangle.
        CPen white_pen(PS_SOLID, 1, GetSysColor(COLOR_BTNHIGHLIGHT)); //sari
        CPen* pOldPen = dcBuf.SelectObject(&white_pen);
        dcBuf.MoveTo(r1.right-1, r1.top);
        dcBuf.LineTo(r1.left, r1.top);
        dcBuf.LineTo(r1.left, r1.bottom-1);
        dcBuf.SelectStockObject(BLACK_PEN);
        dcBuf.MoveTo(r1.right-1, r1.top);
        dcBuf.LineTo(r1.right-1, r1.bottom-1);
        dcBuf.LineTo(r1.left , r1.bottom-1);
        CPen grey_pen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
        dcBuf.SelectObject(&grey_pen);
        dcBuf.MoveTo(r1.right - 2, r1.top + 1);
        dcBuf.LineTo(r1.right - 2, r1.bottom - 2);
        dcBuf.LineTo(r1.left + 1, r1.bottom - 2);
        dcBuf.SelectObject(pOldPen);
#else
        dcBuf.Draw3dRect(r1, RGB(0,0,0), RGB(255,255,255));        //sari
#endif
      }
      else
      {
        r1.OffsetRect(-rcPaint.left, -rcPaint.top);
        dcBuf.SelectStockObject(WHITE_PEN);
        dcBuf.SelectStockObject(NULL_BRUSH);

	    switch (m_pDraggedPiece->m_nShape)
	    {
	      case SHAPE_RECT:
               dcBuf.Rectangle(r1);
	    	   break;
	      case SHAPE_OVAL:
               dcBuf.Ellipse(r1);
	    	   break;
		  case SHAPE_PIECE:
	           m_pApplet->DrawImage(m_pDraggedPiece->m_pImage,r1.TopLeft(), dcBuf);
	    	   break;
        }
      }
    }
    // Mark the piece that is being dragged - source
    AdjustPoint(m_pDraggedPiece->m_rArea, ap);
    CRect r2 (ap, m_pDraggedPiece->m_rArea.Size());
    if (rtemp.IntersectRect(r2,rcPaint))  // intersection is not empty
    {
      if (m_bEmphasizeSlots)
      {
        r2.OffsetRect(-rcPaint.left, -rcPaint.top);
#ifndef WIN32
		// Draw a 3-dimentional rectangle.
        CPen grey_pen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));   //sari
        CPen* pOldPen = dcBuf.SelectObject(&grey_pen);
        dcBuf.MoveTo(r2.right-1, r2.top);
        dcBuf.LineTo(r2.left, r2.top);
        dcBuf.LineTo(r2.left, r2.bottom-1);
        dcBuf.SelectObject(pOldPen);
        dcBuf.SelectStockObject(WHITE_PEN);
        dcBuf.MoveTo(r2.left, r2.bottom-1);
        dcBuf.LineTo(r2.right-1, r2.bottom-1);
        dcBuf.LineTo(r2.right-1, r2.top);
        dcBuf.SelectStockObject(BLACK_PEN);
        dcBuf.MoveTo(r2.right - 2, r2.top + 1);
        dcBuf.LineTo(r2.left + 1, r2.top + 1);
        dcBuf.LineTo(r2.left + 1, r2.bottom - 2);
        dcBuf.SelectObject(pOldPen);
#else
        dcBuf.Draw3dRect(r2, RGB(255,255,255), RGB(0,0,0)); //sari
#endif
      }
      else
      {
        dcBuf.SelectStockObject(WHITE_PEN);
        dcBuf.SelectStockObject(WHITE_BRUSH);

        int d1 = -(m_pDraggedPiece->m_rArea.Width() / 4);
        int d2 = -(m_pDraggedPiece->m_rArea.Height() / 4);
        r2.InflateRect(d1,d2);
        r2.OffsetRect(-rcPaint.left, -rcPaint.top);

	    switch (m_pDraggedPiece->m_nShape)
	    {
	      case SHAPE_RECT:
                 dcBuf.Rectangle(r2);
	      	   break;
	      case SHAPE_OVAL:
                 dcBuf.Ellipse(r2);
	      	   break;
	    	case SHAPE_PIECE:
	      	   break;
        }
      }
    }
  }

  // Rejected move drawing
  if (m_pRejectPiece != NULL)
  {
    CPoint ap;
    AdjustPoint(CRect(m_ptRejectPiece, m_pRejectPiece->m_rArea.Size()), ap);
    CRect r1(ap, m_pRejectPiece->m_rArea.Size());
    CRect r2;
    if (r2.IntersectRect(r1,rcPaint))  // intersection is not empty
    {
      CPen pen (PS_SOLID, 3, RGB(255,0,0));
      CPen* pOldPen = dcBuf.SelectObject(&pen);
      dcBuf.SelectStockObject(WHITE_BRUSH);

      r1.OffsetRect(-rcPaint.left, -rcPaint.top);

      r1.InflateRect(-2, -2);

	  switch (m_pDraggedPiece->m_nShape)
	  {
	    case SHAPE_RECT:
             dcBuf.Rectangle(r1);
	  	   break;
	    case SHAPE_OVAL:
             dcBuf.Ellipse(r1);
	  	   break;
	    case SHAPE_PIECE:
	         m_pApplet->DrawImage(m_pDraggedPiece->m_pImage,r1.TopLeft(), dcBuf);
	  	   break;
      }

      CPoint pc;
#ifndef WIN32
      pc.x = (r1.left + r1.right)  /2;
      pc.y = (r1.top  + r1.bottom) /2;
#else // WIN32
      pc = r1.CenterPoint();
#endif // WIN32
      dcBuf.MoveTo(pc); dcBuf.LineTo(pc.x-5, pc.y-5);
      dcBuf.MoveTo(pc); dcBuf.LineTo(pc.x-5, pc.y+5);
      dcBuf.MoveTo(pc); dcBuf.LineTo(pc.x+5, pc.y-5);
      dcBuf.MoveTo(pc); dcBuf.LineTo(pc.x+5, pc.y+5);
      dcBuf.SelectObject(pOldPen);
    }
  }

  //Game Text areas
  CCmgTextArea* GameText;
  size = m_vecTexts.GetSize();
  for (i=0; i<size; i++)  // list of buttons to be redrawn
  {
    o = m_vecTexts.GetAt(i);
    GameText = (CCmgTextArea*) o;
    CRect r1(GameText->m_rArea);
    if (r1.IntersectRect(r1,rcPaint))  // intersection is not empty
  	  GameText->DrawText(&dcBuf,rcPaint.TopLeft());
  }

  rcPaint.OffsetRect(m_cOffsetPoint);

  rcPaint.OffsetRect(m_RectScroll.TopLeft());
  dc.BitBlt(rcPaint.left, rcPaint.top, rcPaint.Width(), rcPaint.Height(), &dcBuf, 0, 0, SRCCOPY);
  dcBuf.SelectObject(bmOld);
  dcBuf.DeleteDC();

}


/////////////////////////////////////////////////////////////////////////////////////
// Remove all pieces from the board.
/////////////////////////////////////////////////////////////////////////////////////
void CUbqGameBoard::RemoveAllPieces()
{
  while (m_vecPieces.GetSize())
  {
    CObject* p = m_vecPieces.GetAt(0);
    m_vecPieces.RemoveAt(0);
    CUbqGamePiece* pgp = (CUbqGamePiece*) p;
    delete pgp;
  }
  m_pDraggedPiece = NULL;

  PostPaintEvent(m_rBoard);
}

/////////////////////////////////////////////////////////////////////////////////////
// Add a piece to the game board
// @param piece The game piece that should be added. If there is some overlapping,
// new piece will be placed on top of older pieces.
/////////////////////////////////////////////////////////////////////////////////////
void CUbqGameBoard::AddPiece(CUbqGamePiece* pPiece)
{
  m_vecPieces.Add(pPiece);
  PostPaintEvent(pPiece->m_rArea);
}


BOOL CUbqGameBoard::MouseDown(CPoint MPoint)
{
  if ((m_bIsLocked) && m_rBoard.PtInRect(MPoint))
    return TRUE;

  // butts
  int size = m_vecButtons.GetSize();
  for (int i = 0;i < size; i++)
  {
    CUbqGameButton* btn = (CUbqGameButton*)(m_vecButtons.GetAt(i));
    if (btn->IsInside(MPoint) && !btn->IsDisabled())
    {
      m_pCurrClickedButton = btn;
      m_pCurrClickedButton->MouseDown();
      break;
    }
  }

  // pieces
  CPoint ap;
  AdjustPoint(MPoint, ap);

  for (i = m_vecPieces.GetSize() - 1; i >= 0; i--)  // from top to bottom on Z order
  {
    CUbqGamePiece* p = (CUbqGamePiece*)(m_vecPieces.GetAt(i));
    if (p->IsInside(ap) && (p->GetAttribute() & (PA_CLICK|PA_DRAG|PA_DBLCLK)) != 0)
    {
      if (m_pApplet->OnPieceMouseDown(p, ap))
      {
        m_pDraggedPiece = p;
        m_ptDragPieceDest = m_pDraggedPiece->m_rArea.TopLeft();
        CPoint ap;
        AdjustPoint(CRect(m_ptDragPieceDest, m_pDraggedPiece->m_rArea.Size()), ap);
        PostPaintEvent(CRect(ap, m_pDraggedPiece->m_rArea.Size()));
      }
      break;
    }
  }

  return TRUE;
}

BOOL CUbqGameBoard::MouseDrag(CPoint MPoint)
{
 if (m_pDraggedPiece == NULL) return TRUE; // no piece to drag
 if ((m_pDraggedPiece->GetAttribute() & PA_DRAG) == 0) return TRUE; // piece may not drag

 CPoint ap;
 AdjustPoint(MPoint, ap);
 ap.x -= (m_pDraggedPiece->m_rArea.Width()/2);
 ap.y -= (m_pDraggedPiece->m_rArea.Height()/2);

 CUbqGameBoardArea* pArea = GetArea(CRect(ap, m_pDraggedPiece->m_rArea.Size()));
 if (pArea == NULL) return TRUE;  // not in any area
 CUbqGameBoardSlot* slot = pArea->GetBestSlot(ap);

 if (slot != NULL)
   ap = slot->m_ptCoord;

 if (ap == m_pDraggedPiece->m_rArea.TopLeft())
   return TRUE; // not moved
 m_pDragLastArea = pArea;
 m_pDragLastSlot = slot;
 if (m_pApplet->OnPieceDuringDrag(m_pDraggedPiece, pArea, slot, ap))
 {
   CPoint tmp;
   AdjustPoint(CRect(m_ptDragPieceDest, m_pDraggedPiece->m_rArea.Size()), tmp);
   CRect rf(tmp, m_pDraggedPiece->m_rArea.Size());
   m_ptDragPieceDest = ap;
   AdjustPoint(CRect(m_ptDragPieceDest, m_pDraggedPiece->m_rArea.Size()), tmp);
   CRect rt(tmp, m_pDraggedPiece->m_rArea.Size());
   rf.UnionRect(rf,rt);
   rf.InflateRect(1,1);
   PostPaintEvent(rf);
 }

 return TRUE;
}


BOOL CUbqGameBoard::MouseUp(CPoint MPoint)
{
  if (m_pDraggedPiece != NULL)
  {
    CPoint ap1;
    AdjustPoint(CRect(m_ptDragPieceDest, m_pDraggedPiece->m_rArea.Size()), ap1);
    CPoint ap2;
    AdjustPoint(m_pDraggedPiece->m_rArea, ap2);

    if (m_pApplet->OnPieceEndDrag(m_pDraggedPiece, m_pDragLastArea, m_pDragLastSlot, m_ptDragPieceDest))
    {
       if (m_pDraggedPiece != NULL)  // not moved from applet
       {
         CSize Size = m_pDraggedPiece->m_rArea.Size();
         m_pDraggedPiece = NULL;
         PostPaintEvent(CRect(ap1, Size));
         PostPaintEvent(CRect(ap2, Size));
       }
    }
    else
    {
      CSize Size = m_pDraggedPiece->m_rArea.Size();
      m_pDraggedPiece = NULL;
      PostPaintEvent(CRect(ap1, Size));
      PostPaintEvent(CRect(ap2, Size));
    }

    return TRUE;
 }

 if (m_pCurrClickedButton != NULL)// no piece to drag
 {
     if ((m_pCurrFocusedButton != NULL) &&
         (m_pCurrFocusedButton->GetID() == m_pCurrClickedButton->GetID()))
     {
          m_pCurrClickedButton = NULL;
          m_pCurrFocusedButton->MouseUp();
          if (!m_pCurrFocusedButton->IsDisabled())
              m_pApplet->OnButtonClicked(m_pCurrFocusedButton->GetID());
     }
     else
        m_pCurrClickedButton = NULL;

     return TRUE;
 }
 return TRUE;
}



/******************************************************************
 *  Areas management                                              *
 ******************************************************************/

/**
* Remove all board areas.
*/
void CUbqGameBoard::RemoveAllAreas()
{
  while (m_vecAreas.GetSize() > 0)
  {
    CObject* po = m_vecAreas.GetAt(0);
    CUbqGameBoardArea* pa = (CUbqGameBoardArea*) po;
    delete pa;
    m_vecAreas.RemoveAt(0);
  }
}

/**
* Add an area to the board. As Area is a rectangle where pieces can be moved into.
* Board sections that are not in any area can not contain board pieces.
*/
void CUbqGameBoard::AddArea(CUbqGameBoardArea* ar)
{
  m_vecAreas.Add(ar);
}

/**
* Remove an area from the board
*/
BOOL CUbqGameBoard::RemoveArea(int id)
{
  CObject* o = NULL;
  CUbqGameBoardArea* ar = NULL;
  int size = m_vecAreas.GetSize();

  for (int i = 0; i < size; i++)
  {
    o = m_vecAreas.GetAt(i);
    ar = (CUbqGameBoardArea*)o;
    if (ar->GetID() == id)
    {
      delete ar;
      m_vecAreas.RemoveAt(i);
      return TRUE;
    }
  }
  return FALSE;
}

CUbqGameBoardArea* CUbqGameBoard::GetArea(CRect rArea)
{
  CUbqGameBoardArea* ar = NULL;
  CObject* o = NULL;
  int size =  m_vecAreas.GetSize();

  for (int i = 0; i < size; i++)
  {
    o = m_vecAreas.GetAt(i);
    ar = (CUbqGameBoardArea*) o;
    if (ar->IsInside(rArea))
      return ar;
  }

  return NULL;
}


/******************************************************************
 *  Multiple Images management
 ******************************************************************/

void CUbqGameBoard::AddMultiImage(class CUbqMultImage* pMultiImage)
{
  m_vecMultipleImages.Add(pMultiImage);
}

void CUbqGameBoard::RemoveMultiImage(class CUbqMultImage* pMultiImage)
{
  int size = m_vecMultipleImages.GetSize();
  for (int i = 0; i < size; i++)
  {
    CUbqMultImage* mi = (CUbqMultImage*)(m_vecMultipleImages.GetAt(i));
    if (mi == pMultiImage)
    {
      m_vecMultipleImages.RemoveAt(i);
      PostPaintEvent(mi->m_rArea);
      delete mi;
      return;
    }
  }
}

void CUbqGameBoard::RemoveAllMultiImages()
{
  while (m_vecMultipleImages.GetSize() > 0)
  {
    delete (CUbqMultImage*)(m_vecMultipleImages.GetAt(0));
    m_vecMultipleImages.RemoveAt(0);
  }
}


/******************************************************************
 *  Buttons management                                            *
 ******************************************************************/

/**
* Remove all buttons areas.
*/
void CUbqGameBoard::RemoveAllButtons()
{
  // buttons are really removed when removing the multi-images
  m_pCurrFocusedButton  = NULL;
  m_pCurrClickedButton  = NULL;

  m_vecButtons.RemoveAll();
}

/**
* Add a button to the board. As button is a rectangle where user can click on.
*/
void CUbqGameBoard::AddButton(CUbqGameButton* btn)
{
  m_vecButtons.Add(btn);
  AddMultiImage(btn);
}

/**
* Remove a button from the board
*/
BOOL CUbqGameBoard::RemoveButton(int id)
{
  CObject* o = NULL;
  CUbqGameButton* btn = NULL;
  int size = m_vecButtons.GetSize();

  for (int i=0; i<size; i++)
  {
    o = m_vecButtons.GetAt(i);
    btn = (CUbqGameButton*) o;
    if (btn->GetID() == id)
    {
      delete btn;
      m_vecButtons.RemoveAt(i);
      return TRUE;
    }
  }

  return FALSE;
}

CUbqGameButton* CUbqGameBoard::GetButton(CPoint Point)
{
  CUbqGameButton* btn = NULL;
  CObject* o = NULL;
  int size = m_vecButtons.GetSize();

  for (int i = 0; i < size; i++)
  {
    o = m_vecButtons.GetAt(i);
    btn = (CUbqGameButton*)o;
    if (btn->IsInside(Point))
      return btn;
  }

  return NULL;
}

CUbqGameButton* CUbqGameBoard::GetButtonByID(int id)
{
  CUbqGameButton* btn = NULL;
  CObject* o = NULL;
  int size = m_vecButtons.GetSize();

  for (int i = 0; i < size; i++)
  {
    o = m_vecButtons.GetAt(i);
    btn = (CUbqGameButton*) o;
    if (btn->GetID() == id)
      return btn;
  }

  return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CUbqGameBoard message handlers

void CUbqGameBoard::OnPaint()
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return; //xxx

  CPaintDC dc(this); // device context for painting
  CRect rcPaint = dc.m_ps.rcPaint;

  if (m_nBpp != dc.GetDeviceCaps(BITSPIXEL))
  {
    m_cBoardBmp.DeleteObject();
    m_nBpp=CBmp::ReadBmp(&m_cBoardBmp,m_nBoardBmpName,this);
    CAnim::RereadAllBitmaps();
  }

  CPalette* OldPal= dc.SelectPalette(&(CBmp::m_cPalette),FALSE);
  dc.RealizePalette();

  // serg
  // we redraw board&pieces only if the board area was clipped
  CRect Checkintersect=m_rGame;
  Checkintersect.OffsetRect(m_cOffsetPoint);
  if (!rcPaint.IsRectEmpty() && rcPaint.IntersectRect(rcPaint,Checkintersect))
  {
    rcPaint.OffsetRect(-m_RectScroll.TopLeft());
    ASSERT(rcPaint.top >= 0 && rcPaint.left >= 0);
    DrawBoardAndPieces(dc, rcPaint);
  }

  dc.SelectPalette(OldPal,TRUE);
  dc.RealizePalette();
}


void CUbqGameBoard::OnLButtonDown(UINT nFlags, CPoint point)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  point.x -= m_RectScroll.TopLeft().x + m_cOffsetPoint.x;
  point.y -= m_RectScroll.TopLeft().y + m_cOffsetPoint.y;

  MouseDown(point);
  m_bCaptureSet = TRUE;
  SetCapture();

  m_pApplet->OnLButtonDown (point);  // call applet callback.
  if (m_bSuspend) return;

  CWnd::OnLButtonDown(nFlags, point);
}

void CUbqGameBoard::OnRButtonDown(UINT nFlags, CPoint point)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx
  if (m_bShowPopupMenu)
    m_pApplet->LoadMenu(point);
  if (m_bSuspend) return;//xxx

  // This member function is called by the framework to allow your
  // application to handle a Windows message. The parameters passed
  // to your function reflect the parameters received by the framework
  // when the message was received. If you call the base-class implementation
  // of this function, that implementation will use the parameters originally
  // passed with the message and not the parameters you supply to the function.
  CWnd::OnRButtonDown(nFlags, point);
}

/*--------------------------------------*/
/*   ON  L  BUTTON  DBL CLK				*/
/*--------------------------------------*/
void CUbqGameBoard::OnLButtonDblClk(UINT nFlags, CPoint MPoint)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  MPoint.x -= m_RectScroll.TopLeft().x + m_cOffsetPoint.x;
  MPoint.y -= m_RectScroll.TopLeft().y + m_cOffsetPoint.y;

  CPoint ap;
  AdjustPoint(MPoint, ap);
  CObject* o;
  CUbqGamePiece* p;

  // Try to find piece in range
  if (!(m_bIsLocked && m_rBoard.PtInRect(MPoint)))
  {
    for (int i=m_vecPieces.GetSize()-1; i>=0; i--)  // from top to bottom on Z order
    {
      o = m_vecPieces.GetAt(i);
      p = (CUbqGamePiece*) o;
      if (p->IsInside(ap) &&
         (p->GetAttribute() & (PA_CLICK|PA_DRAG|PA_DBLCLK)) != 0)
      {
        if (m_pApplet->OnPieceDoubleClick(p, ap))
        {
          CPoint PieceDest = p->m_rArea.TopLeft();
          CPoint ap;
          AdjustPoint(CRect(PieceDest, p->m_rArea.Size()), ap);
          PostPaintEvent(CRect(ap, p->m_rArea.Size()));
        }
        break;
      }
    }
  }
  CWnd::OnLButtonDblClk(nFlags, MPoint);
}

void CUbqGameBoard::OnMouseMove(UINT nFlags, CPoint point)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  point.x -= m_RectScroll.TopLeft().x + m_cOffsetPoint.x;
  point.y -= m_RectScroll.TopLeft().y + m_cOffsetPoint.y;

  if (m_bCaptureSet)
  {
    // TODO: Fix a bug of fast mouse move beyond the window.
    if (GetCapture() != this)
      m_bCaptureSet = FALSE; // lost capture

    MouseDrag(point);
  }

  // during piece drag ignore buttons
  if (m_pDraggedPiece != NULL)
    return;

  CUbqGameButton* pButton = GetButton(point);
  // The cursor is not standing on any button.
  if (pButton == NULL)
  {
    if (m_pCurrFocusedButton != NULL)
    {
      m_pCurrFocusedButton->SetInFocus(FALSE);
      m_pCurrFocusedButton = NULL;
    }
  }
  else  // The cursor is on *pButton.
  {
    if ((m_pCurrClickedButton != NULL) && (m_pCurrClickedButton->GetID() == pButton->GetID()))
      pButton->MouseDown();

    if (m_pCurrFocusedButton != NULL)
    {
      if (m_pCurrFocusedButton->GetID() != pButton->GetID())
      { // Update the focused button to be the one that we are
        // standing on right now.
        m_pCurrFocusedButton->SetInFocus(FALSE);
        m_pCurrFocusedButton = pButton;
        if (m_pCurrClickedButton == NULL)
          pButton->SetInFocus(TRUE);
      }
    }
    else
    {
      m_pCurrFocusedButton = pButton;
      if (m_pCurrClickedButton == NULL)
        pButton->SetInFocus(TRUE);
    }
  }

  m_pApplet->OnMouseMove (point);  // call applet callback.
  CWnd::OnMouseMove(nFlags, point);
}

void CUbqGameBoard::OnLButtonUp(UINT nFlags, CPoint point)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  point.x -= m_RectScroll.TopLeft().x + m_cOffsetPoint.x;
  point.y -= m_RectScroll.TopLeft().y + m_cOffsetPoint.y;

  if (m_bCaptureSet)
  {
    m_bCaptureSet = FALSE;
    ReleaseCapture();
  }
  MouseDrag(point);
  MouseUp(point);

  m_pApplet->OnLButtonUp (point);  // call applet callback.
  CWnd::OnLButtonUp(nFlags, point);
}

/*---------------------------------------*/
/*    ON R Button Up					 */
/*---------------------------------------*/
void CUbqGameBoard::OnRButtonUp(UINT nFlags, CPoint point)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  m_pApplet->OnRButtonUp (point);  // call applet callback.
  CWnd::OnRButtonUp(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// State management
/////////////////////////////////////////////////////////////////////////////////////////////
DWORD CUbqGameBoard::GetState(BYTE* buf, DWORD bufLen)
{
  DWORD nUsedBytes = 0;
  DWORD nLeft = bufLen;
  BYTE* pCurr = buf;

  CObject* o;
  CUbqGamePiece* p;

  // Take current state of pieces
  int size = m_vecPieces.GetSize();
  for (int i=0; i<size; i++)  // bottom to top to preserve Z order
  {
    o = m_vecPieces.GetAt(i);
    p = (CUbqGamePiece*) o;

    WORD x    = /*htons*/((WORD)p->m_rArea.left);
    WORD y    = /*htons*/((WORD)p->m_rArea.top);
    WORD id   = /*htons*/(p->id);
    WORD attr = /*htons*/(p->GetAttribute());
    WORD type = /*htons*/(p->GetType());
    WORD Action = /*htons*/((WORD)ACTION_ADD_PIECE); //see GameComm.h

    WORD Size = (sizeof(Action)+sizeof(x)+sizeof(y)+sizeof(id)+sizeof(attr)+sizeof(type));
    if (nLeft < Size)
      return (0);
    WORD* ps = (WORD*)pCurr;
    ps[0] = Action;
    ps[1] = id;
    ps[2] = x;
    ps[3] = y;
    ps[4] = attr;
    ps[5] = type;

    nUsedBytes += Size;
    pCurr += Size;
    nLeft -= Size;
  }
  return nUsedBytes;
}

BOOL CUbqGameBoard::SetState(BYTE* buf, DWORD bufLen)
{
  DWORD nLeft = bufLen;
  BYTE* pCurr = buf;

  CObject* o;
  CUbqGamePiece* p;

  while (nLeft > 0)
  {
    WORD x,y,id,attr;
    WORD Size = sizeof(x)+sizeof(y)+sizeof(id)+sizeof(attr);
    if (nLeft < Size)
      return (FALSE);
    WORD* ps = (WORD*)pCurr;
    id = /*ntohs*/(ps[0]);
    x = /*ntohs*/(ps[1]);
    y = /*ntohs*/(ps[2]);
    attr = /*ntohs*/(ps[3]);
    pCurr += Size;
    nLeft -= Size;

    int size = m_vecPieces.GetSize();
    for (int i = 0; i < size; i++)
    {
      o = m_vecPieces.GetAt(i);
      p = (CUbqGamePiece*) o;
      if (p->id == (int)id)
      {
        p->m_rArea.OffsetRect(x-p->m_rArea.left, y-p->m_rArea.top);
        m_vecPieces.RemoveAt(i);
        m_vecPieces.Add(p);        // last element is on the top of the Z order
        break;
      }
    }
  }

  PostPaintEvent(m_rBoard);
  return TRUE;
}

void CUbqGameBoard::OnMultiImageChange(CUbqMultImage* pMultImage)
{
  PostPaintEvent(pMultImage->m_rArea);
}

void CUbqGameBoard::SetButtonDisabled(int id)
{
  if ((m_pCurrClickedButton != NULL) &&
      (m_pCurrClickedButton->GetID() == id))
      m_pCurrClickedButton = NULL;

  CUbqGameButton* btn = GetButtonByID(id);

  btn->SetDisabled(TRUE);
}

void CUbqGameBoard::SetButtonEnabled(int id)
{
  if ((m_pCurrClickedButton != NULL) &&
      (m_pCurrClickedButton->GetID() == id)) return;

  CUbqGameButton* btn = GetButtonByID(id);

  if ((m_pCurrFocusedButton != NULL) &&
      (m_pCurrFocusedButton->GetID() == id))
    btn->SetEnabledInFocus();
  else
    btn->SetDisabled(FALSE);
}


void CUbqGameBoard::SetPieceImage(int id,CUbqGameImage* pImage)
{
  CUbqGamePiece* p = GetPieceByID(id);
  if (p != NULL)
    p->SetImage(pImage);
}

void CUbqGameBoard::SetPieceAttribute(CUbqGamePiece* pPiece, int iAttr)
{
  pPiece->SetAttribute(iAttr);
  PostPaintEvent(pPiece->m_rArea);
}

void CUbqGameBoard::OnNewGame()
{
  m_pDraggedPiece       = NULL;
  m_pDragLastArea       = NULL;
  m_pDragLastSlot       = NULL;
  m_pCurrClickedButton  = NULL;
  PostPaintEvent(m_rBoard);
}

/////////////////////////////////////////////////////////////////////////////
// SCROLLBARS MANAGMENT

void CUbqGameBoard::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  int HSInc;

  switch(nSBCode)
  {
  case SB_LEFT:
    HSInc = -HSPos;
    break;

  case SB_RIGHT:
    HSInc = HSRange - HSPos;
    break;

  case SB_LINELEFT:
    HSInc = -1;
    break;

  case SB_LINERIGHT:
    HSInc = +1;
    break;

  case SB_THUMBTRACK:
    HSInc = nPos - HSPos;
    break;

  case SB_PAGELEFT:
    HSInc = -2;
    break;

  case SB_PAGERIGHT:
    HSInc = +2;
    break;

  default:
    return;
  }

  HSPos += HSInc;

#ifdef WIN32
  if (HSPos <= HSi.nMin)
  {
    ScrollWindow(-m_RectScroll.left, 0);
    m_RectScroll.OffsetRect(-m_RectScroll.left, 0);
    HSPos = HSi.nMin;
  }
  else
    if (HSPos >= (int)(HSi.nMax-HSi.nPage + 1))
    {
      ScrollWindow(-(m_RectScroll.left + HSRange), 0);
      m_RectScroll.OffsetRect(-(m_RectScroll.left + HSRange), 0);
      HSPos = (HSi.nMax-HSi.nPage + 1);
    }
    else
    {
      ScrollWindow((int)((double)-HSInc*HSRange/(HSi.nMax-HSi.nPage+1.)), 0);
      m_RectScroll.OffsetRect((int)((double)-HSInc*HSRange/(HSi.nMax-HSi.nPage+1.)), 0);
    }
#else // WIN32
  if (HSPos <= 0)
  {
    ScrollWindow(-m_RectScroll.left, 0);
    m_RectScroll.OffsetRect(-m_RectScroll.left, 0);
    HSPos = 0;
  }
  else
    if (HSPos >= 10)
    {
      ScrollWindow(-(m_RectScroll.left + HSRange), 0);
      m_RectScroll.OffsetRect(-(m_RectScroll.left + HSRange), 0);
      HSPos = 10;
    }
    else
    {
      ScrollWindow(-HSInc*HSRange/10, 0);
      m_RectScroll.OffsetRect(-HSInc*HSRange/10, 0);
    }
#endif // WIN32

  SetScrollPos(SB_HORZ, HSPos, TRUE);

  UpdateWindow();
}

void CUbqGameBoard::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  int VSInc;

  switch(nSBCode)
  {
  case SB_TOP:
    VSInc = -VSPos;
    break;

  case SB_BOTTOM:
    VSInc = VSRange - VSPos;
    break;

  case SB_LINEUP:
    VSInc = -1;
    break;

  case SB_LINEDOWN:
    VSInc = +1;
    break;

  case SB_THUMBTRACK:
    VSInc = nPos - VSPos;
    break;

  case SB_PAGEUP:
    VSInc = -2;
    break;

  case SB_PAGEDOWN:
    VSInc = +2;
    break;

  default:
    return;
  }

  VSPos += VSInc;

#ifdef WIN32
  if (VSPos <= VSi.nMin)
  {
    ScrollWindow(0, -m_RectScroll.top);
    m_RectScroll.OffsetRect(0, -m_RectScroll.top);
    VSPos = VSi.nMin;
  }
  else
    if (VSPos >= (int)(VSi.nMax-VSi.nPage + 1))
    {
      ScrollWindow(0, -(m_RectScroll.top + VSRange));
      m_RectScroll.OffsetRect(0, -(m_RectScroll.top + VSRange));
      VSPos = (VSi.nMax-VSi.nPage + 1);
    }
    else
    {
      ScrollWindow(0, (int)((double)-VSInc*VSRange/(VSi.nMax-VSi.nPage+1.)));
      m_RectScroll.OffsetRect(0, (int)((double)-VSInc*VSRange/(VSi.nMax-VSi.nPage+1.)));

    }
#else // WIN32
  if (VSPos <= 0)
  {
    ScrollWindow(0, -m_RectScroll.top);
    m_RectScroll.OffsetRect(0, -m_RectScroll.top);
    VSPos = 0;
  }
  else
    if (VSPos >= 10)
    {
      ScrollWindow(0, -(m_RectScroll.top + VSRange));
      m_RectScroll.OffsetRect(0, -(m_RectScroll.top + VSRange));
      VSPos = 10;
    }
    else
    {
      ScrollWindow(0, -VSInc*VSRange/10);
      m_RectScroll.OffsetRect(0, -VSInc*VSRange/10);
    }
#endif  // WIN32

  SetScrollPos(SB_VERT, VSPos, TRUE);

  UpdateWindow();
}

void CUbqGameBoard::SetVScrollBar()
{
  VSRange = m_rGame.Height() - m_RectScroll.Height();
  VSPos = 0;

#ifdef WIN32
  VSi.cbSize = sizeof(VSi);
  VSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
  VSi.nMin = 0;
  VSi.nMax =  (int)(10.*(1.+ (double)m_RectScroll.Height()/(double)m_rGame.Height()));
  VSi.nPage = (UINT)(20.* (double)m_RectScroll.Height()/(double)m_rGame.Height() + 1.);
  VSi.nPos = VSPos;
  SetScrollInfo(SB_VERT, &VSi, TRUE);
#else // WIN32
  SetScrollRange(SB_VERT, 0, 10, FALSE);
  SetScrollPos(SB_VERT, VSPos, TRUE);
#endif  //WIN32
}


void CUbqGameBoard::SetHScrollBar()
{
  HSRange = m_rGame.Width() - m_RectScroll.Width();
  HSPos = 0;

#ifdef WIN32
  HSi.cbSize = sizeof(HSi);
  HSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
  HSi.nMin = 0;
  HSi.nMax = (int)(10.*(1.+ (double)m_RectScroll.Width()/(double)m_rGame.Width()));
  HSi.nPage = (UINT)(20.* (double)m_RectScroll.Width()/(double)m_rGame.Width() + 1.);
  HSi.nPos = HSPos;
  SetScrollInfo(SB_HORZ, &HSi, TRUE);
#else // WIN32
  SetScrollRange(SB_HORZ, 0, 10, FALSE);
  SetScrollPos(SB_HORZ, HSPos, TRUE);
#endif  // WIN32
}


void CUbqGameBoard::OnSize(UINT nType, int cx, int cy)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx

  if (cx == 0 || cy == 0)
    return;

  if (m_bShowScrollBar)
  {
  // On resizing we scroll window so that
  // the top-left corner is placed at (0,0).
  ScrollWindow(0, -m_RectScroll.top);
  m_RectScroll.OffsetRect(0, -m_RectScroll.top);

  ScrollWindow(-m_RectScroll.left, 0);
  m_RectScroll.OffsetRect(-m_RectScroll.left, 0);
  m_RectScroll.SetRect(0, 0, cx, cy); // == GetClientRect(&m_RectScroll), whatever you want

  if (cx>m_rGame.Width())
    m_cOffsetPoint.x=(cx-m_rGame.Width())/2;
  else
    m_cOffsetPoint.x=0;

  if (cy>m_rGame.Height())
    m_cOffsetPoint.y=(cy-m_rGame.Height())/2;
  else
    m_cOffsetPoint.y=0;

  m_pApplet->OnSize(); //change the


#ifdef WIN32
  SetVScrollBar();
  SetHScrollBar();
#else // WIN32
  if (m_RectScroll.Height() < m_rGame.Height())
    SetVScrollBar();
  else
    SetScrollRange(SB_VERT, 0, 0, TRUE);

  if (m_RectScroll.Width() < m_rGame.Width())
    SetHScrollBar();
  else
    SetScrollRange(SB_HORZ, 0, 0, TRUE);
#endif  // WIN32
  }

UpdateWindow();
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
BOOL CUbqGameBoard::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  // Handled by me...
  if (CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

  // No! Handled by applet.
  if (m_pApplet->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

  // Life sucks :(
  return FALSE;
}

void CUbqGameBoard::DoLoadCursor(int where,UINT cursor)
{
  m_hCursors[where]=AfxGetApp()->LoadCursor(cursor);
}

void CUbqGameBoard::DoLoadOEMCursor(int where,UINT cursor)
{
  m_hCursors[where]=AfxGetApp()->LoadOEMCursor(cursor);
}

void CUbqGameBoard::ChangeCursor(long cursor)
{
  if (m_bDisableCursor)
    return;

  if (m_hCursors[cursor] != NULL)
  {
    m_hCurrentCursor=m_hCursors[cursor];

#ifdef WIN32
    SetClassLong(GetSafeHwnd(),GCL_HCURSOR,(long)m_hCurrentCursor);
#else
    SetClassWord(GetSafeHwnd(),GCW_HCURSOR,(WORD)m_hCurrentCursor);
#endif
    SetCursor(m_hCurrentCursor);
  }
}

void CUbqGameBoard::DisableCursor()
{
  m_bDisableCursor=TRUE;
#ifdef WIN32
    SetClassLong(GetSafeHwnd(),GCL_HCURSOR,(long)m_hCursors[0]);
#else
    SetClassWord(GetSafeHwnd(),GCW_HCURSOR,(WORD)m_hCursors[0]);
#endif
  SetCursor(m_hCursors[0]);
}

void CUbqGameBoard::EnableCursor()
{
  m_bDisableCursor=FALSE;
}

void CUbqGameBoard::AddText(class CCmgTextArea* pText)
{
  m_vecTexts.Add(pText);
  PostPaintEvent(pText->m_rArea);
}

void CUbqGameBoard::RemoveText(int ID)
{
  CObject* o;
  CCmgTextArea* p;

  CCmgTextArea* textarea=GetTextByID(ID);
  ASSERT(textarea);

  int size = m_vecTexts.GetSize();
  for (int i=0; i<size; i++)
  {
    o = m_vecTexts.GetAt(i);
    p = (CCmgTextArea*) o;
    if (p == textarea)
    {
      CRect rTMP = p->m_rArea;
      delete m_vecTexts.GetAt(i);
      m_vecTexts.RemoveAt(i);
      PostPaintEvent(rTMP);
      break;
    }
  }
}

void CUbqGameBoard::SetText(int ID,CString text)
{
  CCmgTextArea* textarea=GetTextByID(ID);
  ASSERT(textarea);
  textarea->SetText(text);
  PostPaintEvent(textarea->m_rArea);
}

void CUbqGameBoard::SetTextColors(int ID,COLORREF bg,COLORREF fg)
{
  CCmgTextArea* textarea=GetTextByID(ID);
  ASSERT(textarea);
  textarea->SetColors(bg,fg);
  PostPaintEvent(textarea->m_rArea);
}


CCmgTextArea* CUbqGameBoard::GetTextByID(int ID)
{
  CObject* o;
  CCmgTextArea* t;
  CCmgTextArea* result = NULL;

  int size = m_vecTexts.GetSize();

  for (int i=0; i<size; i++)
  {
    o = m_vecTexts.GetAt(i);
    t = (CCmgTextArea*) o;
    if (ID == t->GetID())
    {
      result = t;
      break;
    }
  }
  return (result);
}

void CUbqGameBoard::RemoveRemoveAllTexts()
{
  while (m_vecTexts.GetSize() > 0)
  {
    CObject* po = m_vecTexts.GetAt(0);
    CCmgTextArea* pa = (CCmgTextArea*) po;
    delete pa;
    m_vecTexts.RemoveAt(0);
  }
}

void CUbqGameBoard::OnTimer(UINT nIDEvent)
{
  //if (nIDEvent != 1)
  //  ASSERT(0);
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return;//xxx
  m_pApplet->OnTimer();
}

LRESULT CUbqGameBoard::OnMMNotify(WPARAM wParam,LPARAM lParam)
{
  AFX_MANAGE_STATE(_afxModuleAddrThis)
  if (IsRemovalSuspended()) return 0;//xxx
  return m_pApplet->OnMMNotify(wParam, lParam);
}

BOOL CUbqGameBoard::IsRemovalSuspended()//xxx - start
{
	if (m_pApplet->IsRemovalSuspended())
	{
	  m_bSuspend = TRUE;
	  return TRUE;
	}
	else return FALSE;
}

void CUbqGameBoard::DeleteWindow()
{
  if(!::IsWindow(m_hWnd))
	m_hWnd = NULL;

  if (m_pApplet->IsOpenMenu())
    m_pApplet->SuspendRemoval();
  else
  {
    delete this;
  }
} ///xxx - end
