// GameMIm.h - generic class for the button and indicator classes

#ifndef _TEXT_AREA_H_
#define _TEXT_AREA_H_

#define  TEXTFONT_WIN_LOOSE  0
#define  TEXTFONT_FIELD  1
#define  TEXTFONT_FIELD_B 2
#define  TEXTFONT_SCORE  3
#define  TEXTFONT_SCORE_B 4

class CCmgTextArea : public CObject
{

	// construction
public:
  CCmgTextArea(int ID,CRect Area, CUbqGameBoard*  pBoard,int TextFont=0);
  virtual ~CCmgTextArea();

	// methods
public:
  BOOL IsInside(CPoint Point);
  void SetStatus(int iStatus);
  int	 GetStatus()
  {
	return m_iStatus;
  }
  void SetText(CString  text);
  void SetColors(COLORREF bg,COLORREF fg);
  void DrawText(CDC* pDC,CPoint DrawPoint);
  int  GetID()
  {
	 return m_nID;
  }

  // members
public:
	CRect m_rArea;

  // Implementation
private:
  CUbqGameBoard* m_pGameBoard;
  int            m_iStatus;
  CString        m_sText;
  int            m_nID;
  COLORREF       m_nBkColor,m_nTextColor;
  int            m_nTextFont;
};

#endif // _MULT_IMAGE_H_

