#include "stdafx.h"

#include "canitime.h"
#include "canim.h"

#include "GameImg.h"
#include "GamePce.h"
#include "GameSlot.h"
#include "GameArea.h"
#include "GameBrd.h"
#include "GameMim.h"
#include "GameApp.h"
#include "GameText.h"

#include "VctApp.h"

#include "bmp.h"

#ifdef WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

int       CAnim::m_aPictUsageCount[MAX_ANIM_GIFS];
UINT      CAnim::m_aPictName[MAX_ANIM_GIFS];
CBitmap*  CAnim::m_aMaskBitmaps[MAX_ANIM_GIFS];
CBitmap*  CAnim::m_aBitmaps[MAX_ANIM_GIFS];
CSize     CAnim::m_aBitmapSize[MAX_ANIM_GIFS];
CWnd*     CAnim::m_pWnd;


CAnim::CAnim(CWnd* wnd)
{
  m_pBitmap=NULL;
  m_pWnd=wnd;
  m_bPlaying=FALSE;
  m_pMaskBitmap=NULL;
  m_pBackgroundBitmap=NULL;
}

CAnim::~CAnim()
{
  Close(FALSE,FALSE);
}


void CAnim::Play(UINT AnimName,CRect rect,BOOL Static,int Loop,BOOL Transparent,int Rate,
                 CPoint Dest,short FuncIndex,BYTE* CBParam,int ParamSize,CRect BackAnim,
                 int LoopStartFrame, int Frames)
{
  if (Rate != 6 && Rate != 12)
  {
    //the animation can play only in 6.25 and 12.5 fps
    ASSERT(0);
  }

  m_nRate = Rate;
  m_bSkipFrame = TRUE;

  if (m_bPlaying)
  {
      Close (TRUE,TRUE);
  }

  m_bPlaying=TRUE;

  //load the bitmap    from gif
  m_pBitmap=NULL;

  int PictNum=FindPicture(AnimName);

  if (PictNum!=-1)
  {
    m_pBitmap=m_aBitmaps[PictNum];
    m_nBMWidth =m_aBitmapSize[PictNum].cx;
    m_nBMHeight=m_aBitmapSize[PictNum].cy;
    m_aPictUsageCount[PictNum]++;
  }
  else
  {
    BITMAP      mybm;
    LoadPicture(AnimName);
    m_pBitmap->GetObject(sizeof(BITMAP),&mybm);
    m_nBMWidth=mybm.bmWidth;
    m_nBMHeight=mybm.bmHeight;
  }

  ASSERT(m_pBitmap);

  //if transparent make the mask bitmap
  if (Transparent)
  {
    if (PictNum == -1 || m_aMaskBitmaps[PictNum]==NULL)
    {
      CDC  BmpDC;
      CDC  MaskDC;

      BmpDC.CreateCompatibleDC(NULL);
      COLORREF BgColor=BmpDC.SetBkColor(RGB(0,0,0));
      CBitmap * pOldBmp=BmpDC.SelectObject(m_pBitmap);

      m_pMaskBitmap=new(CBitmap);
      m_pMaskBitmap->CreateBitmap(((m_nBMWidth+7)/8)*8,
                                    ((m_nBMHeight+7)/8)*8,
                                    1,1,NULL);
      MaskDC.CreateCompatibleDC(NULL);
      CBitmap * pOldmask=MaskDC.SelectObject(m_pMaskBitmap);
      BOOL ret5=MaskDC.BitBlt(0,0,
                                m_nBMWidth,
                                m_nBMHeight,
                                &BmpDC,0,0,SRCCOPY);

      MaskDC.SelectObject(pOldmask);
      BmpDC.SetBkColor(BgColor);
      BmpDC.SelectObject(pOldBmp);
    }
    else
    {
      ASSERT(m_aMaskBitmaps[PictNum]);
      m_pMaskBitmap=m_aMaskBitmaps[PictNum];
    }

    if (Static)
    {
       CDC*    pDC;
       CDC  BackgroundDC;
       CDC  BackImageDC;
       CBitmap* pBackImage;
       CUbqGamePiece* p;
       CUbqMultImage* m;
       CObject* o;

       pDC=m_pWnd->GetDC();

       CPalette* OldPal= pDC->SelectPalette(&(CBmp::m_cPalette),FALSE);
       pDC->RealizePalette();

       BackgroundDC.CreateCompatibleDC(pDC);
       BackImageDC.CreateCompatibleDC(pDC);
       m_pBackgroundBitmap=new(CBitmap);
       m_pBackgroundBitmap->CreateCompatibleBitmap(pDC,
                                                   rect.Width(),
                                                   rect.Height());

       CBitmap* pOldBg =BackgroundDC.SelectObject(m_pBackgroundBitmap);

       //copying the background image
       pBackImage=&((CUbqGameBoard*)m_pWnd)->m_cBoardBmp;
       //pBackImage=((CUbqGameBoard*)m_pWnd)->m_pImageBoard->m_picture.GetBitmap();

       CBitmap* pOldBg2=BackImageDC.SelectObject(pBackImage);

       BOOL ret=BackgroundDC.BitBlt(0,0,
                              rect.Width(),
                              rect.Height(),
                              &BackImageDC,
                              rect.left,
                              rect.top,
                              SRCCOPY);

       BackImageDC.SelectObject(pOldBg2);

       //copying the pieces
       int size = ((CUbqGameBoard*)m_pWnd)->m_vecPieces.GetSize();
       for (int i=0; i<size; i++)  // bottom to top to preserve Z order
       {
         o = ((CUbqGameBoard*)m_pWnd)->m_vecPieces.GetAt(i);
         p = (CUbqGamePiece*) o;
         if ((p->GetAttribute() & PA_INVISIBLE) == 0 && ( p != ((CUbqGameBoard*)m_pWnd)->m_pDraggedPiece ))
         {
           CRect  rIntersect;
           if (rIntersect.IntersectRect(rect,p->m_rArea))
           {
             CPoint ap=p->m_rArea.TopLeft();
#ifdef WIN32
             ap-=rect.TopLeft();
#else
             ap.x-=rect.TopLeft().x;
             ap.y-=rect.TopLeft().y;
#endif
             (((CUbqGameBoard*)m_pWnd)->m_pApplet)->DrawImage(p->m_pImage,ap,BackgroundDC);
           }
         }
       }

       //copying the multi images
       size = ((CUbqGameBoard*)m_pWnd)->m_vecMultipleImages.GetSize();
       for (i=0; i<size; i++)  // bottom to top to preserve Z order
       {
         o = ((CUbqGameBoard*)m_pWnd)->m_vecMultipleImages.GetAt(i);
         m = (CUbqMultImage*) o;

         CRect  rIntersect;
         if (rIntersect.IntersectRect(rect,m->m_rArea))
         {
           CPoint ap=m->m_rArea.TopLeft();
#ifdef WIN32
           ap-=rect.TopLeft();
#else
           ap.x-=rect.TopLeft().x;
           ap.y-=rect.TopLeft().y;
#endif
           (((CUbqGameBoard*)m_pWnd)->m_pApplet)->DrawImage(m->GetCurrImage(),ap,BackgroundDC);
         }
       }

       BackgroundDC.SelectObject(pOldBg);

       pDC->SelectPalette(OldPal,FALSE);
       pDC->RealizePalette();

       m_pWnd->ReleaseDC(pDC);
    }
  }

  //save parameters
  m_rArea=rect;
  m_cEndPoint=Dest;
  m_cCurrPoint=m_cStartPoint=rect.TopLeft();
  m_bStatic=Static;
  m_nLoopStartFrame = LoopStartFrame;
  m_nLoops=Loop;
  if (m_nLoops==0)  //loops 0 is realy 1
    m_nLoops++;
  if (m_nLoops!=1 && !m_bStatic)
    ASSERT(0);
  m_nFuncIndex = FuncIndex;
  m_bTransparent=Transparent;
  if (ParamSize>0)
  {
     m_nCBParamSize=ParamSize;
     m_pCBParam=new BYTE[ParamSize];
     if (!m_pCBParam)
       ASSERT(0);
     memcpy(m_pCBParam,CBParam,ParamSize);
  }
  else
    m_pCBParam=NULL;
  m_rBackAnim=BackAnim;

  //add to list of gifs
  if (PictNum == -1)
  {
    BOOL Found=FALSE;
    for(int i=0;i<MAX_ANIM_GIFS && !Found;i++)
    {
      if (m_aPictName[i]==0)
      {
        m_aPictName[i]=AnimName;
          Found=TRUE;
          m_aPictUsageCount[i]=1;
        m_aBitmaps[i]=m_pBitmap;
        PictNum=i;
      }
    }
  }
  if (m_aMaskBitmaps[PictNum] == NULL && m_pMaskBitmap != NULL) //this is done here due to preloaded bitmaps
    m_aMaskBitmaps[PictNum]=m_pMaskBitmap;

  //do some calculations ...
  if (Frames)
  {
    m_nLastFrame=Frames;
    m_bOneFrame=TRUE;
  }
  else
  {
    m_nLastFrame=m_nBMHeight/m_rArea.Height();
    m_bOneFrame=FALSE;
  }
  m_nFrame=0;
  m_bClosing=FALSE;

  // draw the first frame
  NextFrame();

  //register the animation vector
  AnimTimer.AddAnim((CObject *)this,BackAnim!=CRect(0,0,0,0));
}

