#include "stdafx.h"
#include "bmp.h"

int palcolors[256 * 3] = {
	  0,   0,   0,
	 16,  16,   0,
	 49,  33,   0,
	 49,  49,  49,
	 57,  49,   0,
	 66,   0,   0,
	 66,  57,  33,
	 74,  74,  74,
	 82,  66,   0,
	 99,  82,   0,
	 99,  99,  99,
	115,  90,   0,
	132,   0,   0,
	140, 140, 140,
	148, 115,   0,
	173, 132,   0,
	189, 148,   0,
	189, 189, 189,
	198,   0,   0,
	206, 165,   0,
	222, 222, 222,
	231,   0,   0,
	231, 173,   0,
	231, 181,   0,
	239, 107,   0,
	247,  57,   0,
	247, 148,   0,
	247, 198,   0,
	255,   0,   0,
	255,  99,   0,
	255, 206,   0,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255 
};

CPalette CBmp::m_cPalette;

void CBmp::Init()
{
  BYTE logp[sizeof(LOGPALETTE)+256*sizeof(PALETTEENTRY)];
  LOGPALETTE* LogPal;
  int i;

  LogPal=(LOGPALETTE*)logp;

  LogPal->palVersion=0x300;
  LogPal->palNumEntries=256;
  for (i=0;i<256;i++)
  {
    LogPal->palPalEntry[i].peRed  =palcolors[i*3];
    LogPal->palPalEntry[i].peGreen=palcolors[i*3+1];
    LogPal->palPalEntry[i].peBlue =palcolors[i*3+2];
    LogPal->palPalEntry[i].peFlags=0;
  }
  m_cPalette.CreatePalette(LogPal);
}


void CBmp::UnInit()
{
  m_cPalette.DeleteObject();
}

int CBmp::ReadBmp(CBitmap* pBitmap,UINT Name,CWnd* Wnd)
{
  HRSRC    hrsrc;
  LPSTR    lpBits;
  HGLOBAL  hglb;
  void FAR *         prsrc;
  LPBITMAPINFOHEADER lpInfo;
  HBITMAP hBitmap;
  CDC      BmSrcDC;
  CDC      BmDstDC;
  CPalette* OldPal;
  CDC*     dc;

  hrsrc   = (HRSRC)     FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(Name), (LPCSTR)RT_BITMAP);
  hglb    = (HGLOBAL)   LoadResource(AfxGetInstanceHandle(), (HRSRC) hrsrc);
  prsrc   = (void FAR*) LockResource((HGLOBAL)hglb);

  if (!prsrc)
    return 0;
  /* a pointer to a packed DIB is the result. A packed DIB is a BITMAPINFO */
  /* structure followed by an array of bytes containing the bitmap bits.   */
  lpInfo =  (LPBITMAPINFOHEADER) prsrc;

  dc=Wnd->GetDC();

  int nBpp = dc->GetDeviceCaps(BITSPIXEL);

  //m_cPalette.UnrealizeObject();
  OldPal= dc->SelectPalette(&m_cPalette,FALSE);
  dc->RealizePalette();

  lpBits = (LPSTR)lpInfo + (WORD)lpInfo->biSize + 256 * sizeof(RGBQUAD);
  hBitmap = CreateDIBitmap(dc->m_hDC, lpInfo, CBM_INIT, lpBits, (LPBITMAPINFO)lpInfo, DIB_RGB_COLORS);

  BmSrcDC.CreateCompatibleDC(dc);
  BmDstDC.CreateCompatibleDC(dc);
  pBitmap->CreateCompatibleBitmap(dc,lpInfo->biWidth,lpInfo->biHeight);

  CBitmap* pOldBmp =BmSrcDC.SelectObject(CBitmap::FromHandle(hBitmap));
  CBitmap* pOldBmp2=BmDstDC.SelectObject(pBitmap);

  BmDstDC.BitBlt(0,0,lpInfo->biWidth,lpInfo->biHeight,&BmSrcDC,0,0,SRCCOPY);

  BmSrcDC.SelectObject(pOldBmp);
  BmDstDC.SelectObject(pOldBmp2);

  //m_cPalette.UnrealizeObject();
  dc->SelectPalette(OldPal,TRUE);
  BOOL xxx2=dc->RealizePalette();
  Wnd->ReleaseDC(dc);

  UnlockResource((HGLOBAL)hglb);
  FreeResource  ((HGLOBAL)hglb);

  DeleteObject(hBitmap);

  return nBpp;
}