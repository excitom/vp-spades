#ifndef _UBQ_GAME_INSTANCE_INFO_H_
#define _UBQ_GAME_INSTANCE_INFO_H_

#ifdef _DEBUG
#pragma message("Include: " __FILE__", Stamp:" __TIMESTAMP__)
#endif

class CUbqGameInstanceInfo : public CObject
{
  // Construction
public:
  CUbqGameInstanceInfo(); 
  
  // Methods
public:
  DWORD GetGroupID();
  DWORD GetSlotInGroup();
  DWORD GetMyID();
  DWORD GetLeaderID();
    
  void SetGroupID(DWORD groupId);
  void SetMyID(DWORD myId);
  void SetLeaderID(DWORD leaderId);
  void SetSlotInGroup(DWORD slotInGroup);
    
  BOOL AmILeader();
  BOOL IsLeader(DWORD peresenceId);
  
  // Members
private:
  DWORD m_nGroupID;
  DWORD m_nMyID;
  DWORD m_nLeaderID;
  DWORD m_nSlotInGroup;
  //CObList* PlayersList;
};

#endif //_UBQ_GAME_INSTANCE_INFO_H_
