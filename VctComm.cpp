// Vctcomm.cpp - implementation of CUbqGameCommunication.

#include "stdafx.h"
#include "Vct.h"
#include "GameInst.h"
#include "GameApp.h"
#include "VctComm.h"
#include "checksum.h"

CUbqGameCommunication::CUbqGameCommunication(){
	m_bIsInitialized = FALSE;
}

CUbqGameCommunication::~CUbqGameCommunication(){

}

void CUbqGameCommunication::vpStartGame(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName,long LeaderId, short Capacity, long Seat){
	// Fill in the GameInstance info
	GetGameInstance()->SetMyID(Id);
	GetGameInstance()->SetGroupID(GroupId);
	GetGameInstance()->SetLeaderID(LeaderId);
	GetGameInstance()->SetSlotInGroup(Seat);
	if(GetApplet()){
		m_bIsInitialized = TRUE;
		GetApplet()->InitInstance(this, Id == LeaderId);
	}
}

void CUbqGameCommunication::vpEndGame(){
	if(!m_bIsInitialized) return;
	m_bIsInitialized = FALSE;
	if(GetApplet())
		GetApplet()->ExitInstance();
}

void CUbqGameCommunication::vpJoinGroup(long Id, LPCTSTR Name, long X, long Y,
                                     long GroupId, LPCTSTR GroupName){
	if((DWORD)GroupId == GetGameInstance()->GetGroupID() && GetApplet())
		GetApplet()->OnJoinGroup(Id, X); 
}

void CUbqGameCommunication::vpSend(long Id, LPCTSTR Name, short Type, long ToID, short SendType,
                                LPCTSTR Message, const void* Data, long len){


	if(!m_bIsInitialized) return;

	DWORD GameId, MessageId, chksum, version;
	DWORD PrefixSize = sizeof(GameId) + sizeof(MessageId);
	DWORD Size = PrefixSize + sizeof(chksum);
	DWORD dwLen = (DWORD)len;

	if (dwLen < Size)
	{
		OutputDebugString("Zero-length or too small opaque received.");
		return;
	}
	dwLen -= sizeof(chksum);

	// compute checksum on the message
	// purpose: detect game cheats that modify the messages
	BYTE* byData = (BYTE*)Data;
	BYTE* b = byData + dwLen;
	memcpy(&chksum, b, sizeof(chksum));
	checksum chk;
	chk.clear();
	chk.add((LPBYTE)byData, dwLen);
	DWORD computed = chk.get();
	if (computed != chksum) {
		CString m;
		m.LoadString(IDS_GAME_CORRUPTED);
		AfxMessageBox((const char *)m);
	}
	GameId = /*ntohl*/(((DWORD*)byData)[0]);      // game ID
	MessageId = /*ntohl*/(((DWORD*)byData)[1]);   // message ID

	if (GameId != m_nGameID)
	{
		OutputDebugString("Wrong GameId.");
		return;
	}

	byData += PrefixSize;
	dwLen  -= PrefixSize;

	switch(MessageId){
		case MSG_STATE_REQUEST:
			if(!GetGameInstance()->AmILeader()){
				OutputDebugString("MSG_STATE_REQUEST: Wrong receiver Id - I am not a leader.");
				return;
			}else{
				if(GetApplet())
					version = /*ntohl*/(((DWORD*)byData)[0]);
					GetApplet()->OnStateRequest(Id, version);
				return;
			}
		case MSG_STATE_DISPATCH:
			if(!GetGameInstance()->IsLeader(/*lSenderID*/ Id)){
				OutputDebugString("MSG_STATE_DISPATCH: Wrong sender Id - not a leader.");
				return;
			}else{
				if(GetApplet())
					GetApplet()->OnStateDispatch(byData, dwLen);
				return;
			}
		case MSG_NEW_GAME_REQUEST:
			if(!GetGameInstance()->AmILeader()){
				OutputDebugString("MSG_NEW_GAME_REQUEST: Wrong receiver Id - I am not a leader.");
				return;
			}else{
				if(GetApplet())
					GetApplet()->OnNewGameRequest(Id);
				return;
			}
		case MSG_NEW_GAME_DISPATCH:
			if(!GetGameInstance()->IsLeader(/*lSenderID*/ Id)){
				OutputDebugString("MSG_NEW_GAME_DISPATCH: Wrong Sender Id - not a leader.");
				return;
			}else{
				if(GetApplet())
					GetApplet()->OnNewGameDispatch(byData, dwLen);
				return;
			}
		case MSG_NEW_GAME_REJECT:
			if (!GetGameInstance()->IsLeader(/*lSenderID*/ Id)){
				OutputDebugString("MSG_NEW_GAME_REJECT: Wrong Sender id - Not a leader.");
				return;
			}else{
				if(GetApplet())
					GetApplet()->OnNewGameReject();
				return;
			}
		// tom lang 10/2004
		case MSG_GAME_TEXT_MSG:
			GameTextMsg(byData, dwLen);
			return;

		default:
			if(GetApplet())
				GetApplet()->OnGameMessage(byData, dwLen, MessageId, Id);
			return;
	}
}

