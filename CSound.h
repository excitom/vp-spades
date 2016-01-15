#ifndef   __CSOUND_H_
#define  __CSOUND_H_

class CSound
{
  BOOL m_bMute;

  public:

  CSound()  {}  
  ~CSound() {}

  void  Init()
  {
	m_bMute=FALSE;
  }

  void  Mute();                   

  void  UnMute();                

  void  Stop();                  

  void  Play(char * WavName,BOOL priority=TRUE);

  BOOL  IsMuted() { return m_bMute; }

};

#endif   // __CSOUND_H_



