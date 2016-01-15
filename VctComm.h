// Ytzcomm.h : CYtzComm class declaration.
//                 See Ytzcomm.cpp for implementation.

#ifndef __VCTCOMM_H__
#define __VCTCOMM_H__

#include "GameInst.h"

#define MSG_CHANGE_CURR_TURN_REQUEST  1000
#define MSG_CHANGE_CURR_TURN_DISPATCH 1001
#define MSG_CHANGE_CURR_TURN_REJECT	  1002

#define MSG_NEW_GAME_REQUEST	  	  1003
#define MSG_NEW_GAME_DISPATCH		  1004
#define MSG_NEW_GAME_REJECT           1005

#define MSG_MOVE_PIECE_REQUEST        1006
#define MSG_MOVE_PIECE_DISPATCH       1007
#define MSG_MOVE_PIECE_REJECT         1008

#define MSG_STATE_REQUEST             1009
#define MSG_STATE_DISPATCH            1010
#define MSG_STATE_REJECT              1011

#define MSG_GAME_TEXT_MSG			  1100

#define ACTION_MOVE_PIECE      0
#define ACTION_ADD_PIECE       1
#define ACTION_REMOVE_PIECE    2
#define ACTION_SET_PIECE_ATTR  3
#define ACTION_CHANGE_TURN     4

#include "objcomm.h"

class CUbqGameCommunication : public CObjectBase
{
  // Construction
public:
  CUbqGameCommunication();
  virtual ~CUbqGameCommunication();

  // Methods
public:
  class CUbqGameInstanceInfo* GetGameInstance();
  // Running off the game
  void ExitGroup();

  void SendGameMessage(BYTE* msg, DWORD dwMsgLen, DWORD dwMsgType, DWORD scopeID);
  void RegisterGame(DWORD GameId);

	// VP notifications
  virtual void vpStartGame(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName,
                           long LeaderId, short Capacity, long Seat);
  virtual void vpEndGame();

  // VPKernel(IAPI) notifications
  virtual void vpJoinGroup(long Id, LPCTSTR Name, long X, long Y,
                           long GroupId, LPCTSTR GroupName);
  virtual void vpSend(long Id, LPCTSTR Name, short Type, long ToID, short SendType,
                      LPCTSTR Message, const void* Data, long len);
  virtual void vpLeaveGroup(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName);

  // EnumMembers request notification
	virtual void vpEnumMembers(long Current, short Level, long Id,
                             LPCTSTR Name, short Type, long X, long Y);
  // Service notifications
	virtual void vpSendFromService(long Id, short Type, long SrvSendType, LPCTSTR Message,
                                 const void* Data, long len, long ReqId);

  // Request from VP
  virtual void vpGetGameDetails(CString& Name, CString& Info, CString& SeatList,
                                 CString& CanChangeSeat, CString& CanSelectSeat,
                                 short& MinParticipants, short& MaxParticipants,
                                 char*& pAvatar, long& len);


private:

  BOOL m_bIsInitialized;
  DWORD m_nGameID;
  class CUbqGameInstanceInfo m_Instance;
  void GameTextMsg(const void* Data, long len);

};

#endif // __VCTCOMM_H__


