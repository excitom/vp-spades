#ifndef _UBQ_GAME_IMAGE_H_
#define _UBQ_GAME_IMAGE_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

#include <Picture.h>

// see ImageDef.h for the similar definitions
#ifndef __HUGE
#ifdef WIN32
#define __HUGE
#else
#define __HUGE  huge
#endif // WIN32
#endif // __HUGE

class CUbqGameImage : public CObject
{
  // construction
public:
  CUbqGameImage();
  ~CUbqGameImage();

  // methods
public:
  BOOL LoadImageFromFile(const CString& cFileName);
  BOOL LoadImageFromFile(const CString& cFileName, COLORREF clTransparent);
  BOOL LoadImageFromResources(const CString& lpName);
	BOOL LoadImageFromResources(const CString& lpName, COLORREF clTransparent);
	BOOL LoadImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize);
  BOOL LoadImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize, COLORREF clTransparent);
  
  void DrawImage(CDC& dc, CRect r);
  int  GetWidth();
  int  GetHeight();

  CPicture m_picture;

  // members 
private:
  BOOL m_bLoaded;
};

#endif // _UBQ_GAME_IMAGE_H_
