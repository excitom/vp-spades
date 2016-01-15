#include "stdafx.h"

#include "cmidi.h"

#include <mmsystem.h>

#define MCI_ERROR_LENGTH 129


#ifdef WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

void CMidi::Init(HWND hWnd)
{
  m_hwndToNotify=hWnd;

  char * TempDir=getenv("TEMP");
  if (TempDir == NULL)
    TempDir=getenv("TMP");

  if (TempDir != NULL)
    m_sMidiFile=CString(TempDir)+"\\btl.rmi";
  else
    m_sMidiFile="c:\\btl.rmi";
  m_sLastMidi="";
} // ::Init

CMidi::CMidi()
{
  m_bMidiInitialized = FALSE;
  m_uMCIDeviceID=0;
  m_bMute=FALSE;
}


CMidi::~CMidi()
{
  Close();
}

void CMidi::Play(char * MidiName)
{
  if (m_sLastMidi != CString(MidiName))
  {

    HINSTANCE hInst = AfxGetInstanceHandle();

    HRSRC hResInfo = FindResource(hInst, MidiName, "MIDIMUSIC");
    if (hResInfo == NULL)
    {
      ASSERT(0);
    	return;
    }

    HGLOBAL hRes = LoadResource(hInst, (HRSRC)hResInfo);
    if (hRes == NULL)
    {
      ASSERT(0);
    	return;
    }

    LPBYTE lpRes = (LPBYTE)LockResource(hRes);
    if (lpRes == NULL)
    {
      ASSERT(0);
    	return;
    }

    FILE * pMidFile=fopen(LPCSTR(m_sMidiFile),"wb");
    int size=0,nWritten=1;
    if (pMidFile)
    {
      size=*(DWORD *)((lpRes+sizeof(DWORD)));
      size+=8;
      nWritten=fwrite(lpRes,1,size,pMidFile);
      fclose(pMidFile);
    }

    UnlockResource(hRes);
    FreeResource(hRes);
    hRes = NULL;

    m_sLastMidi = CString(MidiName);

    if (nWritten != size)
      return;
  }
  PlayFile();
}

void CMidi::PlayFile()
{

  DWORD dwReturn;
  MCI_OPEN_PARMS mciOpenParms;
  char mciErrorString[MCI_ERROR_LENGTH];
  UINT mciErrorLen;
  BOOL KnownError = FALSE;

  Close();

  mciOpenParms.lpstrDeviceType = "sequencer";
  mciOpenParms.lpstrElementName = LPCSTR(m_sMidiFile);
  if (dwReturn = mciSendCommand(NULL, MCI_OPEN,
      MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
      (DWORD)(LPVOID) &mciOpenParms))
  {
      mciErrorLen = MCI_ERROR_LENGTH;
      KnownError = mciGetErrorString(dwReturn, mciErrorString, mciErrorLen);
      TRACE("Couldn't Open Midi Device in constructor\n");
      if (KnownError)
        TRACE("MCI ERROR : %s\n", mciErrorString);
      else
        TRACE("MCI ERROR : Unknown Error (%x)!!!!! \n",dwReturn);

      // Failed to open device. Don't close it; just return error.
      m_bMidiInitialized = FALSE;
      return;
  }

  // The device opened successfully; get the device ID.
  m_uMCIDeviceID = mciOpenParms.wDeviceID;
  m_bMidiInitialized = TRUE;

  MciPlay();
}


void CMidi::Mute()
{
  m_bMute=TRUE;
  MciStop();
}

void CMidi::UnMute()
{
  m_bMute=FALSE;
  MciPlay();
}

void CMidi::Stop()
{
  Close();
}

void CMidi::Close()
{
  DWORD dwReturn;
  char mciErrorString[MCI_ERROR_LENGTH];
  UINT mciErrorLen;
  BOOL KnownError = FALSE;

  if (!m_uMCIDeviceID) return;

  MciStop();
  dwReturn =mciSendCommand(m_uMCIDeviceID, MCI_CLOSE, 0, NULL);
  if (dwReturn)
  {
    mciErrorLen = MCI_ERROR_LENGTH;
    KnownError = mciGetErrorString(dwReturn, mciErrorString, mciErrorLen);
    TRACE("Couldn't Close Midi Device \n");
    if (KnownError)
      TRACE("MCI ERROR : %s\n", mciErrorString);
    else
      TRACE("MCI ERROR : Unknown Error (%x)!!!!! \n",dwReturn);
  }
  else
    m_uMCIDeviceID=NULL;
}


