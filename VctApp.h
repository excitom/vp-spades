// VctApp.h: interface for the CVctApplet class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __VCT_APP_H__
#define __VCT_APP_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "GameApp.h"
#include "csound.h"

#define GAME_VERSION	2

#define NUM_PLAYERS				4
// total amount of people allowed in this game
#define MAX_IN_GROUP			8
// game ID for clubs
#define GAME_ID					33007

#define CURSOR_NORMAL			0
#define CURSOR_AIM				1

// size of our gameboard
#define BOARD_WIDTH				420
#define BOARD_HEIGHT			308
#define rcGameBoard				CRect(0,0,BOARD_WIDTH,BOARD_HEIGHT)

// game messages
#define GMSG_PLAY_CARD			2000
#define GMSG_PLAY_CARD_REQ		2001
#define GMSG_NEW_HAND			2002
#define GMSG_BID				2003
#define GMSG_BID_REQ			2004
#define GMSG_WRONG_PLAYER		2005
#define GMSG_PASS_CARD_REQ		2006
#define GMSG_PASS_CARD			2007
#define GMSG_DECLINE_BN_REQ		2008
#define GMSG_DECLINE_BN			2009

#define INACTION_TIME	15

#include "card.h"
#include "deck.h"
#include "hands.h"

class	CUbqGameButton;
class	CPoint;

class ArrowInfo {
public:
	int h;
	int w;
	int x;
	int y;
	int idx_on;
	int idx_off;
};

//
// pseudo-random number generator
void init_genrand(unsigned long s);
unsigned long genrand(void);

class CVctApplet : public CUbqGameApplet  
{
public:
	CVctApplet();
	virtual ~CVctApplet();

	void AnimCallback (short FuncIndex,BYTE* Param,int size, long AnimID = 0);
	void ConnectVP();
	void GameLoop();
	void RequestState();
	void Bidding();
	void OpenBidDialog();

private:
	CString	m_BaseDir;

	// intra game communication buffer
	BYTE	CommBuff[500];

	BOOL	m_bInitialized;					// applet initialized
	BOOL	m_bShuttingDown;
	BOOL	m_bDealt;						// cards have been dealt (players have seen their hands)
	BOOL	m_bStarted;						// the game has started (which has significance to the game
											// server. the game is "official" at this point.)
	BOOL	m_bDispatched;					// game state dispatched from the leader
	BOOL	m_bPlaying;
	BOOL	m_bWaitOnBid;					// wait for player to hint or bid
	BOOL	m_bPassDlgOpen;
	BOOL	m_bMenuActive;					// popup menu is active
	time_t	m_InactionTimer;
	BOOL	m_bVoicePlayed;
	CObArray m_vecImages;

	BOOL	m_bLeader;						// Am I the leader.
	BOOL	m_bPlayer;						// Am I a player (or just an observer)
	long	m_nMySlot;						// slot in the game group
	BOOL	m_bSlotOccupied[MAX_IN_GROUP];	// game slot occupied?
	BOOL	m_bPlayerApproved[NUM_PLAYERS];	// leader approves of different player taking over a slot
	long	m_PlayersID[MAX_IN_GROUP];		// VP presence ID of player in a slot
	int		m_BoardSlot[NUM_PLAYERS];		// look up physical slot on board by game slot
	int		m_nBidPos[NUM_PLAYERS];			// keep track: 1st two are hinters, 2nd two are bidders
	CString	m_Name[NUM_PLAYERS];			// players' chat names
	CString m_ExpectedName[NUM_PLAYERS];	// name of player who previously occupied a slot
	char	m_nGameNum;
	char	m_nCurrPlayer;
	char	m_nDealer;
	int		m_nTargetScore;					// game ends when one team surpasses this
	char	m_nBlinkAvatarCount;
	char	m_nGameLoopDelay;
	
