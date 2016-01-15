#define MAX_ANIMS 30

class CAnimTimer
{
  UINT m_uTimerId;
  CObject*  m_vecAnims[MAX_ANIMS];
  HWND m_hWnd;
  class CVctApplet * m_pApplet;

  public:

  CAnimTimer() {}
  ~CAnimTimer() {}

  void Init(HWND hwnd, class CVctApplet* Applet);                 //start the timer
                               // callback to the timer
  void Stop();                 //stop the timer

  void OnTimerTick();

  void AddAnim(CObject* obj,BOOL AddOnTop);

  void RemoveAnim(CObject* obj);
};

extern CAnimTimer AnimTimer;