void CUbqGameCommunication::vpLeaveGroup(long Id, LPCTSTR Name, long GroupId, LPCTSTR GroupName){
	if ((DWORD)GroupId == GetGameInstance()->GetGroupID() && GetApplet())
		GetApplet()->OnLeaveGroup(GetGameInstance()->GetLeaderID(), Id);
} 

void CUbqGameCommunication::vpEnumMembers(long Current, short Level, long Id,
                                       LPCTSTR Name, short Type, long X, long Y){
	if(GetApplet())
		GetApplet()->OnEnumMembers(X,Id);
}

void CUbqGameCommunication::vpSendFromService(long Id, short Type, long SrvSendType, LPCTSTR Message,
                                           const void* Data, long len, long ReqId){
	if(GetApplet())
		GetApplet()->SendFromService(Id,SrvSendType,Data,len);
}

void CUbqGameCommunication::vpGetGameDetails(CString& Name, CString& Info, CString& SeatList,
                                          CString& CanChangeSeat, CString& CanSelectSeat,
                                          short& MinParticipants, short& MaxParticipants,
                                          char*& pAvatar, long& len){
	// Load the GameGroup Name
	Name.LoadString(IDS_GMGR_NAME);
	// Load the MoreInfo URL-name
	Info.LoadString(IDS_GMGR_MOREINFO);
	// Load the Slot list
	SeatList.LoadString(IDS_GMGR_SLOTLIST);
	// Load and convert to BOOL the CanChangeSlot str
	CanChangeSeat.LoadString(IDS_GMGR_CANCHNGSLOT);
	// Load and convert to BOOL the CanSelectSlot str
	CanSelectSeat.LoadString(IDS_GMGR_CANSLCTSLOT);
	// Load and convert to short the MinPlayers value
	CString szMinParticipants;
	szMinParticipants.LoadString(IDS_GMGR_MINPLRS);
	MinParticipants = (short)atoi(szMinParticipants);
	// Load and convert to short the MaxPlayers value
	CString szMaxParticipants;
	szMaxParticipants.LoadString(IDS_GMGR_MAXPLRS);
	MaxParticipants = (short)atoi(szMaxParticipants);
	// TODO: change the Bitmap to custom binary resource if needed
	// Find, lock and pass the buffer containing the GameGroup bitmap
	HINSTANCE hInst = AfxGetInstanceHandle();
	HRSRC hResInfo = FindResource(hInst, "IDG_GAMEGROUP", "GIFIMAGE");
	ASSERT(hResInfo);
	HGLOBAL hRes = LoadResource(hInst, hResInfo);
	ASSERT(hRes);
	LPBYTE lpImage = (LPBYTE)LockResource(hRes);
	ASSERT(lpImage);
	len = (long)SizeofResource(hInst, hResInfo);
	ASSERT(len);
	pAvatar = new char[len];
	memcpy(pAvatar, lpImage, (int)len);
	// Unlock and free the resources
	UnlockResource(hRes);
	FreeResource(hRes);
}

void CUbqGameCommunication::SendGameMessage(BYTE* msg, DWORD dwMsgLen, DWORD dwMsgType, DWORD scopeID){
	// Don't accept any message to be sent before the initialization is complete.
	if(!m_bIsInitialized) return;
	DWORD newLen = dwMsgLen + 2 * sizeof(DWORD);
	DWORD totalLen = newLen + sizeof(DWORD);			// add space for checksum suffix
	BYTE* buf = new BYTE[totalLen];
	DWORD* pl = (DWORD*)buf;
	pl[0] = /*htonl*/(m_nGameID);
	pl[1] = /*htonl*/(dwMsgType);

	if (dwMsgLen)
		memcpy (pl + 2, msg, (UINT)dwMsgLen);

	// compute checksum of the message buffer and add the
	// computed value to the end of the message
	checksum chk;
	chk.clear();
	chk.add((LPBYTE)buf, newLen);
	BYTE* b = buf + newLen;
	DWORD computed = chk.get();
	memcpy(b, &computed, sizeof(computed));

	// TODO: add exception handling
	send(scopeID, 0, NULL, buf, totalLen);
	delete buf;
}

CUbqGameInstanceInfo* CUbqGameCommunication::GetGameInstance(){
	return &m_Instance;
}

void CUbqGameCommunication::RegisterGame(DWORD GameId){
	m_nGameID = GameId;
}

void CUbqGameCommunication::ExitGroup(){
  // TODO: add exception handling
	leaveGroup();
}

void CUbqGameCommunication::GameTextMsg(const void* Data, long len) {
	DWORD msgLen;
	memcpy(&msgLen, Data, sizeof(msgLen));
	char* m = (char *)malloc(msgLen+1);
	strncpy(m, (char *)Data+sizeof(msgLen), msgLen);
	m[msgLen] = '\0';
	CString tm = m;
	GetApplet()->OnGameTextMsg(tm);
	free(m);
}