void CMidi::MciStop()
{
  DWORD dwReturn;
  MCI_GENERIC_PARMS  mciGenParms;
  MCI_STATUS_PARMS   mciStatParms;

  // Error message mechanism
  char mciErrorString[MCI_ERROR_LENGTH];
  UINT mciErrorLen;
  BOOL KnownError = FALSE;

  // Check if MIDI was intialized at all
  if (!m_bMidiInitialized)
	return;

  memset(&mciStatParms,0,sizeof(mciStatParms));
  mciStatParms.dwItem = MCI_STATUS_MODE;

  if ( (dwReturn = mciSendCommand(m_uMCIDeviceID, MCI_STATUS,
        MCI_STATUS_ITEM, (DWORD) (LPMCI_STATUS_PARMS) &mciStatParms)) != 0)
  {

      mciErrorLen = MCI_ERROR_LENGTH;
      KnownError = mciGetErrorString(dwReturn, mciErrorString, mciErrorLen);
      TRACE("Couldn't Get Midi status in MidiStop\n");
      if (KnownError)
       TRACE("MCI ERROR : %s\n", mciErrorString);
      else
       TRACE("MCI ERROR : Unknown Error (%x)!!!!! \n",dwReturn);
  }

  // Check if midi is being played at all
  if (mciStatParms.dwReturn != MCI_MODE_PLAY)
    return;

  mciGenParms.dwCallback=0;

  if ( (dwReturn = mciSendCommand(m_uMCIDeviceID, MCI_PAUSE, 0L,
                (DWORD)(LPMCI_GENERIC_PARMS) &mciGenParms)) != 0)
  {

      mciErrorLen = MCI_ERROR_LENGTH;
      KnownError = mciGetErrorString(dwReturn, mciErrorString, mciErrorLen);
      TRACE("Couldn't PAUSE Midi seq. in MidiStop\n");
      if (KnownError)
       TRACE("MCI ERROR : %s\n", mciErrorString);
      else
       TRACE("MCI ERROR : Unknown Error (%x)!!!!! \n",dwReturn);

      // Failed. Close Device and return error.
      //mciSendCommand(m_uMCIDeviceID, MCI_CLOSE, 0, NULL);
      //m_uMCIDeviceID = 0;
      //m_bMidiInitialized = FALSE;
      //return FALSE;
  }

  m_bMidiIsPlaying = FALSE;
  return;
}


void CMidi::MciPlay()
{
  DWORD dwReturn;
  MCI_PLAY_PARMS     mciPlayParms;
  DWORD dwFlags = MCI_FROM | MCI_NOTIFY;

  // Error message mechanism
  char mciErrorString[MCI_ERROR_LENGTH];
  UINT mciErrorLen;
  BOOL KnownError = FALSE;

  if (!m_uMCIDeviceID || m_bMute) return;

  memset(&mciPlayParms, 0, sizeof(MCI_PLAY_PARMS));

  mciPlayParms.dwCallback=MAKELONG(m_hwndToNotify,0);

  if (dwReturn = mciSendCommand(m_uMCIDeviceID, MCI_PLAY, dwFlags,
                               (DWORD)(LPVOID) &mciPlayParms))
  {
      mciErrorLen = MCI_ERROR_LENGTH;
      KnownError = mciGetErrorString(dwReturn, mciErrorString, mciErrorLen);
      TRACE("Couldn't Play Midi seq. in PlaySequence\n");
      if (KnownError)
       TRACE("MCI ERROR : %s\n", mciErrorString);
      else
       TRACE("MCI ERROR : Unknown Error (%x)!!!!! \n",dwReturn);

      // Failed. Close Device and return error.
      mciSendCommand(m_uMCIDeviceID, MCI_CLOSE, 0, NULL);
      m_uMCIDeviceID = 0;
      m_bMidiInitialized = FALSE;
      return;
  }

  m_bMidiIsPlaying = TRUE;
}

LRESULT CMidi::CallBack(WPARAM wFlags,LPARAM lDevID)
{
  if ((wFlags & MCI_NOTIFY_SUCCESSFUL) && (UINT)lDevID == m_uMCIDeviceID)
	MciPlay();
  return 0;
}

void CMidi::UnInit()
{
  Stop();
  remove(m_sMidiFile);
}
