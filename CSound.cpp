#include "stdafx.h"

#include "CSound.h"

#include <mmsystem.h>

#ifdef WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

void CSound::Mute()
{
  m_bMute=TRUE;
  Stop();
}

void CSound::UnMute()
{
  m_bMute=FALSE;
}

void CSound::Stop()
{
  BOOL ret=sndPlaySound(NULL,SND_ASYNC);
}

void CSound::Play(char * WavName,BOOL priority)
{
  if (m_bMute)
	return;

  ///find and lock the  wav
  HINSTANCE hInst = AfxGetInstanceHandle();

  HRSRC hResInfo = FindResource(hInst, WavName, "WAVSOUND");
  if (hResInfo == NULL)
  {
  	return;
  }

  HGLOBAL hRes = LoadResource(hInst, (HRSRC)hResInfo);
  if (hRes == NULL)
  {
  	return;
  }

  LPBYTE lpRes = (LPBYTE)LockResource(hRes);
  if (lpRes == NULL)
  {
  	return;
  }

  //play the wav

  UINT Flags=SND_ASYNC|SND_NODEFAULT|SND_MEMORY;

  if (!priority)
	Flags|=SND_NOSTOP;

  BOOL ret=sndPlaySound((LPCSTR)lpRes,Flags);

  UnlockResource(hRes);
  FreeResource(hRes);
  hRes = NULL;
}

