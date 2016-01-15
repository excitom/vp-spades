#ifndef __CANIM_H__
#define __CANIM_H__

#define MAX_ANIM_GIFS   20

class CAnim	: public CObject
{
  CRect       m_rArea;
  BOOL        m_bStatic;
  int         m_nRate;
  BOOL        m_bSkipFrame;
  CBitmap*    m_pBitmap;
  CBitmap*    m_pMaskBitmap;
  CBitmap*    m_pBackgroundBitmap;
  int         m_nLastFrame,m_nFrame;
  CPoint      m_cStartPoint,m_cCurrPoint,m_cEndPoint;
  BOOL        m_bPlaying;
  int         m_nLoops;  // 0-no loops, -1 infinite ,positive - number of loops
  int         m_nLoopStartFrame;
  BOOL        m_bTransparent;
  short       m_nFuncIndex;
  BYTE*       m_pCBParam;
  int         m_nCBParamSize;
  CRect       m_rBackAnim;
  long		  m_nID;
  BOOL        m_bClosing;
  int         m_nBMWidth;
  int         m_nBMHeight;
  BOOL        m_bOneFrame;

  static CWnd*	   m_pWnd;

  static  int      m_aPictUsageCount[MAX_ANIM_GIFS];
  static UINT      m_aPictName[MAX_ANIM_GIFS];
  static CBitmap*  m_aMaskBitmaps[MAX_ANIM_GIFS];
  static CBitmap*  m_aBitmaps[MAX_ANIM_GIFS];
  static CSize     m_aBitmapSize[MAX_ANIM_GIFS];

  void LoadPicture (UINT AnimName);

  int FindPicture (UINT AnimName);

public:

  CAnim(CWnd* wnd);

  ~CAnim();

  void Play(UINT AnimName,CRect rect,BOOL Static=TRUE,int Loop=0,BOOL Transparent=FALSE,
	        int Rate=12,CPoint Dest=CPoint(0,0),
			short FuncIndex=0,BYTE* CBParam=NULL,int ParamSize=0,
			CRect BackAnim=CRect(0,0,0,0), int LoopStartFrame=0,int Frames=0);

  void NextFrame();

  void  SetID (long id) {m_nID = id;}
  long  GetID ()        {return m_nID;}

  void  Close(BOOL Callback = FALSE, BOOL Repaint = TRUE);

  void Load(UINT AnimName);

  static void ReleaseAll();

  static void InitAll();

  static void RereadAllBitmaps();

  BOOL IsPlaying()
  {
	return m_bPlaying;
  }
};

#endif __CANIM_H__