	// game transcript/history log
	class History* m_HistoryDlg;
	
public:
	class		History* getHistoryDlg() { return m_HistoryDlg; }
	void		clrHistoryDlg() { m_HistoryDlg	= NULL; }
	void		clrHintDlg()	{ m_HintDlg		= NULL; }
	void		clrBidDlg()		{ m_BidDlg		= NULL; }
	void		clrBnOptDlg()	{ m_BnOptDlg	= NULL; }
		
private:
	void	GetBaseDir(CString& base);
	// game state
	void	UpdateGameState();
	void	LoadStateFromFile();
	unsigned char* loadStateBuffer( unsigned char* b );
	void	SaveStateToFile();
	unsigned char* saveStateBuffer( unsigned char* b );
	void	CorruptState();
	void	EraseState();
	void	ResetState();
	void	CorruptMsg();
	BOOL	AllHere();
	void	NextHand( BOOL newGame );
	void	GetPlayerName( int slot, long id );
	void	ShowHand();
	void	ShowCardsOnTable();
	void	ShowBids();
	void	ShowBid( char hand );
	BOOL	UpdateScores();
	void	ShowScores();
	void	ShowTeamScores();
	void	ShowTeamScores( int winner, int team1, int team2, int total1, int total2, char handsPlayed );
	void	ShowCurrPlayer();
	void	ShowDealer();
	void	ShowTeams();
	void	logPlayedCard( char hand, char slot );
	void	ClearTheTable();
	void	WrongPlayer();
	void	CloseDialogs();
	
	// hand state
	// - first 2 players hinting
	// - second 2 players bidding

	char	m_nHandState;
#define HAND_STATE_BIDDING	0
#define HAND_STATE_PLAYING	1
#define HAND_STATE_PASSING	2
#define HAND_STATE_TRICK_ENDED		3
#define HAND_STATE_GAME_OVER		4
#define HAND_STATE_HAND_ENDED		5

	  // Player avatar positions
	class	CPoint	m_AvPos[NUM_PLAYERS];

#define SLOT_0_X		277
#define SLOT_0_Y		247
#define SLOT_1_X		61
#define SLOT_1_Y		122
#define SLOT_2_X		194
#define SLOT_2_Y		8
#define SLOT_3_X		325
#define SLOT_3_Y		122
#define SLOT_WIDTH		36
#define SLOT_HEIGHT		48

#define IMG_CURR_PLAYER		1
#define IMG_NOT_CURR_PLAYER	0
#define IMG_ARROW_ON		0
#define IMG_ARROW_OFF		1

  // Buttons

#define BTN_OPTIONS		0
	class	CUbqGameButton*	m_pOptionButton;
#define OPT_BTN_X		343
#define OPT_BTN_Y		5

#define IMAGE(x) ((CUbqGameImage*) m_vecImages.GetAt(x))

  // Cards

  class		CPoint	m_CardLoc[CARDS_IN_HAND+2];		// x,y coordinates of the card pictures (in hand)
  class		CPoint	m_CardPlayedLoc[NUM_PLAYERS];	// x,y coordinates of the card pictures (on table)
  class		CPoint  m_CardPassedLoc[2];				// x,y coordinates of cards being passed to partner
  
// coordiates of the first (leftmost) card in the hand
#define HAND_CARD_X			89
#define HAND_CARD_Y			229
#define SELECTED_CARD_DELTA_Y	32
// coordinates of a card that is being played
#define PLAYED_CARD_0_X		185
#define PLAYED_CARD_0_Y		149
#define PLAYED_CARD_1_X		129
#define PLAYED_CARD_1_Y		110
#define PLAYED_CARD_2_X		185
#define PLAYED_CARD_2_Y		71
#define PLAYED_CARD_3_X		241
#define PLAYED_CARD_3_Y		110

#define CARD_HEIGHT			72
#define CARD_WIDTH			54
#define CARD_OVERLAP		10

  // coordinates of the current player arrows

#define ARROW_0_X		197
#define ARROW_0_Y		197
#define ARROW_1_X		129
#define ARROW_1_Y		131
#define ARROW_2_X		197
#define ARROW_2_Y		71
#define ARROW_3_X		272
#define ARROW_3_Y		131

  ArrowInfo	m_ArrowInfo[NUM_PLAYERS];	// info about the current player arrows

  int		m_nSelectedCard;
  int		m_nCardsPlayed;
  BOOL		m_bCardPlayed;
  BOOL		m_bMyTurn;
  BOOL		m_bAlerted;
  class		CDialog*	m_CurrDialog;
  class		CDialog*	m_OptDialog;
  class		HintDlg*	m_HintDlg;
  class		BidDlg*		m_BidDlg;
  class		BnOptDlg*	m_BnOptDlg;

