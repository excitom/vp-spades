#ifndef _UBQ_GAME_SLOT_H_
#define _UBQ_GAME_SLOT_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

class CUbqGameBoardSlot : public CObject
{
  // construction
  public:
    CUbqGameBoardSlot(int id, CPoint Point);
    ~CUbqGameBoardSlot();


  // methods
  public:
    DWORD Distance(CPoint Point);

  // members
  public:
    int id;
    CPoint m_ptCoord;

  // Implementation
  private:
  
};

#endif
