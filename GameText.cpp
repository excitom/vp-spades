// GameText.cpp - inmplementation of the class CCmgGameText
// the class for displaying text on the game board

#include "stdafx.h"
#include "GameApp.h"
#include "GameBrd.h"
#include "GameText.h"

/////////////////////////////////////////////////////////////////////////////
// construction/destruction

CCmgTextArea::CCmgTextArea(int ID,CRect Area, CUbqGameBoard*  pBoard,int TextFont)
{
  m_rArea = Area;
  m_pGameBoard = pBoard;
  m_iStatus = -1;
  m_nID=ID;
  m_nBkColor=RGB(0xFF,0,0);
  m_nTextColor=RGB(0,0,0xFF);
  m_nTextFont=TextFont;
}

CCmgTextArea::~CCmgTextArea()
{
}

/////////////////////////////////////////////////////////////////////////////////
// Add an image to the list (first one is number 0)
void CCmgTextArea::SetText(CString  text)
{
  m_sText=text;
}

void CCmgTextArea::SetColors(COLORREF bg,COLORREF fg)
{
  m_nBkColor=bg;
  m_nTextColor=fg;
}

/////////////////////////////////////////////////////////////////////////////////
// is inside the object?
BOOL CCmgTextArea::IsInside(CPoint Point)
{
	return (m_rArea.PtInRect(Point));
}

//////////////////////////////////////////////////////////////////////////////////
// set the status/gif
void CCmgTextArea::SetStatus(int Status)
{
  //m_pGameBoard->OnMultiImageChange(this);
}

void CCmgTextArea::DrawText(CDC* pDC,CPoint DrawPoint)
{
	CFont aaa;
	CFont* OldFont;
	BOOL ret;
	
	
	switch (m_nTextFont)
	{
	case TEXTFONT_WIN_LOOSE:
	  ret=aaa.CreateFont(20,10,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,
		                 CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH,CString("Courier New"));
	  break;
	case TEXTFONT_FIELD:
	  ret=aaa.CreateFont(12,0,0,0,FW_REGULAR,0,0,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,     
		                 CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH,CString("Verdana"));
	  break;

	case TEXTFONT_FIELD_B:
	  ret=aaa.CreateFont(12,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,     
		                 CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH,CString("Verdana"));
	  break;

	case TEXTFONT_SCORE:
	  ret=aaa.CreateFont(14,0,0,0,FW_REGULAR,0,0,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,     
		                 CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH,CString("Courier New"));
	  break;

	case TEXTFONT_SCORE_B:
	  ret=aaa.CreateFont(14,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_CHARACTER_PRECIS,     
		                 CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FIXED_PITCH,CString("Courier New"));
	  break;

	default:
	  ASSERT(0);
	}

	if (ret)
	  OldFont=pDC->SelectObject(&aaa);

	COLORREF OldTextColor=pDC->SetTextColor(m_nTextColor);
	COLORREF OldBkColor=pDC->SetBkColor(m_nBkColor);

	pDC->SetBkMode(TRANSPARENT);
	
	CPoint p1=m_rArea.TopLeft();         
	p1.x-=DrawPoint.x;
	p1.y-=DrawPoint.y;
#ifdef WIN32	                           
	pDC->ExtTextOut(p1.x,p1.y,0,m_rArea,m_sText,NULL);
#else
	pDC->ExtTextOut(p1.x,p1.y,0,m_rArea,LPCSTR(m_sText),m_sText.GetLength(),NULL);
#endif	
	
	pDC->SetBkColor(OldBkColor);
	pDC->SetTextColor(OldTextColor);

	if (ret)
	  pDC->SelectObject(OldFont);
}
