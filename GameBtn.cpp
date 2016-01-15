// Game Board Button implementation 

#include "stdafx.h"
#include "GameApp.h"
#include "GameBrd.h"
#include "GameImg.h"
#include "GameMIm.h"
#include "GameBtn.h"
#include <stdlib.h>


/*-----------------------------------*/
/*-----------------------------------*/
CUbqGameButton::CUbqGameButton(int id, CRect Area, CUbqGameBoard*  pBoard,BOOL IsToggle): 
  CUbqMultImage(Area, pBoard)
{
	m_id = id;
	m_bIsToggle = IsToggle;
	m_nToggleFrame = 0;
}


/*-----------------------------------*/
/*-----------------------------------*/
CUbqGameButton::~CUbqGameButton()
{
}


/*-----------------------------------*/
/*-----------------------------------*/
void CUbqGameButton::MouseUp()
{
  if (IsDisabled()) 
	return;

  if (!m_bIsToggle)
    SetStatus(BTN_UP_FOCUS);
  else
  {
	 SetToggle (m_nToggleFrame==2);  // switch the toggle.
	 SetStatus (TOGGLE_FOCUS + m_nToggleFrame);
  }

} 

/*-----------------------------------*/
/*-----------------------------------*/
void CUbqGameButton::MouseDown()
{ 
  if (IsDisabled())  
	  return;

  if (!m_bIsToggle)
    SetStatus(BTN_DOWN); 
}

/*-----------------------------------*/
/*-----------------------------------*/
void CUbqGameButton::SetDisabled(BOOL bIsDisbled) 
{
  if (bIsDisbled) 
  {
	if (m_bIsToggle)
      SetStatus(TOGGLE_DISABLED);
	else
      SetStatus(BTN_DISABLED);
  }
  else
  {
	if (m_bIsToggle)
      SetStatus(TOGGLE_NO_FOCUS + m_nToggleFrame);
	else
      SetStatus(BTN_UP_NO_FOCUS);
  }
}

/*-----------------------------------*/
/*-----------------------------------*/
void CUbqGameButton::SetEnabledInFocus()
{
   if (m_bIsToggle)
     SetStatus(TOGGLE_NO_FOCUS + m_nToggleFrame);
   else
     SetStatus(BTN_UP_NO_FOCUS);

   SetInFocus(TRUE);
}

/*-----------------------------------*/
/*-----------------------------------*/
void CUbqGameButton::SetInFocus(BOOL focus)
{
  if (focus && !IsUpNoFocus()) return;
  if (!focus && IsDisabled()) return;

  if (m_bIsToggle)
  {
    if (focus)
      SetStatus(TOGGLE_FOCUS + m_nToggleFrame);
    else
      SetStatus(TOGGLE_NO_FOCUS + m_nToggleFrame);
  }
  else
  {
    if (focus)
      SetStatus(BTN_UP_FOCUS);
    else
      SetStatus(BTN_UP_NO_FOCUS);
  }
}

 
 
 
