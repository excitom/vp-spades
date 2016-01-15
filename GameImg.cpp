// Game Image implementation


#include "stdafx.h"
#include "GameImg.h"

CUbqGameImage::CUbqGameImage()
{
  m_bLoaded = FALSE;
}

CUbqGameImage::~CUbqGameImage()
{
}

BOOL CUbqGameImage::LoadImageFromFile(const CString& cFileName)
{
  ASSERT(!m_bLoaded);
  m_bLoaded = m_picture.Create(cFileName);
  ASSERT(m_bLoaded);
  return m_bLoaded;
}

BOOL CUbqGameImage::LoadImageFromFile(const CString& cFileName, COLORREF clTransparent)
{
  BOOL b = LoadImageFromFile(cFileName);
  m_picture.SetTransparentColor(TRUE, clTransparent);
  return b;
}

BOOL CUbqGameImage::LoadImageFromResources(const CString& lpName, COLORREF clTransparent)
{
  BOOL b = LoadImageFromResources(lpName);
  m_picture.SetTransparentColor(TRUE, clTransparent);
  return b;
}

BOOL CUbqGameImage::LoadImageFromResources(const CString& lpName)
{
  ASSERT(!m_bLoaded);
  m_bLoaded = m_picture.Create(AfxGetInstanceHandle(), lpName, "GIFIMAGE");
  ASSERT(m_bLoaded);
  return m_bLoaded;
}

BOOL CUbqGameImage::LoadImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize, COLORREF clTransparent)
{
  BOOL b = LoadImageFromBuffer(lpBuffer, dwSize);
  m_picture.SetTransparentColor(TRUE, clTransparent);
  return b;
}

BOOL CUbqGameImage::LoadImageFromBuffer(const BYTE __HUGE* lpBuffer, DWORD dwSize)
{
  ASSERT(!m_bLoaded);
  /*
  CFile File;
  File.Open("c:\\temp\\jopa.gif", CFile::modeCreate | CFile::modeWrite);
  File.WriteHuge(lpBuffer, dwSize);
  File.Close();
  */
  m_bLoaded = m_picture.Create((BYTE __HUGE*)lpBuffer, dwSize);
  ASSERT(m_bLoaded);
  return m_bLoaded;
}

int CUbqGameImage::GetWidth()
{
  ASSERT(m_bLoaded);
  return (int)m_picture.GetWidth();
}

int CUbqGameImage::GetHeight()
{
  ASSERT(m_bLoaded);
  return (int)m_picture.GetHeight();
}


void CUbqGameImage::DrawImage(CDC& dc, CRect r)
{
  ASSERT(m_bLoaded);
  m_picture.DrawPicture(&dc, r);
}