  class		CUbqMultImage*	m_pCardPic[CARDS_IN_HAND+2];	// card picture array for my hand
  class		CUbqMultImage*	m_pCardPlayed[NUM_PLAYERS];		// picture array for cards being played
  class		CUbqMultImage*	m_pCardPassed[2];				// picture array for cards being passed
  class		CUbqMultImage*	m_pChair[NUM_PLAYERS];			// chairs at the table
  class		CUbqMultImage*	m_pArrow[NUM_PLAYERS];			// current player indicator
  class		CDeck	m_deck;	
  class		CHands	m_hands;

  CSound	m_cSound;

  // There are two types of text areas
  // - fixed position on the table (e.g. team scores)
  // - player-relative positions, where the player always sees himself at the bottom slot
  // The TextPos array maps the upper left x,y of the player-relative text boxes. There are three
  // text boxes per player (tricks taken, hint/bid info, and dealer label). They all have the same
  // x coordinate and they y coordinate of the latter two is relative to the first.

  class	CPoint	m_TextPos[NUM_PLAYERS];

#define BID_TEXT_AREA	0
#define TRICK_TEXT_AREA	(BID_TEXT_AREA + NUM_PLAYERS)
#define SCORE_TEXT_AREA (TRICK_TEXT_AREA + NUM_PLAYERS)
#define SCORE_TEAM_1_AREA (SCORE_TEXT_AREA + 3)
#define TOTAL_TEAM_1_AREA (SCORE_TEAM_1_AREA + 3)
#define WINNER_TEXT_AREA   (SCORE_TEXT_AREA + 9)
#define DEALER_TEXT_AREA (WINNER_TEXT_AREA + 5)
#define TEAM_TEXT_AREA (DEALER_TEXT_AREA + 4)

#define TEXT_BG_COLOR		RGB(255,255,255)
#define TEXT_FG_COLOR_STD	RGB(255,255,204)
#define TEXT_FG_COLOR_T1	RGB(255,255,102)
#define TEXT_FG_COLOR_T2	RGB(51,204,255)

  // x,y coordinates and width/height of various text boxes

#define DEALER_TEXT_X_0		321
#define DEALER_TEXT_Y_0		289
#define DEALER_TEXT_W		40
#define DEALER_TEXT_H		12
#define DEALER_TEXT_X_1		57
#define DEALER_TEXT_Y_1		105
#define DEALER_TEXT_X_2		237
#define DEALER_TEXT_Y_2		49
#define DEALER_TEXT_X_3		321
#define DEALER_TEXT_Y_3		105
  
#define BID_TEXT_X_0		321
#define BID_TEXT_Y_0		254
#define BID_TEXT_W			66
#define BID_TEXT_H			12
#define BID_TEXT_X_1		57
#define BID_TEXT_Y_1		188
#define BID_TEXT_X_2		237
#define BID_TEXT_Y_2		16
#define BID_TEXT_X_3		321
#define BID_TEXT_Y_3		188
  
#define TRICK_TEXT_X_0		321
#define TRICK_TEXT_Y_0		242
#define TRICK_TEXT_W		78
#define TRICK_TEXT_H		12
#define TRICK_TEXT_X_1		57
#define TRICK_TEXT_Y_1		176
#define TRICK_TEXT_X_2		237
#define TRICK_TEXT_Y_2		4
#define TRICK_TEXT_X_3		321
#define TRICK_TEXT_Y_3		176

#define MAX_NAME_TEXT		14
#define SCORE_TEXT_T1_X		43
#define SCORE_TEXT_T1_Y		18
#define SCORE_TEXT_W1		30
#define SCORE_TEXT_W2		40
#define SCORE_TEXT_W3		30
#define SCORE_TEXT_H		16
#define SCORE_TEXT_T2_X		85
#define SCORE_TEXT_T2_Y		18
#define SCORE_TEXT_LAST_X	11
#define SCORE_TEXT_LAST_Y	31
#define SCORE_TEXT_TOTAL_X	11
#define SCORE_TEXT_TOTAL_Y	44
#define SCORE_TEXT_LAST_T1_X	45
#define SCORE_TEXT_LAST_T1_Y	30
#define SCORE_TEXT_TOTAL_T1_X	45
#define SCORE_TEXT_TOTAL_T1_Y	43
#define SCORE_TEXT_LAST_T2_X	89
#define SCORE_TEXT_LAST_T2_Y	30
#define SCORE_TEXT_TOTAL_T2_X	89
#define SCORE_TEXT_TOTAL_T2_Y	43

#define WINNER_TEXT_X		180
#define WINNER_TEXT_Y		110
#define WINNER_TEXT_W		150
#define WINNER_TEXT_H		12
#define WINNER_TEXT_X_L2	160
#define WINNER_TEXT_Y_L2	(WINNER_TEXT_Y+12)
#define WINNER_TEXT_X_L3	160
#define WINNER_TEXT_Y_L3	(WINNER_TEXT_Y_L2+12)
#define WINNER_TEXT_X_L4	160
#define WINNER_TEXT_Y_L4	(WINNER_TEXT_Y_L3+12)
#define WINNER_TEXT_X_L5	160
#define WINNER_TEXT_Y_L5	(WINNER_TEXT_Y_L4+12)

#define TEAM_TEXT_T1_L1_X	9
#define TEAM_TEXT_T1_L1_Y	229
#define TEAM_TEXT_W			70
#define TEAM_TEXT_H			12
#define TEAM_TEXT_T1_L2_X	9
#define TEAM_TEXT_T1_L2_Y	241
#define TEAM_TEXT_T1_L3_X	9
#define TEAM_TEXT_T1_L3_Y	253
#define TEAM_TEXT_T2_L1_X	9
#define TEAM_TEXT_T2_L1_Y	268
#define TEAM_TEXT_T2_L2_X	9
#define TEAM_TEXT_T2_L2_Y	280
#define TEAM_TEXT_T2_L3_X	9
#define TEAM_TEXT_T2_L3_Y	292