void CAnim::NextFrame()
{
  CDC* pDC;
  CDC  BmpDC;
  int FramePos;

  if (m_bClosing)
    return ;

  if (m_nRate == 6 && m_bSkipFrame)
  {
      m_bSkipFrame = FALSE;
      return;
  }

  m_bSkipFrame = TRUE;

  CPoint OffSet;
  OffSet.x=((CUbqGameBoard*)m_pWnd)->GetScrollRect().TopLeft().x+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint().x;
  OffSet.y=((CUbqGameBoard*)m_pWnd)->GetScrollRect().TopLeft().y+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint().y;

  //if this is not static then delete the old frame;
  if (!m_bStatic && m_nFrame)
  {
    if (m_rBackAnim==CRect(0,0,0,0))
    {
      m_pWnd->InvalidateRect(m_rArea+m_cCurrPoint-m_cStartPoint+OffSet,FALSE);
      m_pWnd->UpdateWindow();
    }
    else
    {
#ifdef WIN32
      CRect r=m_rArea+(m_cCurrPoint-m_cStartPoint);
#else
      CRect r=m_rArea+m_cCurrPoint-m_cStartPoint;
#endif
      CRect r2;
      if (r2.IntersectRect(&r,&m_rBackAnim))
      {
        if (r2 != r)
        {
          CRect r3;
          BOOL ret=r3.SubtractRect(r,r2);
          ASSERT(ret);

          //r.=CPoint(LPCRECT(r2)->right-LPCRECT(r2)->left,0);
          m_pWnd->InvalidateRect(r+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint(),FALSE);
          m_pWnd->UpdateWindow();
        }
      }
      else
      {
        m_pWnd->InvalidateRect(r+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint(),FALSE);
        m_pWnd->UpdateWindow();
      }
    }
  }

  //if this is the last frame the close the animation
  if (m_nFrame == m_nLastFrame)
  {
    if (m_nLoops == -1)
      m_nFrame=m_nLoopStartFrame;
    else
    {
      m_nLoops--;
      if (m_nLoops==0)
      {
        Close(TRUE,TRUE);
         return;
      }
      else
        m_nFrame=m_nLoopStartFrame;
    }
  }

  if (!m_bStatic)
  {
    m_cCurrPoint.x=m_cStartPoint.x+m_nFrame*((m_cEndPoint.x-m_cStartPoint.x)/(m_nLastFrame-1));
    m_cCurrPoint.y=m_cStartPoint.y+m_nFrame*((m_cEndPoint.y-m_cStartPoint.y)/(m_nLastFrame-1));
  }

  // draw the next frame
  if (!m_pWnd)
  {
    ASSERT(0);
    return;
  }
  if (!IsWindow(m_pWnd->GetSafeHwnd()))
  {
    ASSERT(0);
    return;
  }

  if (!m_bOneFrame)
    FramePos=m_nFrame;
  else
    FramePos=0;

  pDC=m_pWnd->GetDC();
  ASSERT(pDC);
  CPalette* OldPal= pDC->SelectPalette(&(CBmp::m_cPalette),FALSE);
  pDC->RealizePalette();

  BmpDC.CreateCompatibleDC(pDC);
  CBitmap * pOldBmp=BmpDC.SelectObject(m_pBitmap);

  long DrawOffsetx,DrawOffsety;
  if (m_cCurrPoint.x<0)
  {
    DrawOffsetx=-m_cCurrPoint.x;
    OffSet.x-=m_cCurrPoint.x;
  }
  else
    DrawOffsetx=0;
  if (m_cCurrPoint.y<0)
  {
    DrawOffsety=-m_cCurrPoint.y;
    OffSet.y-=m_cCurrPoint.y;
  }
  else
    DrawOffsety=0;



  if (m_bTransparent)
  {
    CDC  MaskDC;
    MaskDC.CreateCompatibleDC(pDC);
    CBitmap * pOldMask=MaskDC.SelectObject(m_pMaskBitmap);

    if (m_bStatic)
    {
      CBitmap Temp;
      CDC TempDC;
      CDC BackgroundDC;

      TempDC.CreateCompatibleDC(pDC);
      BackgroundDC.CreateCompatibleDC(pDC);

      Temp.CreateCompatibleBitmap(pDC,
                                  m_rArea.Width(),
                                  m_rArea.Height());

      CBitmap* pOldTemp=TempDC.SelectObject(&Temp);
      CBitmap* pOldBg=BackgroundDC.SelectObject(m_pBackgroundBitmap);

      TempDC.BitBlt(0,0,
                    m_rArea.Width(),
                    m_rArea.Height(),
                    &BackgroundDC,
                       0,
                    0,
                       SRCCOPY);

      BackgroundDC.SelectObject(pOldBg);

      TempDC.BitBlt(0,0,
                    m_rArea.Width(),
                    m_rArea.Height(),
                       &MaskDC,
                    0,
                       FramePos*m_rArea.Height(),
                       SRCAND);

      TempDC.BitBlt(0,0,
                    m_rArea.Width(),
                    m_rArea.Height(),
                    &BmpDC,
                    0,
                       FramePos*m_rArea.Height(),
                       SRCPAINT);

      pDC->BitBlt(m_cCurrPoint.x+OffSet.x,
                  m_cCurrPoint.y+OffSet.y,
                  m_rArea.Width(),
                  m_rArea.Height(),
                  &TempDC,
                  DrawOffsetx,
                  DrawOffsety,
                  SRCCOPY);

      TempDC.SelectObject(pOldTemp);

      Temp.DeleteObject();
    }
      else
    {
      pDC->BitBlt(m_cCurrPoint.x+OffSet.x,
                  m_cCurrPoint.y+OffSet.y,
                  m_rArea.Width(),
                  m_rArea.Height(),
                  &MaskDC,
                  DrawOffsetx,
                  FramePos*m_rArea.Height()+DrawOffsety,
                  SRCAND);

      pDC->BitBlt(m_cCurrPoint.x+OffSet.x,
                  m_cCurrPoint.y+OffSet.y,
                  m_rArea.Width(),
                  m_rArea.Height(),
                  &BmpDC,
                  DrawOffsetx,
                  FramePos*m_rArea.Height()+DrawOffsety,
                  SRCPAINT);
    }
    MaskDC.SelectObject(pOldMask);

  }
  else
  {
    pDC->BitBlt(m_cCurrPoint.x+OffSet.x,
                m_cCurrPoint.y+OffSet.y,
                 m_rArea.Width(),
                 m_rArea.Height(),
                 &BmpDC,
                 DrawOffsetx,
                 FramePos*m_rArea.Height()+DrawOffsety,
                 SRCCOPY);
  }


  BmpDC.SelectObject(pOldBmp);

  pDC->SelectPalette(OldPal,FALSE);
  pDC->RealizePalette();

  m_pWnd->ReleaseDC(pDC);

  m_nFrame++;

  return;
}

