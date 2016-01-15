// Game Piece implementation 

#include "stdafx.h"
#include "GameImg.h"
#include "GamePce.h"
#include <stdlib.h>

CUbqGamePiece::CUbqGamePiece(int id, int type, int Shape,CUbqGameImage* pImage, int attr, CRect Area)
{
  this->id = id;
  this->type = type;
  this->m_nShape = Shape;
  this->m_pImage = pImage;
  this->attr = attr;
  this->m_rArea = Area;

  if (m_nShape)
  {
    m_nXRadiusSquare = (m_rArea.Width()/2)*(m_rArea.Width()/2);
    m_nYRadiusSquare = (m_rArea.Height()/2)*(m_rArea.Height()/2);
  }
}

CUbqGamePiece::~CUbqGamePiece()
{
}

/**
* Check if a point of the board is inside a piece.
*/
BOOL CUbqGamePiece::IsInside(CPoint Point)
{
  if (m_nShape)
  {
    long dx = abs(m_rArea.left+(m_rArea.Width()/2)-Point.x);
    long dy = abs(m_rArea.top+(m_rArea.Height()/2)-Point.y);
	return ((double)((dx*dx)/(m_nXRadiusSquare)) + (double((dy*dy)/(m_nYRadiusSquare))) < 1);
  }
  else
  {
    return m_rArea.PtInRect(Point);
  }
}
