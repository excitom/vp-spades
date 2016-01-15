// GameMIm.cpp - inmplementation of the class CUbqMultImage
// the generic class for button and indicator classes

#include "stdafx.h"
#include "GameImg.h"
#include "GameBrd.h"
#include "GameMIm.h"


/////////////////////////////////////////////////////////////////////////////
// CUbqMultImage - multiImage objects [buttons, indicators, etc] prototype
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// construction/destruction

CUbqMultImage::CUbqMultImage(CRect Area, CUbqGameBoard*  pBoard)
{
	m_rArea = Area;
  m_pGameBoard = pBoard;
  m_iStatus = -1;
  m_pCurrImage=NULL;
}

CUbqMultImage::~CUbqMultImage()
{
  m_vecImages.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////////
// Add an image to the list (first one is number 0)
void CUbqMultImage::AddImage(CUbqGameImage* pImage)
{
  m_vecImages.Add(pImage);
}

/////////////////////////////////////////////////////////////////////////////////
// is inside the object?
BOOL CUbqMultImage::IsInside(CPoint Point)
{
	return (m_rArea.PtInRect(Point));
}

//////////////////////////////////////////////////////////////////////////////////
// set the status/gif
void CUbqMultImage::SetStatus(int Status)
{ 	
	ASSERT(Status < m_vecImages.GetSize());
	
	CObject* Object;
	Object = m_vecImages.GetAt(Status);	
  ASSERT(Object);

	m_pCurrImage = (CUbqGameImage*) Object;
	m_iStatus = Status;
  m_pGameBoard->OnMultiImageChange(this);
}

void CUbqMultImage::ChangePos(CPoint Point)
{
  CRect OldRect=m_rArea;
  Point.Offset(-OldRect.TopLeft());
  m_rArea.OffsetRect(Point);
  m_pGameBoard->PostPaintEvent(OldRect);
  m_pGameBoard->PostPaintEvent(m_rArea);
}
