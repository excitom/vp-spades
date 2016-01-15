// Game Board Slot implementation 

#include "stdafx.h"
#include "GameSlot.h"
#include <stdlib.h>

CUbqGameBoardSlot::CUbqGameBoardSlot(int id, CPoint Point)
{
  this->id = id;
  this->m_ptCoord = Point;    
}


CUbqGameBoardSlot::~CUbqGameBoardSlot()
{
}

DWORD CUbqGameBoardSlot::Distance(CPoint Point)
{
  int dx = abs(Point.x-m_ptCoord.x);
  int dy = abs(Point.y-m_ptCoord.y);
  return ((DWORD)dx*dx+dy*dy);
}
