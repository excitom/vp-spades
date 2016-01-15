#ifndef   __CBMP_H_
#define  __CBMP_H_

class CBmp
{
public:
   static int ReadBmp(CBitmap* pBitmap,UINT Name,CWnd* Wnd=NULL);

   static void Init();

   static void UnInit();

   static CPalette m_cPalette;
};

#endif