	// CUbqGameApplet overrides
protected:
	void OnNewGameRequest(DWORD dwUserID);
	void OnNewGameDispatch(BYTE* byData, DWORD dwLen);
	void OnNewGameReject();
	void OnStateRequest(DWORD dwUserID, DWORD version);
	void OnStateDispatch(BYTE* byData, DWORD dwLen);
	void OnMouseMove(CPoint Point);
	void OnLButtonDown(CPoint Point);
	void OnRButtonDown(CPoint Point);
	void OnLButtonUp(CPoint Point);
	void OnRButtonUp(CPoint Point);
	void OnGameTextMsg(CString& msg);
	void InitInstance(class CUbqGameCommunication* pComm, BOOL IsLeader);
	void ExitInstance();
	void RemoveAllImages();
	void OnGameMessage(BYTE* byData, DWORD dwLen, DWORD dwMsgID, DWORD dwSenderID);
	void OnNewGame();
	void OnButtonClicked(int btnID);
	BOOL OnPieceMouseDown(class CUbqGamePiece* Piece, CPoint Point);
	BOOL OnPieceRMouseDown(CUbqGamePiece* Piece, CPoint Point);
	BOOL OnPieceDoubleClick(CUbqGamePiece* Piece, CPoint Point);
	BOOL OnPieceDuringDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point);
	BOOL OnPieceEndDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point);
	void OnMovePieceDispatch(BYTE* byData, DWORD dwLen);
	void OnMovePieceRequest(DWORD dwUserID, BYTE* byData, DWORD dwLen);
	void OnMovePieceReject(BYTE* byData, DWORD dwLen);
	void OnLeaveGroup(DWORD leaderId, DWORD presenceId);
	void OnJoinGroup(DWORD presenceId, DWORD SlotId);
	void OnEnumMembers(long nSlot, long lMemberID);
	void LoadMenu(CPoint point);
	LPBYTE GetGameGroupGifFromResources(DWORD& dwLength);
	LPBYTE GetGameGroupSlotList();
	LRESULT OnMMNotify(WPARAM wParam,LPARAM lParam);
	void OnTimer();
	void OnSize();

protected:

	// Generated message map functions
	//{{AFX_MSG(COptMenu)
	afx_msg void OnGameOptions();
	afx_msg void OnAbout();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuGfx();
	afx_msg void OnMenuHelp();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuSound();
	afx_msg void OnMenuHistory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif /* __VCT_APP_H__ */
