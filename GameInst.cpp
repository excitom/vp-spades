
// Game insatance info implementation 

#include "stdafx.h"
#include "GameInst.h"
#include <stdlib.h>

CUbqGameInstanceInfo::CUbqGameInstanceInfo() 
{ 
  m_nGroupID = 0;
  m_nMyID = 0;
  m_nLeaderID = 0; 
  m_nSlotInGroup = 0; 
}

DWORD CUbqGameInstanceInfo::GetGroupID()     
{
  return m_nGroupID;
}

DWORD CUbqGameInstanceInfo::GetSlotInGroup() 
{
  return m_nSlotInGroup;
}

DWORD CUbqGameInstanceInfo::GetMyID()        
{
  return m_nMyID;
}

DWORD CUbqGameInstanceInfo::GetLeaderID()    
{
  return m_nLeaderID;
}
    
void CUbqGameInstanceInfo::SetMyID(DWORD myId)               
{
  m_nMyID = myId;
}

void CUbqGameInstanceInfo::SetGroupID(DWORD groupId)         
{
  m_nGroupID = groupId;
}

void CUbqGameInstanceInfo::SetLeaderID(DWORD leaderId)       
{
  m_nLeaderID = leaderId;
}

void CUbqGameInstanceInfo::SetSlotInGroup(DWORD slotInGroup) 
{
  m_nSlotInGroup = slotInGroup;
}
    
BOOL CUbqGameInstanceInfo::AmILeader() 
{
  return (m_nMyID == m_nLeaderID) ? TRUE : FALSE; 
}

BOOL CUbqGameInstanceInfo::IsLeader(DWORD peresenceId) 
{
  return (peresenceId == m_nLeaderID) ? TRUE : FALSE; 
}

