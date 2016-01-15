// GameMIm.h - generic class for the button and indicator classes

#ifndef _MULT_IMAGE_H_
#define _MULT_IMAGE_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

class CUbqMultImage : public CObject
{
	// construction
public:
	CUbqMultImage(CRect Area, CUbqGameBoard*  pBoard);
	virtual ~CUbqMultImage();

	// methods
public:
	BOOL IsInside(CPoint Point);
	void SetStatus(int iStatus);
	int	 GetStatus() { return m_iStatus; }
    void AddImage(CUbqGameImage* pImage);
	CUbqGameImage* GetCurrImage() { return m_pCurrImage; } 

	void ChangePos(CPoint Point);

  void SetID(long id) {this->m_nID = id;}
  int  GetID ()       {return this->m_nID;}
	
	// members
public:
	CRect m_rArea;

  // Implementation
private:
  CUbqGameImage* m_pCurrImage;
  CUbqGameBoard* m_pGameBoard;
  int m_iStatus;
  CObArray m_vecImages;
  long m_nID;		// Identity number
};
 
#endif // _MULT_IMAGE_H_

