#include "stdafx.h"
#include <picture.h>

#include "canitime.h"
#include "Canim.h"

#include "GameImg.h"
#include "GamePce.h"
#include "GameSlot.h"
#include "GameArea.h"
#include "GameBrd.h"

#include "GameApp.h"
#include "VctComm.h"
#include "GameText.h"

#include "VctApp.h"

#include <mmsystem.h>

#ifdef WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


void CAnimTimer::Init(HWND hwnd, class CVctApplet* applet)
{
  m_hWnd=hwnd;
  m_uTimerId=SetTimer(hwnd,1,80,NULL);
  ASSERT(m_uTimerId);
  m_pApplet = applet;

  for (int i=0;i<MAX_ANIMS;i++)
	m_vecAnims[i]=NULL;
}


void CAnimTimer::Stop()
{
  KillTimer(m_hWnd,m_uTimerId);
}

void CAnimTimer::AddAnim(CObject* obj,BOOL AddOnTop)
{
  if (AddOnTop)
  {
    for (int i=MAX_ANIMS-1;i>=0;i--)
      if (m_vecAnims[i]==NULL)
      {
        m_vecAnims[i]=obj;
    	  break;
      }
  }
  else
  {
    for (int i=0;i<MAX_ANIMS;i++)
    	if (m_vecAnims[i]==NULL)
      {
        m_vecAnims[i]=obj;
    	  break;
      }
  }
}

void CAnimTimer::RemoveAnim(CObject* obj)
{
  BOOL found=FALSE;

  for (int i=0;i<MAX_ANIMS;i++)
    if (m_vecAnims[i]==obj)
    {
	  m_vecAnims[i]=NULL;
	  found=TRUE;
	  break;
    }

  if (!found)
	ASSERT(0);
}


void CAnimTimer::OnTimerTick()
{
  CObject*  newvec[MAX_ANIMS];
  CAnim*   Anim;

  for (int i=0;i<MAX_ANIMS;i++)
	newvec[i]=m_vecAnims[i];

  for (i=0;i<MAX_ANIMS;i++)
  if (newvec[i]!=NULL)
  {
	Anim=(CAnim*)newvec[i];
	Anim->NextFrame();
  }

  m_pApplet->GameLoop();  //General stuff
}

