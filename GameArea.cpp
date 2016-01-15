// Game Board Area implementation 

#include "stdafx.h"
#include "GameSlot.h"
#include "GameArea.h"
#include <stdlib.h>

CUbqGameBoardArea::CUbqGameBoardArea(int id, CRect rArea, BOOL isSlotted)
{
  this->id = id;
  this->m_rArea = rArea;
  this->m_bIsSlotted = isSlotted;
}

CUbqGameBoardArea::~CUbqGameBoardArea()
{
  RemoveAllSlots();
}

int CUbqGameBoardArea::GetID()
{
  return id;
}

CUbqGameBoardSlot* CUbqGameBoardArea::GetBestSlot(CPoint Point)
{
  if (!m_bIsSlotted) return NULL;  // not a sloted area
  DWORD dwMinDistance = 9999;
  CUbqGameBoardSlot* best_slot = NULL;
  CUbqGameBoardSlot* s;
  CObject* o;
  DWORD d;
  int size = m_vecSlots.GetSize();
  for (int i=0; i<size; i++)
  {
    o = m_vecSlots.GetAt(i);
    s = (CUbqGameBoardSlot*) o;
    d = s->Distance(Point);
    if (d < dwMinDistance)
    {
      best_slot = s;
      dwMinDistance = d;
    }
  }
  return (best_slot);
}

void CUbqGameBoardArea::RemoveAllSlots()
{
  while (m_vecSlots.GetSize() > 0)
  {
    CObject* o = m_vecSlots.GetAt(0);
    CUbqGameBoardSlot* s;
    s = (CUbqGameBoardSlot*) o;
    delete s;
    m_vecSlots.RemoveAt(0);
  }
}

BOOL CUbqGameBoardArea::IsInside(CRect rArea)
{
  return (m_rArea.PtInRect(rArea.BottomRight()) && m_rArea.PtInRect(rArea.TopLeft()));  
}

BOOL CUbqGameBoardArea::AddSlot(CUbqGameBoardSlot* slot)
{
  if (!m_bIsSlotted) return FALSE;
  m_vecSlots.Add(slot);  
  return (TRUE);
}
 
BOOL CUbqGameBoardArea::RemoveSlot(int id)
{
  if (!m_bIsSlotted) return FALSE;
  CObject* o; 
  CUbqGameBoardSlot* s;
  BOOL found = FALSE;
  int size = m_vecSlots.GetSize();
  for (int i=0; i<size; i++)
  {
    o = m_vecSlots.GetAt(i);
    s = (CUbqGameBoardSlot*) o;
    if (s->id == id)
    {
      delete s;
      m_vecSlots.RemoveAt(i);
      found = TRUE;
      break;
    }
  }
  return (found);
}

