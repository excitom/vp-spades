#ifndef _UBQ_GAME_AREA_H_
#define _UBQ_GAME_AREA_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

#define BA_SLOTTED   TRUE
#define BA_UNSLOTTED FALSE


class CUbqGameBoardArea : public CObject
{
  // construction
  public:
    CUbqGameBoardArea(int id, CRect rArea, BOOL isSlotted);
    ~CUbqGameBoardArea();

  // methods
  public:
    int GetID();
    class CUbqGameBoardSlot* GetBestSlot(CPoint Point);
    void RemoveAllSlots();
    BOOL IsInside(CRect rArea);
    BOOL AddSlot(CUbqGameBoardSlot* slot);
    BOOL RemoveSlot(int id);

  // members
  private:
    int id;
    CRect m_rArea;
    BOOL m_bIsSlotted;
    CObArray m_vecSlots;
};

#endif // _UBQ_GAME_AREA_H_