void CAnim::Close(BOOL Callback , BOOL Repaint)
{
  if (!m_bPlaying)
    return;
  m_bClosing=TRUE;

  //delete the bitmap
  BOOL Found=FALSE;

  for(int i=0;i<MAX_ANIM_GIFS && !Found;i++)
  {
    if (m_pBitmap==m_aBitmaps[i])
    {
      Found=TRUE;
      m_aPictUsageCount[i]--;
      if (m_aPictUsageCount[i]==0)
      {
        m_aPictName[i]=0;
          m_pBitmap->DeleteObject();
        delete(m_pBitmap);
        m_aBitmaps[i]=NULL;
        if (m_bTransparent)
        {
          m_pMaskBitmap->DeleteObject();
          delete(m_pMaskBitmap);
          m_aMaskBitmaps[i]=NULL;
        }
      }
    }
  }

  m_pBitmap=NULL;

  if (m_bTransparent)
  {
    m_pMaskBitmap=NULL;
    if (m_bStatic)
    {
      m_pBackgroundBitmap->DeleteObject();
      delete(m_pBackgroundBitmap);
      m_pBackgroundBitmap=NULL;
    }
  }
  //delete the timer registration
  AnimTimer.RemoveAnim((CObject *)this);

  //post paint message
  if (m_bStatic )
  {
    if (Repaint && m_pWnd->m_hWnd && IsWindow(m_pWnd->m_hWnd))
      m_pWnd->InvalidateRect(m_rArea+((CUbqGameBoard*)m_pWnd)->GetScrollRect().TopLeft()+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint(),FALSE);
  }
  else
  {
    if (Repaint && m_pWnd->m_hWnd && IsWindow(m_pWnd->m_hWnd))
      m_pWnd->InvalidateRect(m_rArea+m_cCurrPoint-m_cStartPoint+((CUbqGameBoard*)m_pWnd)->GetScrollRect().TopLeft()+((CUbqGameBoard*)m_pWnd)->GetOffsetPoint(),FALSE);
  }

  m_bPlaying=FALSE;

  if (Callback && m_nFuncIndex != 0 )
    ((CVctApplet *)(((CUbqGameBoard*)m_pWnd)->m_pApplet))->AnimCallback(m_nFuncIndex, m_pCBParam,m_nCBParamSize,m_nID);
  if (m_pCBParam != NULL)
  {
    delete(m_pCBParam);
    m_pCBParam=NULL;

  }
}

  void CAnim::LoadPicture (UINT AnimName)
  {
    m_pBitmap=new(CBitmap);
    CBmp::ReadBmp(m_pBitmap,AnimName,m_pWnd);
  }

  int  CAnim::FindPicture(UINT AnimName)
  {
    for(int i=0;i<MAX_ANIM_GIFS && m_pBitmap==NULL;i++)
    {
      if (AnimName==m_aPictName[i])
        return i;
    }
    return -1;
  }

  void  CAnim::Load(UINT AnimName)
  {
    BOOL Found=FALSE;
    for(int i=0;i<MAX_ANIM_GIFS && !Found;i++)
    {
      if (m_aPictName[i]==0)
      {
        BITMAP      mybm;
        LoadPicture(AnimName);
        m_aPictName[i]=AnimName;
        m_aBitmaps[i]=m_pBitmap;
        Found=TRUE;
        m_aPictUsageCount[i]=10000;
        m_pBitmap->GetObject(sizeof(BITMAP),&mybm);
        m_aBitmapSize[i].cx=mybm.bmWidth;
        m_aBitmapSize[i].cy=mybm.bmHeight;
        m_aMaskBitmaps[i]=NULL;
      }
    }
  }

  void CAnim::ReleaseAll()
  {
    for(int i=0;i<MAX_ANIM_GIFS ;i++)
    {
      if (m_aBitmaps[i])
      {
        delete  m_aBitmaps[i];
        m_aBitmaps[i]=NULL;
        if (m_aMaskBitmaps[i])
        {
          delete  m_aMaskBitmaps[i];
          m_aMaskBitmaps[i]=NULL;
        }
      }
    }
  }

  void CAnim::InitAll()
  {
    for(int i=0;i<MAX_ANIM_GIFS ;i++)
    {
      m_aPictUsageCount[i]=0;
      m_aPictName[i]=0;
      m_aMaskBitmaps[i]=NULL;
      m_aBitmaps[i]=NULL;
      m_aBitmapSize[i]=CSize(0,0);
    }
  }

  void CAnim::RereadAllBitmaps()
  {
    for(int i=0;i<MAX_ANIM_GIFS ;i++)
    {
      if (m_aBitmaps[i] && m_aPictName[i])
      {
        m_aBitmaps[i]->DeleteObject();
        CBmp::ReadBmp(m_aBitmaps[i],m_aPictName[i],m_pWnd);
      }
    }
  }
