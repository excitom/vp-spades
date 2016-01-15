#ifndef   __CMIDI_H_
#define  __CMIDI_H_

class CMidi
{
  BOOL    m_bMidiInitialized;
  UINT    m_uMCIDeviceID;   // MCI Device ID
  BOOL    m_bMidiIsPlaying;
  BOOL    m_bMute;
  HWND    m_hwndToNotify;
  CString m_sLastMidi;
  CString m_sMidiFile;


  void  Close();                 //stop; restart only from begginig

  void  MciPlay();

  void  MciStop();

  void  PlayFile();             // play a module from the beggining

public:
	LRESULT CallBack(WPARAM wFlags,LPARAM lDevID);


  CMidi();

  ~CMidi();

  void  Init(HWND hWnd);                 // play a module from the beggining

  void  Play(char * MidiName);  // play a module from the beggining

  void  Mute() ;                // pause a module

  void  UnMute();               // continue playing after p.ause

  void  Stop();                 //stop; restart only from begginig

  void  UnInit(); 

};

#endif   // __CMIDI_H_
