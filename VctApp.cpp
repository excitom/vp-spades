// VctApp.cpp: implementation of the CVctApplet class.
//
// This is the main game logic.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameImg.h"
#include "GamePce.h"
#include "GameBrd.h"
#include "GameApp.h"
#include "VctComm.h"
#include "GameText.h"
#include "GameMIm.h"
#include "GameBtn.h"
#include "GameArea.h"
#include "canitime.h"
#include "canim.h"
#include "csound.h"
#include "VctApp.h"
#include "Vct.h"
#include <winsock.h>
#include <mmsystem.h>
#include "resource.h"
#include "dibpalt.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "HintDlg.h"
#include "BidDlg.h"
#include "BnOptDlg.h"
#include "VctAboutBox.h"
#include "OptionDlg.h"
#include "Log.h"
#include "History.h"
#include "MsgBox.h"
#include "ApproveDlg.h"
#include "PassDialog.h"
#include "TextMsgDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CDibPalette GlobalPalette;   // global image library palette

#define STATE_FILENAME "spades.tmp"
#define STATE_DIR "C:\\Program Files\\vplaces\\games"
#define ALT_STATE_DIR "D:\\Program Files\\vplaces\\games"

// The only instance of the class.
CVctApplet theApplet;
CUbqGameApplet* GetApplet(){ return (CUbqGameApplet*)&theApplet; }

CAnimTimer AnimTimer;

extern CDibPalette GlobalPalette;   // global image library palette

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVctApplet::CVctApplet() : CUbqGameApplet()
{
	m_bInitialized = FALSE;
}

CVctApplet::~CVctApplet()
{
}

//////////////////////////////////////////////////////////////////////
// Connect Game
//////////////////////////////////////////////////////////////////////
void CVctApplet::ConnectVP(){
	m_pComm->RegisterGame(GAME_ID);
}

//////////////////////////////////////////////////////////////////////
// Init Instance of Game
//////////////////////////////////////////////////////////////////////

void
CVctApplet::InitInstance(class CUbqGameCommunication* pComm, BOOL IsLeader) {
	CUbqGameApplet::InitInstance(pComm, IsLeader);

	GlobalPalette.SetPaletteResource(IDB_BOARD);
	
	long i,j,x,y;

	//
	// Add the graphics objects to the objects vector.
	//

	GetBaseDir(m_BaseDir);

	// Blank card (0)
#define IMG_IDX_CARD_BLANK	0
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_BLANK"));
	// Back of card (1)
#define IMG_IDX_CARD_BACK	1

#ifdef CARD_FILES
	// Find where the VP client was installed

	CString base = m_BaseDir + "\\spades\\";
	CString file = base + "b.gif";
	CFileStatus status;
	if (!CFile::GetStatus(file, status)) {
		
		// If cards not where expected, try some likely alternatives

		CString b = STATE_DIR;
		b += "\\spades\\";
		file = b + "b.gif";
		if (CFile::GetStatus(file, status)) {
			m_BaseDir = STATE_DIR;
			base = b;
		}
		else {
			b = ALT_STATE_DIR;
			b += "\\spades\\";
			file = b + "b.gif";
			if (CFile::GetStatus(file, status)) {
				m_BaseDir = ALT_STATE_DIR;
				base = b;
			}
			else {
				CString msg = "Card pictures not found in ";
				msg += STATE_DIR;
				AfxMessageBox(msg);
			}
		}
	}

	m_vecImages.Add(GetSynchImageFromFile(file, RGB(73, 163, 28)));

	// Cards (2-53)
    // -- card index = (suit * 13) + face value
	// -- suits range from 0-4 (clubs, diamonds, hearts, spades)
	// -- face values range from 2-14 (2,3,4,5,6,7,8,9,10,J,Q,K,A)
	// -- therefore card index ranges from 2-53. conveniently, these
	//    correspond to the index of the card image in the image vector

	char val[14] = "23456789tjqka";
	char suit[5] = "dchs";
	char cardFile[10];
	for ( int s=0; s<4; s++ ) {
		for ( int v=0; v<13; v++ ) {
			sprintf(cardFile, "%c%c.gif", val[v], suit[s]);
			file = base + cardFile;
			m_vecImages.Add(GetSynchImageFromFile(file, RGB(73, 163, 28)));
		}
	}
	
#else
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_BACK",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_2D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_3D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_4D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_5D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_6D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_7D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_8D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_9D",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_TD",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_JD",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_QD",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_KD",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_AD",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_2C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_3C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_4C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_5C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_6C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_7C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_8C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_9C",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_TC",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_JC",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_QC",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_KC",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_AC",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_2H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_3H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_4H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_5H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_6H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_7H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_8H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_9H",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_TH",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_JH",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_QH",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_KH",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_AH",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_2S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_3S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_4S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_5S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_6S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_7S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_8S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_9S",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_TS",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_JS",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_QS",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_KS",  RGB(73, 163, 28)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_CARD_AS",  RGB(73, 163, 28)));
#endif
#define IMG_IDX_CARD_LAST	53

	// color-keyed frames around the avatars, for each team (54-55)

#define IMG_IDX_TEAM1	54
	m_vecImages.Add(GetSynchImageFromResources("GIF_TEAM1",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_TEAM1_HILITE",  RGB(255,255,255)));
#define IMG_IDX_TEAM2	56
	m_vecImages.Add(GetSynchImageFromResources("GIF_TEAM2",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_TEAM2_HILITE",  RGB(255,255,255)));
#define IMG_IDX_BTN		58
	m_vecImages.Add(GetSynchImageFromResources("GIF_BTN_UP"));
	m_vecImages.Add(GetSynchImageFromResources("GIF_BTN_UP_HI"));
	m_vecImages.Add(GetSynchImageFromResources("GIF_BTN_DOWN"));
	m_vecImages.Add(GetSynchImageFromResources("GIF_BTN_DOWN_HI"));
#define IMG_IDX_ARROW		62
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_D",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_D_OFF",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_L",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_L_OFF",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_U",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_U_OFF",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_R",  RGB(255,255,255)));
	m_vecImages.Add(GetSynchImageFromResources("GIF_ARROW_R_OFF",  RGB(255,255,255)));

	// set up our gameboard
	m_pBoard = new CUbqGameBoard(this, CWnd::FromHandle(m_pComm->getParentWnd()), rcGameBoard, IDB_BOARD, rcGameBoard);
	m_pBoard->Init();
	m_pComm->setGameWnd(m_pBoard->m_hWnd);

	CUbqGameBoardArea* ar = new CUbqGameBoardArea(1, rcGameBoard, BA_UNSLOTTED);
	m_pBoard->AddArea(ar);
	//m_pBoard->DoLoadOEMCursor(CURSOR_AIM,IDC_POINTER);
	m_pBoard->DoLoadCursor(CURSOR_AIM,IDC_POINTER);
	m_pBoard->ChangeCursor(CURSOR_AIM);
	m_pBoard->SetViewPoint(FALSE, FALSE);

	// Options button

	m_pOptionButton = new CUbqGameButton(BTN_OPTIONS, CRect(CPoint(OPT_BTN_X, OPT_BTN_Y),
                   CSize(IMAGE(IMG_IDX_BTN)->GetWidth(), IMAGE(IMG_IDX_BTN)->GetHeight())), m_pBoard , TRUE);

	m_pOptionButton->AddImage(IMAGE(IMG_IDX_BTN));
	m_pOptionButton->AddImage(IMAGE(IMG_IDX_BTN+1));
	m_pOptionButton->AddImage(IMAGE(IMG_IDX_BTN+2));
	m_pOptionButton->AddImage(IMAGE(IMG_IDX_BTN+3));
	m_pBoard->AddButton(m_pOptionButton);
	m_pBoard->SetButtonEnabled(BTN_OPTIONS);

	m_nSelectedCard = -1;
	m_nCardsPlayed  = 0;			// cards played, this trick
	m_nDealer       = -1;
	m_CurrDialog    = NULL;			// pointers to open dialog windows
	m_OptDialog     = NULL;
	m_HistoryDlg    = NULL;
	m_HintDlg       = NULL;
	m_BidDlg        = NULL;
	m_BnOptDlg      = NULL;

	m_bCardPlayed   = FALSE;		// i've played my card this trick
	m_bWaitOnBid    = FALSE;
	m_bMyTurn       = FALSE;
	m_bAlerted      = FALSE;
	m_bVoicePlayed  = FALSE;
	m_nHandState    = HAND_STATE_BIDDING;
	
	init_genrand( (unsigned int)timeGetTime() );	// initialize the random number generator

	ConnectVP();									// connect to the host VP client
	m_pComm->setGameWnd(m_pBoard->m_hWnd);
		
	for(i = 0; i < NUM_PLAYERS; i++){
		m_PlayersID[i] = NULL;
		m_bSlotOccupied[i] = FALSE;
	}

	m_nMySlot = m_pComm->GetGameInstance()->GetSlotInGroup();
	m_bPlayer = (m_nMySlot <= NUM_PLAYERS) ? TRUE : FALSE;
	if(m_pComm->GetGameInstance()->AmILeader()) {
		m_bLeader = TRUE;
		m_PlayersID[0] = m_pComm->GetGameInstance()->GetMyID();
		CString Place=m_pComm->getPlaceName();
		if (!ServiceOpenGame(GAME_ID,Place,BUILD_NUM)) {
			m_pComm->leaveGroup();
			return;
		}
    }
	else {
		m_bLeader = FALSE;
		m_pComm->enumMembers(m_pComm->GetGameInstance()->GetGroupID());
	}
	
	// Avatar positions (hard coded locations at the table)
	
	// The player always sees himself at the bottom of the game. These arrays
	// map the VP game slot numbers to the physical board slots.
	// Observers (non-players) see the leader in slot 0.

	j = (m_bPlayer) ? m_nMySlot - 1 : 0;		// convert vp game slot range 1-4 to 0-3
	m_bSlotOccupied[j] = TRUE;
	for ( i=0; i<NUM_PLAYERS; i++, j++) {
		if ( j == NUM_PLAYERS) j = 0;
		m_BoardSlot[i] = j;
	}

	m_nBlinkAvatarCount = 0;
	m_nGameLoopDelay = 0;

	// players' avatar positions

	m_AvPos[m_BoardSlot[0]].x = SLOT_0_X;
	m_AvPos[m_BoardSlot[0]].y = SLOT_0_Y;
	m_AvPos[m_BoardSlot[1]].x = SLOT_1_X;
	m_AvPos[m_BoardSlot[1]].y = SLOT_1_Y;
	m_AvPos[m_BoardSlot[2]].x = SLOT_2_X;
	m_AvPos[m_BoardSlot[2]].y = SLOT_2_Y;
	m_AvPos[m_BoardSlot[3]].x = SLOT_3_X;
	m_AvPos[m_BoardSlot[3]].y = SLOT_3_Y;

	// positions of cards on the table

	m_CardPlayedLoc[m_BoardSlot[0]].x = PLAYED_CARD_0_X;
	m_CardPlayedLoc[m_BoardSlot[0]].y = PLAYED_CARD_0_Y;
	m_CardPlayedLoc[m_BoardSlot[1]].x = PLAYED_CARD_1_X;
	m_CardPlayedLoc[m_BoardSlot[1]].y = PLAYED_CARD_1_Y;
	m_CardPlayedLoc[m_BoardSlot[2]].x = PLAYED_CARD_2_X;
	m_CardPlayedLoc[m_BoardSlot[2]].y = PLAYED_CARD_2_Y;
	m_CardPlayedLoc[m_BoardSlot[3]].x = PLAYED_CARD_3_X;
	m_CardPlayedLoc[m_BoardSlot[3]].y = PLAYED_CARD_3_Y;

	// postions of cards as they are passed

	m_CardPassedLoc[0].x = PLAYED_CARD_0_X;
	m_CardPassedLoc[0].y = PLAYED_CARD_0_Y;
	m_CardPassedLoc[1].x = PLAYED_CARD_0_X + CARD_OVERLAP;
	m_CardPassedLoc[1].y = PLAYED_CARD_0_Y;


	// positions of the arrows which indicate the players' turns

	m_ArrowInfo[m_BoardSlot[0]].x = ARROW_0_X;
	m_ArrowInfo[m_BoardSlot[0]].y = ARROW_0_Y;
	m_ArrowInfo[m_BoardSlot[1]].x = ARROW_1_X;
	m_ArrowInfo[m_BoardSlot[1]].y = ARROW_1_Y;
	m_ArrowInfo[m_BoardSlot[2]].x = ARROW_2_X;
	m_ArrowInfo[m_BoardSlot[2]].y = ARROW_2_Y;
	m_ArrowInfo[m_BoardSlot[3]].x = ARROW_3_X;
	m_ArrowInfo[m_BoardSlot[3]].y = ARROW_3_Y;
	j = IMG_IDX_ARROW;
	for ( i=0; i<NUM_PLAYERS; i++, j+=2) {
		m_ArrowInfo[m_BoardSlot[i]].idx_on = j;
		m_ArrowInfo[m_BoardSlot[i]].idx_off = j+1;
		m_ArrowInfo[m_BoardSlot[i]].w = IMAGE(j)->GetWidth();
		m_ArrowInfo[m_BoardSlot[i]].h = IMAGE(j)->GetHeight();
	}

	// chairs (which are really just box frames around the players' avatars

	for (i=0; i<NUM_PLAYERS; i++) {
		x = m_AvPos[i].x-4;
		y = m_AvPos[i].y-4;
		m_pChair[i] = new CUbqMultImage(CRect(CPoint(x, y),
	     CSize(IMAGE(IMG_IDX_TEAM1)->GetWidth(),IMAGE(IMG_IDX_TEAM1)->GetHeight())), m_pBoard);
		m_pBoard->AddMultiImage(m_pChair[i]);
		if ((i == 0) || (i == 2)) {
			m_pChair[i]->AddImage(IMAGE(IMG_IDX_TEAM1));
			m_pChair[i]->AddImage(IMAGE(IMG_IDX_TEAM1+1));
		}
		else {
			m_pChair[i]->AddImage(IMAGE(IMG_IDX_TEAM2));
			m_pChair[i]->AddImage(IMAGE(IMG_IDX_TEAM2+1));
		}
		m_pChair[i]->SetStatus(IMG_NOT_CURR_PLAYER);
	}

	// current player indicators (which are thicker framed boxes around the players' avatars)

	for (i=0; i<NUM_PLAYERS; i++) {
		x = m_ArrowInfo[i].x;
		y = m_ArrowInfo[i].y;
		m_pArrow[i] = new CUbqMultImage(CRect(CPoint(x, y),
	     CSize(m_ArrowInfo[i].w, m_ArrowInfo[i].h)), m_pBoard);
		m_pBoard->AddMultiImage(m_pArrow[i]);
		m_pArrow[i]->AddImage(IMAGE(m_ArrowInfo[i].idx_on));
		m_pArrow[i]->AddImage(IMAGE(m_ArrowInfo[i].idx_off));
	}

	// add the card images to the table. this is done after the arrows and chairs, so that
	// the cards will show up on top

	x = HAND_CARD_X;
	y = HAND_CARD_Y;
	for (i=0 ; i< CARDS_IN_HAND+2; i++) {	// hand may temporarily have 2 extra cards during passing
		m_CardLoc[i].x = x;
		m_CardLoc[i].y = y;
		m_pCardPic[i] = new CUbqMultImage(CRect(CPoint(x,y),
			CSize(IMAGE(1)->GetWidth(),IMAGE(1)->GetHeight())), m_pBoard);
		x += CARD_OVERLAP;

		m_pBoard->AddMultiImage(m_pCardPic[i]);

		// each card position has 54 possible values -- the 52 cards plus blank or the back of the card

		for (j=0; j<=IMG_IDX_CARD_LAST; j++) {
			m_pCardPic[i]->AddImage(IMAGE(j));
		}
	}
	for (i=0; i<NUM_PLAYERS; i++) {
		m_pCardPlayed[i] = new CUbqMultImage(CRect(CPoint(0,0),
			CSize(IMAGE(1)->GetWidth(),IMAGE(1)->GetHeight())), m_pBoard);
		m_pBoard->AddMultiImage(m_pCardPlayed[i]);
		for (j=0; j<=IMG_IDX_CARD_LAST; j++) {
			m_pCardPlayed[i]->AddImage(IMAGE(j));
		}
	}
	for (i=0; i<2; i++) {
		m_pCardPassed[i] = new CUbqMultImage(CRect(CPoint(0,0),
			CSize(IMAGE(1)->GetWidth(),IMAGE(1)->GetHeight())), m_pBoard);
		m_pBoard->AddMultiImage(m_pCardPassed[i]);
		for (j=0; j<=IMG_IDX_CARD_LAST; j++) {
			m_pCardPassed[i]->AddImage(IMAGE(j));
		}
	}

	// get the players' names and avatars from the vp client

	for(short a=0 ; a<NUM_PLAYERS ; a++) {
		if(m_bSlotOccupied[a]) {
			m_pComm->dupAvatar(m_pBoard->m_hWnd, a+1);
			m_pComm->setAvatarPos(a+1,
							(short)(m_AvPos[a].x+m_pBoard->GetOffsetPoint().x), 
							(short)(m_AvPos[a].y+m_pBoard->GetOffsetPoint().y), SLOT_WIDTH, SLOT_HEIGHT);
			GetPlayerName(a, m_PlayersID[a]);
			m_hands.setPlayerName( a, m_Name[a] );
			m_ExpectedName[a] = m_Name[a];
			m_bPlayerApproved[a] = TRUE;
		}
		else {
			m_Name[a].Empty();
			m_ExpectedName[a].Empty();
		}
	}

	// bidding and scoring text areas

	int ta;
	CCmgTextArea* text;

	// first, the player slot-relative text areas

	m_TextPos[m_BoardSlot[0]].x = TRICK_TEXT_X_0;
	m_TextPos[m_BoardSlot[0]].y = TRICK_TEXT_Y_0;
	m_TextPos[m_BoardSlot[1]].x = TRICK_TEXT_X_1;
	m_TextPos[m_BoardSlot[1]].y = TRICK_TEXT_Y_1;
	m_TextPos[m_BoardSlot[2]].x = TRICK_TEXT_X_2;
	m_TextPos[m_BoardSlot[2]].y = TRICK_TEXT_Y_2;
	m_TextPos[m_BoardSlot[3]].x = TRICK_TEXT_X_3;
	m_TextPos[m_BoardSlot[3]].y = TRICK_TEXT_Y_3;
	
	ta = TRICK_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		x = m_TextPos[i].x;
		y = m_TextPos[i].y;
		text = new CCmgTextArea(ta,CRect(x,y,x+TRICK_TEXT_W,y+TRICK_TEXT_H),m_pBoard,TEXTFONT_FIELD);
		m_pBoard->AddText(text);
		m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	}
	
	m_TextPos[m_BoardSlot[0]].x = BID_TEXT_X_0;
	m_TextPos[m_BoardSlot[0]].y = BID_TEXT_Y_0;
	m_TextPos[m_BoardSlot[1]].x = BID_TEXT_X_1;
	m_TextPos[m_BoardSlot[1]].y = BID_TEXT_Y_1;
	m_TextPos[m_BoardSlot[2]].x = BID_TEXT_X_2;
	m_TextPos[m_BoardSlot[2]].y = BID_TEXT_Y_2;
	m_TextPos[m_BoardSlot[3]].x = BID_TEXT_X_3;
	m_TextPos[m_BoardSlot[3]].y = BID_TEXT_Y_3;

	ta = BID_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		x = m_TextPos[i].x;
		y = m_TextPos[i].y;
		text = new CCmgTextArea(ta,CRect(x,y,x+BID_TEXT_W,y+BID_TEXT_H),m_pBoard,TEXTFONT_FIELD);
		m_pBoard->AddText(text);
		m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	}

		
	m_TextPos[m_BoardSlot[0]].x = DEALER_TEXT_X_0;
	m_TextPos[m_BoardSlot[0]].y = DEALER_TEXT_Y_0;
	m_TextPos[m_BoardSlot[1]].x = DEALER_TEXT_X_1;
	m_TextPos[m_BoardSlot[1]].y = DEALER_TEXT_Y_1;
	m_TextPos[m_BoardSlot[2]].x = DEALER_TEXT_X_2;
	m_TextPos[m_BoardSlot[2]].y = DEALER_TEXT_Y_2;
	m_TextPos[m_BoardSlot[3]].x = DEALER_TEXT_X_3;
	m_TextPos[m_BoardSlot[3]].y = DEALER_TEXT_Y_3;

	ta = DEALER_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		x = m_TextPos[i].x;
		y = m_TextPos[i].y;
		text = new CCmgTextArea(ta,CRect(x,y,x+DEALER_TEXT_W,y+DEALER_TEXT_H),m_pBoard,TEXTFONT_FIELD);
		m_pBoard->AddText(text);
		m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	}

	// fixed-position text areas

	ta = SCORE_TEXT_AREA;
	x = SCORE_TEXT_T1_X;
	y = SCORE_TEXT_T1_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W2,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = SCORE_TEXT_T2_X;
	y = SCORE_TEXT_T2_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W2,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	ta++;
	x = SCORE_TEXT_LAST_X;
	y = SCORE_TEXT_LAST_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W1,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_FIELD);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;
	x = SCORE_TEXT_LAST_T1_X;
	y = SCORE_TEXT_LAST_T1_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W3,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_SCORE);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = SCORE_TEXT_LAST_T2_X;
	y = SCORE_TEXT_LAST_T2_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W3,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_SCORE);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	ta++;
	x = SCORE_TEXT_TOTAL_X;
	y = SCORE_TEXT_TOTAL_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W3,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;	
	x = SCORE_TEXT_TOTAL_T1_X;
	y = SCORE_TEXT_TOTAL_T1_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W3,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_SCORE);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = SCORE_TEXT_TOTAL_T2_X;
	y = SCORE_TEXT_TOTAL_T2_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+SCORE_TEXT_W1,y+SCORE_TEXT_H),m_pBoard,TEXTFONT_SCORE);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	
	ta = WINNER_TEXT_AREA;
	x = WINNER_TEXT_X;
	y = WINNER_TEXT_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+WINNER_TEXT_W,y+WINNER_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;
	x = WINNER_TEXT_X_L2;
	y = WINNER_TEXT_Y_L2;
	text = new CCmgTextArea(ta,CRect(x,y,x+WINNER_TEXT_W,y+WINNER_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;
	x = WINNER_TEXT_X_L3;
	y = WINNER_TEXT_Y_L3;
	text = new CCmgTextArea(ta,CRect(x,y,x+WINNER_TEXT_W,y+WINNER_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;
	x = WINNER_TEXT_X_L4;
	y = WINNER_TEXT_Y_L4;
	text = new CCmgTextArea(ta,CRect(x,y,x+WINNER_TEXT_W,y+WINNER_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);
	ta++;
	x = WINNER_TEXT_X_L5;
	y = WINNER_TEXT_Y_L5;
	text = new CCmgTextArea(ta,CRect(x,y,x+WINNER_TEXT_W,y+WINNER_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_STD);

	ta = TEAM_TEXT_AREA;
	x = TEAM_TEXT_T1_L1_X;
	y = TEAM_TEXT_T1_L1_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = TEAM_TEXT_T2_L1_X;
	y = TEAM_TEXT_T2_L1_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD_B);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	ta++;
	x = TEAM_TEXT_T1_L2_X;
	y = TEAM_TEXT_T1_L2_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = TEAM_TEXT_T2_L2_X;
	y = TEAM_TEXT_T2_L2_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	ta++;
	x = TEAM_TEXT_T1_L3_X;
	y = TEAM_TEXT_T1_L3_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T1);
	ta++;
	x = TEAM_TEXT_T2_L3_X;
	y = TEAM_TEXT_T2_L3_Y;
	text = new CCmgTextArea(ta,CRect(x,y,x+TEAM_TEXT_W,y+TEAM_TEXT_H),m_pBoard,TEXTFONT_FIELD);
	m_pBoard->AddText(text);
	m_pBoard->SetTextColors(ta,TEXT_BG_COLOR,TEXT_FG_COLOR_T2);
	
	AfxEnableControlContainer();		// for bid/hint dialogs

	m_cSound.UnMute();					// default: sound on

	m_bDealt = FALSE;
	m_bStarted = FALSE;
	if (m_bLeader) {
		m_bDispatched = TRUE;
		LoadStateFromFile();
		UpdateGameState();

		// set up timer for animations and the game loop
	
		AnimTimer.Init(m_pBoard->GetSafeHwnd() , this);
		CAnim::InitAll();
	}
	else {
		m_bDispatched = FALSE;
		RequestState();
	}

	m_bInitialized = TRUE;
	m_bShuttingDown = FALSE;
}

//////////////////////////////////////////////////////////////////////
// Look in the Registry for the directory where the VP client was installed
//////////////////////////////////////////////////////////////////////

#define KEY_MAX_SIZE 255

void
CVctApplet::GetBaseDir(CString& base) {
	HKEY hKey = NULL;
	CString subKey("Software\\Ubique\\Virtual Places");
	long rc = RegOpenKey(HKEY_CLASSES_ROOT, subKey, &hKey);

	if(rc != ERROR_SUCCESS) {
		base = STATE_DIR;
		return;
	}
	char lpKeyName[KEY_MAX_SIZE];
	char lpValue[KEY_MAX_SIZE];
	LONG cbValue = KEY_MAX_SIZE;

	for(DWORD i = 0; RegEnumKey(hKey, i, lpKeyName, KEY_MAX_SIZE) == ERROR_SUCCESS; i++) {
		if (strcmp("Path", lpKeyName) == 0) {
			if(RegQueryValue(hKey, lpKeyName, lpValue, &cbValue) == ERROR_SUCCESS) {
				base = lpValue;
				base += "\\games";
				return;
			}
		}
	}
	RegCloseKey(hKey);
	base = STATE_DIR;
	return;
}

//////////////////////////////////////////////////////////////////////
// Exit Instance of the Game
//////////////////////////////////////////////////////////////////////

void CVctApplet::ExitInstance() {

	m_bShuttingDown = TRUE;
	
	if (m_bServiceGameStart && m_bLeader)
		ServiceLeaveGame(1);

	
	if (m_HistoryDlg) {	m_HistoryDlg->DestroyWindow(); }

	CloseDialogs();

	Log::removeAll();

	for ( int i=0; i<NUM_PLAYERS; i++ ) {
		m_Name[i].Empty();
		m_ExpectedName[i].Empty();
	}

	m_pComm->leaveGroup();

	// kill our game board

	if(m_pBoard != NULL){
		m_pBoard->DeleteWindow();
		if(!m_bNeedDelete)
			m_pBoard = NULL;
	}
	RemoveAllImages();
	
	
	CUbqGameApplet::ExitInstance();
}

void CVctApplet::RemoveAllImages()
{
	while (m_vecImages.GetSize() > 0)
	{
		CObject* po = m_vecImages.GetAt(0);
		CUbqGameImage* pb = (CUbqGameImage*) po;
		delete pb;
		m_vecImages.RemoveAt(0);
	}
}

//////////////////////////////////////////////////////////////////////
// Close any open dialogs related to this hand of cards
//////////////////////////////////////////////////////////////////////

void
CVctApplet::CloseDialogs() {
	
	if (m_CurrDialog) {
		m_CurrDialog->EndDialog(IDABORT);
		m_CurrDialog = NULL;
	}
	if (m_OptDialog) {
		m_OptDialog->EndDialog(IDABORT);
		m_OptDialog = NULL;
	}
	m_hands.closeDialog();
	if (m_HintDlg) { m_HintDlg->DestroyWindow(); }
	if (m_BidDlg)  { m_BidDlg->DestroyWindow(); }
	if (m_BnOptDlg) { m_BnOptDlg->DestroyWindow(); }
}

//////////////////////////////////////////////////////////////////////
// If you are the leader, handle someone's request for current game state
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnStateRequest(DWORD dwUserID, DWORD version) {

	if (!m_bInitialized)
		return;
	
	if (!m_bLeader) {
		AfxMessageBox("Invalid game message - state request");
		return;
	}

	if (version < GAME_VERSION) {
		CString m;
		m.LoadString(IDS_OLDER_VERSION);
		CMsgBox dlg;
		dlg.init(m);
		m_CurrDialog = &dlg;
		dlg.DoModal();
		m_CurrDialog = NULL;
	}
	
	for (int i=0; i<MAX_IN_GROUP; i++) {
		if (m_PlayersID[i] == (long)dwUserID)
			break;
	}
	BOOL approved;
	if (i<NUM_PLAYERS) {
		approved = m_bPlayerApproved[i];
	}
	else {
		approved = TRUE;
	}

	if (approved) {
		unsigned char* p = CommBuff;
		p = saveStateBuffer(p);
		int len = p - CommBuff;
		ASSERT(len < sizeof(CommBuff));
		m_pComm->SendGameMessage(CommBuff, len, MSG_STATE_DISPATCH, dwUserID);
	}
	else {
		m_pComm->SendGameMessage(NULL, 0, GMSG_WRONG_PLAYER, dwUserID);
	}
}

//////////////////////////////////////////////////////////////////////
// Collect game state info
//////////////////////////////////////////////////////////////////////

unsigned char*
CVctApplet::saveStateBuffer( unsigned char* p ){

	long version = GAME_VERSION;
	memcpy(p, &version, sizeof(version));
	p += sizeof(version);

	*p++ = (m_bDealt) ? 1 : 0;
	*p++ = m_nHandState;
	char myHand = (char)m_nMySlot - 1;
	char dealer = m_nDealer - myHand;
	if (dealer < 0)
		dealer += NUM_PLAYERS;
	*p++ = dealer;
	char player = m_nCurrPlayer - myHand;
	if (player < 0)
		player += NUM_PLAYERS;
	*p++ = player; 
	memcpy(p, &m_nCardsPlayed, sizeof(m_nCardsPlayed));
	p += sizeof(m_nCardsPlayed);
	int i, hand;
	for (hand = myHand, i=0; i<NUM_PLAYERS; hand++, i++) {
		if (hand >= NUM_PLAYERS)
			hand -= NUM_PLAYERS;
		char len = (char)m_ExpectedName[hand].GetLength();
		*p++ = len;
		memcpy(p, (const char*)m_ExpectedName[hand], len);
		p += len;
	}
	p = m_hands.saveState(p, myHand);
	*p++ = (Log::getPref()) ? 1 : 0;
	return p;
}

//////////////////////////////////////////////////////////////////////
// Game state snapshot received from the VP group leader
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnStateDispatch(BYTE* byData, DWORD dwLen) {

	unsigned char* p = byData;
	p = loadStateBuffer( p );

	if ((DWORD)(p - byData) > dwLen) {
		AfxMessageBox("Corrupt game message - state dispatch");
		return;
	}
	m_bDispatched = TRUE;

	// update the visual aspects of the game
	// and save a snapshot of the state

	UpdateGameState();

	// set up timer for animations and the game loop
	
	AnimTimer.Init(m_pBoard->GetSafeHwnd() , this);
	CAnim::InitAll();
}

//////////////////////////////////////////////////////////////////////
// Extract game state info from saved snaphot
//////////////////////////////////////////////////////////////////////

unsigned char* 
CVctApplet::loadStateBuffer( unsigned char* p ) {
	long version;
	memcpy(&version, p, sizeof(version));
	p += sizeof(version);
	m_bDealt = (  *p++ == 1) ? TRUE : FALSE;
	m_nHandState  = *p++;
	m_nDealer     = *p++;
	m_nCurrPlayer = *p++;
	memcpy(&m_nCardsPlayed, p, sizeof(m_nCardsPlayed));
	p += sizeof(m_nCardsPlayed);

	m_deck.shuffle();
	m_hands.Reset(TRUE);
	int myHand = m_nMySlot - 1;
	char tmp[256];
	for (int i = 0; i<NUM_PLAYERS; i++) {
		char len = *p++;
		memcpy(tmp, p, len);
		tmp[len] = '\0';
		m_ExpectedName[i] = tmp;
		p += len;
	}
	p = m_hands.loadState(p, &m_deck);
	BOOL n = (*p++) ? TRUE : FALSE;
	Log::setPref(n);

	if (m_bPlayer) {
		m_bCardPlayed = (m_hands.getCardPlayed(myHand) == -1) ? FALSE : TRUE;

		if (m_nCurrPlayer == myHand)
			m_bMyTurn = TRUE;
	}
	
	int j = m_nDealer + 1;
	if (j == NUM_PLAYERS) j = 0;
	for (i=1; i<=NUM_PLAYERS; i++, j++) {
		if (j == NUM_PLAYERS) j = 0;
		m_nBidPos[j] = i;
	}
	
	UpdateGameState();

	return p;
}

//////////////////////////////////////////////////////////////////////
// Start a new game
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnNewGameRequest(DWORD dwUserID) {
  m_pComm->SendGameMessage(NULL, 0, MSG_NEW_GAME_DISPATCH,
						   m_pComm->GetGameInstance()->GetGroupID());
}

void
CVctApplet::OnNewGameDispatch(BYTE* byData, DWORD dwLen) {
	Log::writeLog("New Game");
	ResetState();
}

// not allowed to restart since not the leader

void
CVctApplet::OnNewGameReject() {
  CString m;
  m.LoadString(IDS_GAME_NO_RESTART);
  CMsgBox dlg;
  dlg.init(m);
  m_CurrDialog = &dlg;
  dlg.DoModal();
  m_CurrDialog = NULL;
}

//////////////////////////////////////////////////////////////////////
// Receive a Game Message
//////////////////////////////////////////////////////////////////////

void 
CVctApplet::OnGameMessage(BYTE* byData, DWORD dwLen, DWORD dwMsgID, DWORD dwSenderID) {

  char hand, cardSlot, i, bid, bids;
  char myHand = (char)m_nMySlot - 1;
  BOOL nil;
  unsigned char* p = byData;	// a copy of the data pointer, that will get incremented
  switch(dwMsgID)
  {
	case GMSG_PLAY_CARD_REQ:

		// propagate the play to the other players (and observers)

		if (m_bLeader)
			m_pComm->SendGameMessage(byData, dwLen, GMSG_PLAY_CARD, m_pComm->GetGameInstance()->GetGroupID());
		else
			AfxMessageBox("Invalid game message - play card request");
		break;

	case GMSG_PLAY_CARD:
		cardSlot = byData[0];
		hand     = byData[1];
		if (hand == myHand) {
			m_CardLoc[cardSlot].x = BOARD_WIDTH;
			m_pCardPic[cardSlot]->ChangePos(m_CardLoc[cardSlot]);
		}
		else {
			m_hands.play( hand, cardSlot );
			logPlayedCard( hand, cardSlot );
			m_cSound.Play("WAV_PLAYCARD");
		}
		m_pCardPlayed[hand]->ChangePos(m_CardPlayedLoc[hand]);
		m_pCardPlayed[hand]->SetStatus(m_hands.show( hand, cardSlot )->getIndex());

		// if everyone has played a card, the trick is ended

		if (++m_nCardsPlayed == NUM_PLAYERS) {
			m_nCardsPlayed = 0;
			m_bMyTurn = FALSE;
			char winner = m_hands.scoreTrick();
			m_nCurrPlayer = winner;

			// was nil bid set ?

			int gameLoopDelay = 0;
			if (m_hands.nilBid(winner) && (m_hands.getTricksTakenBy(winner) == 1)) {
				m_cSound.Play("WAV_SET");
				gameLoopDelay = -12;
			}
			
			// if all cards played, hand is over

			if (m_hands.getTricksPlayed() == CARDS_IN_HAND) {
				BOOL gameOver = UpdateScores();

				// If game is over and I am the game leader, report the results to the game club service

				gameLoopDelay = -12;	// make sure there's delay before clearing the table
				if (gameOver) {
					m_nHandState = HAND_STATE_GAME_OVER;
					if (m_bLeader) {
						m_bStarted = FALSE;
						int* Scores = new int [NUM_PLAYERS];
						for (int i=0; i<NUM_PLAYERS; i++) {
							Scores[i] = m_hands.getTeamScore(i);
						}

						ServiceResultGame(NUM_PLAYERS,(unsigned long*)Scores);
						delete[] Scores;
					}
				}
				else {
					m_nHandState = HAND_STATE_HAND_ENDED;
				}
			}
			else {
				m_nHandState = HAND_STATE_TRICK_ENDED;
			}
			m_nGameLoopDelay = gameLoopDelay;	// make sure there is a pause before clearing the table
			m_bAlerted = FALSE;
		}
		else {

			// find the next player
			
			m_nCurrPlayer++;
			if (m_nCurrPlayer == NUM_PLAYERS)
				m_nCurrPlayer = 0;
			m_bMyTurn = (myHand == m_nCurrPlayer) ? TRUE : FALSE;
		}

		UpdateGameState();

		break;

	case GMSG_NEW_HAND:

		ClearTheTable();
		m_cSound.Play("WAV_SHUFFLE");

		if (!m_bLeader) {
			m_nDealer++;						// the deal rotates
			if (m_nDealer == NUM_PLAYERS)
				m_nDealer = 0;
			m_nCurrPlayer = m_nDealer + 1;		// left of the dealer
			if (m_nCurrPlayer == NUM_PLAYERS)
				m_nCurrPlayer = 0;
			int j = m_nCurrPlayer;
			for (i=1; i<=NUM_PLAYERS; i++, j++) {
				if (j == NUM_PLAYERS) j = 0;
					m_nBidPos[j] = i;
			}
			m_nCardsPlayed = 0;
			m_deck.shuffle();
			m_hands.Reset(FALSE);
			for (hand=0 ; hand<NUM_PLAYERS ; hand++) {
				for (i=0; i<CARDS_IN_HAND; i++) {
					char suit  = *p++;
					char val   = *p++;
					Card* card = m_deck.pick(suit, val);
					m_hands.addTo( hand, card );
					m_hands.setSlot( hand, i, card, CARD_UNPLAYED );
				}
			}
		
			if ((DWORD)(p - byData) > dwLen) {
				AfxMessageBox("Corrupt game message - new hand");
			}
		}
		if (m_nCurrPlayer == myHand)
			m_bMyTurn = TRUE;
		m_bCardPlayed = FALSE;
		m_nHandState = HAND_STATE_BIDDING;

		UpdateGameState();

		break;

	case GMSG_BID_REQ:

		// propagate the hint/bid to the other players (and observers)

		if (m_bLeader)
			m_pComm->SendGameMessage(byData, dwLen, GMSG_BID, m_pComm->GetGameInstance()->GetGroupID());
		else
			AfxMessageBox("Invalid game message - bid request");
		break;

	case GMSG_BID:

		hand = byData[0];
		bid =  byData[1];
		nil = (byData[2] == 1) ? TRUE : FALSE;
		ASSERT(hand == m_nCurrPlayer);
		m_bWaitOnBid = FALSE;			// Clear this flag to indicate NOT waiting on user input
		
		bids = m_hands.setBid( hand, bid, nil );

		// bidding completed?

		if (bids == 4) {

			// either team has bid blind nil?

			if (m_hands.blindNilBid(0) || m_hands.blindNilBid(1)) {
				m_nHandState = HAND_STATE_PASSING;

				// the player who opted for the blind nil now passes two cards

				m_nCurrPlayer = -1;
				for (i=0; i<NUM_PLAYERS; i++) {
					if (m_hands.canBlindNil(i) && m_hands.nilBid(i)) {
						m_nCurrPlayer = i;
						break;
					}
				}
				ASSERT(m_nCurrPlayer != -1);
			}

			// first player is left of the dealer

			else {
				m_nHandState = HAND_STATE_PLAYING;
				m_nCurrPlayer = m_nDealer+1;
				if (m_nCurrPlayer == NUM_PLAYERS)
					m_nCurrPlayer = 0;
			}
		}

		// still bidding, get next bidder

		else {
			m_nCurrPlayer++;
			if (m_nCurrPlayer == NUM_PLAYERS)
				m_nCurrPlayer = 0;
		}

		m_bMyTurn = (m_nCurrPlayer == myHand) ? TRUE : FALSE;

		UpdateGameState();
		
		break;

	case GMSG_PASS_CARD_REQ:
		
		// propagate the pass to the other players

		if (m_bLeader)
			m_pComm->SendGameMessage(byData, dwLen, GMSG_PASS_CARD, m_pComm->GetGameInstance()->GetGroupID());
		else
			AfxMessageBox("Invalid game message - play card request");
		break;

	// passing cards between team mates, at the start of a blind nil hand

	case GMSG_PASS_CARD:
		char partner, idx1, idx2;
		hand    = byData[0];
		partner = byData[1];
		idx1    = byData[2];
		idx2   = byData[3];

		Card *c1, *c2;
		
		// If I'm the receiver of the pass, show the passed card on the table

		if (partner == myHand) {

			// Show the passed cards on the table

			m_pCardPassed[0]->ChangePos(m_CardPassedLoc[0]);
			c1 = m_hands.showByIdx( hand, idx1 );
			m_pCardPassed[0]->SetStatus(c1->getIndex());
			m_pCardPassed[1]->ChangePos(m_CardPassedLoc[1]);
			c2 = m_hands.showByIdx( hand, idx2 );
			m_pCardPassed[1]->SetStatus(c2->getIndex());

			// Allow the receiver to view the pass

			CString m;
			m.LoadString(IDS_RECEIVE_PASS);
			CMsgBox dlg;
			dlg.init(m);
			m_CurrDialog = &dlg;
			dlg.DoModal();
			m_CurrDialog = NULL;

			// Clear the passed cards

			m_pCardPassed[0]->ChangePos(CPoint(BOARD_WIDTH, 0));
			m_pCardPassed[1]->ChangePos(CPoint(BOARD_WIDTH, 0));
		}

		// Pass the cards

		m_hands.pass( hand, idx1 );
		m_hands.pass( hand, idx2 );
		m_hands.setPassCount( hand );

		Log::writeLog( m_Name[hand] + " passed 2 cards");

		// If partner has not passed yet, let him do so now
				
		if (m_hands.getPassCount( partner ) < 2) {
			m_nCurrPlayer = partner;
		}

		// Both partners have passed two cards, time to start the hand

		else {
			m_nHandState = HAND_STATE_PLAYING;
			m_nCurrPlayer = m_nDealer + 1;		// First player is left of the dealer
			if (m_nCurrPlayer == NUM_PLAYERS)
				m_nCurrPlayer = 0;
		}
		m_bAlerted = FALSE;
		m_bPassDlgOpen = FALSE;
		m_bMyTurn = (myHand == m_nCurrPlayer) ? TRUE : FALSE;
		UpdateGameState();

		break;
			
	case GMSG_DECLINE_BN_REQ:
		
		// propagate the action to the other players

		if (m_bLeader)
			m_pComm->SendGameMessage(byData, dwLen, GMSG_DECLINE_BN, m_pComm->GetGameInstance()->GetGroupID());
		else
			AfxMessageBox("Invalid game message - decline blind nil request");
		break;

	// First player on a team (that is eligible for a blind nil) declines the blind nil.
    // It's important to have this in the game state in case the player bids nil after seeing his cards,
	// since he no longer qualifies for the blind nil bonus. Also, after a player declines the BN and 
	// bids nil, his partner still could accept the blind nil (resulting in a double blind nil bonus opportunity).

	case GMSG_DECLINE_BN:
		hand = byData[0];
		m_hands.setBnOpt(hand, FALSE);
		m_bWaitOnBid = FALSE;			// Clear this flag to allow the Hint dialog to open now
		Log::writeLog( m_Name[hand] + " declined the Blind Nil");
		break;

	case GMSG_WRONG_PLAYER:
		WrongPlayer();	
		break;

	default:
      AfxMessageBox("Invalid game message !");
	  break;
  }
}

//////////////////////////////////////////////////////////////////////
// Player (re)joined the game in the wrong seat
//////////////////////////////////////////////////////////////////////

void
CVctApplet::WrongPlayer() {

	// show "you're in the wrong seat" dialog

	CString m;
	m.LoadString(IDS_WRONG_PLAYER);
	CMsgBox dlg;
	dlg.init(m);
	m_CurrDialog = &dlg;
	dlg.DoModal();
	m_CurrDialog = NULL;
}

//////////////////////////////////////////////////////////////////////
// Highlight the cards as the mouse is dragged across them
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnMouseMove(CPoint Point) {

	m_pBoard->EnableCursor();
	m_pBoard->ChangeCursor(CURSOR_AIM);

	BOOL selectAllowed = ((m_nHandState == HAND_STATE_PLAYING) || (m_nHandState == HAND_STATE_PASSING));

	//if ((!m_bMyTurn) || m_bCardPlayed || (!selectAllowed) || (!AllHere()))
	if (m_bCardPlayed || (!AllHere()))
		return;

	// reset previously highlighted card, if any

	if (m_nSelectedCard != -1) {
		m_CardLoc[m_nSelectedCard].y = HAND_CARD_Y;
		m_pCardPic[m_nSelectedCard]->ChangePos(m_CardLoc[m_nSelectedCard]);
		m_nSelectedCard = -1;
	}

	// see if the mouse is over a specific card

	char hand = (char)m_nMySlot - 1;
	for (int i=0; i<CARDS_IN_HAND+2; i++) {
	  if ((m_hands.showState( hand, i ) == CARD_UNPLAYED) && (m_pCardPic[i]->IsInside(Point)))
		  m_nSelectedCard = i;
	}

	// highlight the specific card, if any

	if (m_nSelectedCard != -1) {
		m_CardLoc[m_nSelectedCard].y = HAND_CARD_Y - SELECTED_CARD_DELTA_Y;
		m_pCardPic[m_nSelectedCard]->ChangePos(m_CardLoc[m_nSelectedCard]);
	}
}

//////////////////////////////////////////////////////////////////////
// Select/play a card
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnLButtonDown(CPoint Point) {

	if (!m_bMyTurn || !((m_nHandState == HAND_STATE_PLAYING) || (m_nHandState == HAND_STATE_PASSING)))
		return;

	// see if the mouse is over a specific card

	int cardSlot = -1;
	int hand = m_nMySlot - 1;
	for (int i=0; i<CARDS_IN_HAND+2; i++) {
	  if (m_pCardPic[i]->IsInside(Point) && (m_hands.showState(hand, i) == CARD_UNPLAYED))
		  cardSlot = i;
	}
	if (cardSlot == -1)
		return;				// mouse wasn't over a card

	// playing or passing ?

	if (m_nHandState == HAND_STATE_PLAYING) {

		// tell the game server we've started playing, 
		// which makes the game "official"

		if (!m_bStarted && m_bLeader) {
			m_bStarted = 1;
			ServiceStartGame();
		}
			
		// if card clicked, play it

		if ((m_hands.showState(hand, cardSlot) == CARD_UNPLAYED) &&
			(m_nSelectedCard == cardSlot) &&
			 m_hands.isLegalPlay(hand, cardSlot))
		{
			m_nSelectedCard = -1; 
			m_bCardPlayed = TRUE;
			m_cSound.Play("WAV_PLAYCARD");
			m_hands.play( hand, cardSlot );
			logPlayedCard( hand, cardSlot );
			unsigned char* p = CommBuff;
			p[0] = cardSlot;
			p[1] = hand;
			if (m_bLeader) {
				m_pComm->SendGameMessage(p, 2, GMSG_PLAY_CARD, m_pComm->GetGameInstance()->GetGroupID());
			}
			else {
				m_pComm->SendGameMessage(p, 2, GMSG_PLAY_CARD_REQ, m_pComm->GetGameInstance()->GetLeaderID());
			}
		}
	}
	else {
		ASSERT(m_nHandState == HAND_STATE_PASSING);
		if ((cardSlot != -1) &&
			(m_hands.showState(hand, cardSlot) == CARD_UNPLAYED) &&
			(m_nSelectedCard == cardSlot))
		{
			int ct = m_hands.getPassCount( hand );
			if (ct < 2) {
				m_nSelectedCard = -1;

				// erase the passed card from my hand

				m_CardLoc[cardSlot].x = BOARD_WIDTH;
				m_pCardPic[cardSlot]->ChangePos(m_CardLoc[cardSlot]);

				// show the passed card on the table
			
				char idx = m_hands.show( hand, cardSlot )->getIndex();
				m_pCardPassed[ct]->ChangePos(m_CardPassedLoc[ct]);
				m_pCardPassed[ct]->SetStatus(idx);
			
				// pass the card to my partner's hand

				m_hands.prePass( hand, cardSlot );
			}
		}
	}
}

void CVctApplet::OnRButtonDown(CPoint Point){
	CUbqGameApplet::OnRButtonDown(Point);
}

void CVctApplet::OnLButtonUp(CPoint Point){
	CUbqGameApplet::OnLButtonUp(Point);
}

void CVctApplet::OnRButtonUp(CPoint Point){
	CUbqGameApplet::OnRButtonUp(Point);
}

void CVctApplet::OnNewGame(){
	CUbqGameApplet::OnNewGame();
}

///////////////////////////////////////////////////
// A button was clicked
///////////////////////////////////////////////////

void 
CVctApplet::OnButtonClicked(int btnID){
	ASSERT (btnID == BTN_OPTIONS);
	// position the menu near the cursor location

	CRect myRect;
	m_pBoard->GetClientRect(&myRect);
	m_pBoard->ClientToScreen(myRect);

	LoadMenu(CPoint((((myRect.right-myRect.left)/2)+(BOARD_WIDTH/2)), myRect.top));
}

BOOL CVctApplet::OnPieceMouseDown(class CUbqGamePiece* Piece, CPoint Point){
	return CUbqGameApplet::OnPieceMouseDown(Piece, Point);
}

BOOL CVctApplet::OnPieceRMouseDown(CUbqGamePiece* Piece, CPoint Point){
	return CUbqGameApplet::OnPieceRMouseDown(Piece, Point);
}

BOOL CVctApplet::OnPieceDoubleClick(CUbqGamePiece* Piece, CPoint Point){
	return CUbqGameApplet::OnPieceDoubleClick(Piece, Point);
}

BOOL CVctApplet::OnPieceDuringDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point){
	return CUbqGameApplet::OnPieceDuringDrag(Piece, area, slot, Point);
}

BOOL CVctApplet::OnPieceEndDrag(class CUbqGamePiece* Piece, class CUbqGameBoardArea* area, class CUbqGameBoardSlot* slot, CPoint Point){
	return CUbqGameApplet::OnPieceEndDrag(Piece, area, slot, Point);
}

void CVctApplet::OnMovePieceDispatch(BYTE* byData, DWORD dwLen){
	CUbqGameApplet::OnMovePieceDispatch(byData, dwLen);
}

void CVctApplet::OnMovePieceRequest(DWORD dwUserID, BYTE* byData, DWORD dwLen){
	CUbqGameApplet::OnMovePieceRequest(dwUserID, byData, dwLen);
}

void CVctApplet::OnMovePieceReject(BYTE* byData, DWORD dwLen){
	CUbqGameApplet::OnMovePieceReject(byData, dwLen);
}

//////////////////////////////////////////////////////////////////////
// A player has left the game
//////////////////////////////////////////////////////////////////////

void
CVctApplet::OnLeaveGroup(DWORD leaderId, DWORD presenceId) {
	for (int i=0 ; i<MAX_IN_GROUP ; i++) {
		if (m_PlayersID[i] == (long)presenceId)
		{
			m_bSlotOccupied[i] = FALSE;
			m_PlayersID[i] = -1;
			if (i < NUM_PLAYERS ) {
				CTime time;
				time = CTime::GetCurrentTime();
				CString now = time.Format(" left the game at %b %d, %Y %I:%M %p %z");
				Log::writeLog( m_Name[i] + now );
				m_Name[i].Empty();
				m_hands.setPlayerName( i, m_Name[i] );
				ShowTeams();
				m_bPlayerApproved[i] = FALSE;
				if (m_bLeader && (leaderId != presenceId) ) {  // If I'm the leader ..
					if (m_bServiceGameStart)
						ServiceLeaveGame(i+1);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// A player has joined the game
//////////////////////////////////////////////////////////////////////
void
CVctApplet::OnJoinGroup(DWORD presenceId, DWORD Slot) {
	  // FACES:
	for(int i=0 ; i<MAX_IN_GROUP ; i++){
		if(Slot-1 == (DWORD)i){
			m_bSlotOccupied[i] = TRUE;
			m_PlayersID[i] = presenceId;
			if(i<NUM_PLAYERS){
				//add avatars
				m_pComm->dupAvatar(m_pBoard->m_hWnd, i+1);
				m_pComm->setAvatarPos((short)(i+1),
								  (short)(m_AvPos[i].x+m_pBoard->GetOffsetPoint().x), 
								  (short)(m_AvPos[i].y+m_pBoard->GetOffsetPoint().y), SLOT_WIDTH, SLOT_HEIGHT);
				GetPlayerName(i, m_PlayersID[i]);
				m_hands.setPlayerName( i, m_Name[i] );

				if (m_bLeader) {
					ServiceJoinGame(Slot,m_Name[Slot-1]);
					
					// if a player had been in a slot and left, and a different player takes his place,
					// let the leader decide if this is OK

					if ((m_ExpectedName[i].GetLength() > 0) && (m_ExpectedName[i] != m_Name[i])) {
						CString msg = m_Name[i] + " joined the game but " + m_ExpectedName[i] + " was expected.";
						ApproveDlg dlg;
						dlg.init(msg);
						m_CurrDialog = &dlg;
						int ret = dlg.DoModal();
						m_CurrDialog = NULL;
						if (ret == IDABORT) {
							return;
						}
						m_bPlayerApproved[i] = dlg.getApproved();
						if (m_bPlayerApproved[i]) {
							m_ExpectedName[i] = m_Name[i];
						}
					}
					else {
						m_bPlayerApproved[i] = TRUE;
						if (m_ExpectedName[i].GetLength() == 0) {
							m_ExpectedName[i] = m_Name[i];
						}
					}
				}
				else {
					m_bPlayerApproved[i] = TRUE;
					m_ExpectedName[i] = m_Name[i];
				}
				CTime time;
				time = CTime::GetCurrentTime();
				CString now = time.Format(" joined the game at %b %d, %Y %I:%M %p %z");
				Log::writeLog( m_Name[i] + now );
			}
		}
	}
	
	// update the visual aspects of the game
	// and save a snapshot of the state

	UpdateGameState();
}

void
CVctApplet::OnEnumMembers(long nSlot, long lMemberID) {
	for (int i=0 ; i<MAX_IN_GROUP ; i++)
		if (nSlot-1 == i)
		{
			m_bSlotOccupied[i] = TRUE;
			m_PlayersID[i] = lMemberID;
		}
}

////////////////////////////////////////////////////////
//
// build and display a popup menu on right button click
//

void CVctApplet::LoadMenu(CPoint point){
	
  CMenu Menu;
  m_bMenuActive = TRUE;
  Menu.LoadMenu(IDR_MENU_OPT);
  ASSERT(Menu);
  CMenu* SubMenu = Menu.GetSubMenu(0);

  // position the menu near the cursor location

  CRect rect;
  m_pBoard->GetWindowRect(&rect);
  point.x += rect.TopLeft().x;
  point.y += rect.TopLeft().y;

  // set default check marks for animation and sound options

  SubMenu->CheckMenuItem(ID_MENU_GFX,MF_CHECKED);
  SubMenu->CheckMenuItem(ID_MENU_SOUND, (m_cSound.IsMuted()) ? MF_UNCHECKED: MF_CHECKED);

  // if group leader, enable the "new game" option

  if (m_bLeader) {
	  SubMenu->EnableMenuItem( ID_MENU_NEW, MF_ENABLED );
	  SubMenu->DeleteMenu(SubMenu->GetMenuItemCount() - 1, MF_BYPOSITION);
	  CString item;
	  item.LoadString(IDS_EXIT_GAME);
	  SubMenu->AppendMenu(MF_STRING, ID_MENU_EXIT, item);
  }
  m_pBoard->DisableCursor();

  // show the menu

  SubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, m_pBoard);

  // control returns after item selected, selection handled in a callback

  Menu.DestroyMenu();
  m_pBoard->EnableCursor();
  m_pBoard->ChangeCursor(CURSOR_NORMAL);
  m_hMenu = NULL;
  m_bMenuActive = FALSE;
}


LPBYTE CVctApplet::GetGameGroupGifFromResources(DWORD& dwLength){
	return CUbqGameApplet::GetGameGroupGifFromResources(dwLength);
}

LPBYTE CVctApplet::GetGameGroupSlotList(){
	return CUbqGameApplet::GetGameGroupSlotList();
}

LRESULT CVctApplet::OnMMNotify(WPARAM wParam,LPARAM lParam){
	return CUbqGameApplet::OnMMNotify(wParam, lParam);
}

void CVctApplet::OnTimer(){
	AnimTimer.OnTimerTick();
}

void CVctApplet::OnSize(){
	if(!m_bInitialized || !m_pBoard) return;
	for(int i=0 ; i<NUM_PLAYERS ; i++) {
		if(m_bSlotOccupied[i]) {
			m_pComm->setAvatarPos((short)i+1,
								(short)(m_AvPos[i].x+m_pBoard->GetOffsetPoint().x), 
								(short)(m_AvPos[i].y+m_pBoard->GetOffsetPoint().y), SLOT_WIDTH, SLOT_HEIGHT);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Animation Callback
//////////////////////////////////////////////////////////////////////
void CVctApplet::AnimCallback(short FuncIndex, BYTE* Param, int size, long AnimID){
	
}

//////////////////////////////////////////////////////////////////////
// Game Loop
//////////////////////////////////////////////////////////////////////
void
CVctApplet::GameLoop() {

	if (AllHere() && (m_nHandState != HAND_STATE_GAME_OVER)) {
		
		// blink the border around the avatar of the current player

		m_nBlinkAvatarCount++;
		if (m_nBlinkAvatarCount>=12*2-2) {
			m_pChair[m_nCurrPlayer]->SetStatus(IMG_CURR_PLAYER);
			m_pArrow[m_nCurrPlayer]->SetStatus(IMG_ARROW_ON);		// make sure the arrow is showing
		}
		if (m_nBlinkAvatarCount>=12*2) {
			m_nBlinkAvatarCount=0;
			m_pChair[m_nCurrPlayer]->SetStatus(IMG_NOT_CURR_PLAYER);
		}
	}

	// The timer pops every 80 milliseconds, which is intended for handling animations.
	// However, that's a bit too frequent for other activities, which can really tie up the CPU.
	// So, slow down the polling to about once per second ( ~ 960 milliseconds).

	if (m_nGameLoopDelay++ < 12)
			return;
	m_nGameLoopDelay = 0;

	//Log::scroll();

	// There are three types of dialogs
	// - Modal popups, used for error messages
	// - Non-modal popups for bidding and hinting
	// - Non-modal popup for the game history
	//
	// The game history may stay open indefinitely and does not need to be in focus.
	// The other two type need to be in focus so the player will answer then, since
	// the game will not continue until they are answered.
	//
	// The modal dialogs are most urgent, and are brought to the top once per second
	// to encourage a quick response. The following code checks for the modal
	// dialogs, which may come from the top level game object or from the hands object.

	if (m_OptDialog) {
		m_OptDialog->BringWindowToTop();
	}

	if (m_CurrDialog) {
		m_CurrDialog->BringWindowToTop();
	}
	CDialog* dlg = m_hands.getCurrDialog();
	if (dlg) {
		dlg->BringWindowToTop();
	}

	// Check if any of the hint/bid dialogs are open. They are popped into focus since
	// they need to be answered before the game can continue, although less frequently
	// than the modal dialogs. This allows the players to do some typing in the chat pane
	// while contemplating how to answer the dialog.

	if (m_bWaitOnBid) {
		Bidding();
		return;
	}

	// We get to here if we're NOT waiting on a hint/bid dialog

	if (AllHere()) {

		// Has a trick just been played?

		if (m_nHandState == HAND_STATE_TRICK_ENDED) {

			m_nHandState = HAND_STATE_PLAYING;
				
			// clear cards off the table

			for (int i=0; i<NUM_PLAYERS; i++) {
				m_pCardPlayed[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
			}
			m_bCardPlayed = FALSE;
			char myHand = (char)m_nMySlot - 1;
			m_bMyTurn = (m_nCurrPlayer == myHand) ? TRUE : FALSE;
		}
		
		// Has the hand ended ?

		else if (m_nHandState == HAND_STATE_HAND_ENDED) {
					
			// The leader reshuffles the deck and tells everyone about it,
			// regardless of the "dealer". The dealer determines order of
			// bidding and the first player, but the VP group leader
			// actually deals the cards.

			if (m_bLeader) {
				BOOL newGame = FALSE;
				NextHand(newGame);
			}
			m_bMyTurn = FALSE;	// wait for the New Hand message to reset
		}
				
		// Has the game ended ?

		else if (m_nHandState == HAND_STATE_GAME_OVER) {
			EraseState();	// get rid of the saved game state
			return;
		}

		// Players are hinting/bidding

		else if (m_nHandState == HAND_STATE_BIDDING) {
			if (!m_bWaitOnBid) {
				OpenBidDialog();
			}
		}

		// Passsing cards for Blind Nil

		else if (m_nHandState == HAND_STATE_PASSING) {
			CString passMsg = "";
			char myHand = (char)m_nMySlot - 1;
			char partner = m_nCurrPlayer + 2;
			if (partner >= NUM_PLAYERS)
				partner -= NUM_PLAYERS;

			// Both cards passed ?

			if (m_hands.getPassCount(m_nCurrPlayer) == 2) {
				
				// If I'm passing, confirm the selection now

				if (myHand == m_nCurrPlayer) {
					if (m_bPassDlgOpen)
						return;
					m_bPassDlgOpen = TRUE;
					PassDialog dlg;
					m_CurrDialog = &dlg;
					int ret = dlg.DoModal();
					m_CurrDialog = NULL;
					if (ret == IDABORT) {
						return;
					}

					// Pass confirmed

					if (ret == IDOK) {
					
						// tell everyone else about the passed cards

						unsigned char* p = CommBuff;
						p[0] = myHand;
						p[1] = partner;
						p[2] = m_hands.getCardToPass( myHand, 0);
						p[3] = m_hands.getCardToPass( myHand, 1);
						if (m_bLeader) {
							m_pComm->SendGameMessage(p, 4, GMSG_PASS_CARD, m_pComm->GetGameInstance()->GetGroupID());
						}
						else {
							m_pComm->SendGameMessage(p, 4, GMSG_PASS_CARD_REQ, m_pComm->GetGameInstance()->GetLeaderID());
						}
					}

					// Start over

					else {
						m_hands.clearPass(myHand);
						ShowHand();
						m_bPassDlgOpen = FALSE;
					}
					m_pCardPassed[0]->ChangePos(CPoint(BOARD_WIDTH, 0));
					m_pCardPassed[1]->ChangePos(CPoint(BOARD_WIDTH, 0));
				}
			}
			else {
				passMsg.LoadString(IDS_PASSING);
			}
			int ta = m_nCurrPlayer + BID_TEXT_AREA;
			m_pBoard->SetText(ta, passMsg);
		}

		// Playing a hand

		else if (m_nHandState == HAND_STATE_PLAYING) {

		}

		else {
			ASSERT(FALSE);		// unknown hand state
		}
		
		// Alert the current player
		// -- first alert is a subtle "ding"
		// -- after a period of inaction, use a vocal prompt

		if (m_bMyTurn) {
			if (!m_bAlerted) {
				m_bAlerted = TRUE;
				m_cSound.Play("WAV_YOURTURN");
				m_InactionTimer = time(0);
			}
			if (!m_bVoicePlayed) {
				time_t now = time(0);
				if ((now - m_InactionTimer) > INACTION_TIME) {
					m_cSound.Play("WAV_YOURTURN2");
					m_bVoicePlayed = TRUE;
				}
			}
		}
		else {
			m_bAlerted = FALSE;
			m_bVoicePlayed = FALSE;
		}
	}
	else {
		m_InactionTimer = time(0);
	}
}

//////////////////////////////////////////////////////////////////////
// Handle hinting and bidding in the game timer loop
//////////////////////////////////////////////////////////////////////
void
CVctApplet::Bidding() {
		
	char partner = m_nCurrPlayer + 2;
	if (partner >= NUM_PLAYERS)
		partner -= NUM_PLAYERS;
	
	// Blind Nil dialog open?

	if (m_BnOptDlg) {
	
		// The player took/declined the blind nil option - time to close the dialog
		
		if (m_BnOptDlg->optWasSelected()) {

			BOOL nil = m_BnOptDlg->nilBid();		// Get the selection from the dialog
			char bid = 0;
					
			if (nil) {
				m_hands.setBnOpt(partner, FALSE);	// My partner no longer has blind nil option since I took it
				BYTE* p = CommBuff;
				*p++ = m_nCurrPlayer;
				*p++ = bid;
				*p++ = (nil) ? 1 : 0;
				int len = p-CommBuff;
				if (m_bLeader) {
					m_pComm->SendGameMessage(CommBuff, len, GMSG_BID, m_pComm->GetGameInstance()->GetGroupID());
				}
				else {
					m_pComm->SendGameMessage(CommBuff, len, GMSG_BID_REQ, m_pComm->GetGameInstance()->GetLeaderID());
				}
			}
			else {
			
				// Tell the others that I declined the BN, so they know that if I
				// bid nil after seeing the cards it doesn't count as a BN.
						
				BYTE* p = CommBuff;
				*p++ = m_nCurrPlayer;
				int len = p-CommBuff;
				if (m_bLeader) {
					m_pComm->SendGameMessage(CommBuff, len, GMSG_DECLINE_BN, m_pComm->GetGameInstance()->GetGroupID());
				}
				else {
					m_pComm->SendGameMessage(CommBuff, len, GMSG_DECLINE_BN_REQ, m_pComm->GetGameInstance()->GetLeaderID());
				}
				m_hands.setBnOpt(m_nCurrPlayer, FALSE);		// Don't allow blind nil after seeing cards
			}
			
			// Finished with the Blind Nil dialog

			m_BnOptDlg->DestroyWindow();
								
			// Show the cards now
			
			ShowHand();
			return;
		}
	}

	// Hint dialog is open

	else if (m_HintDlg) {
			
		// The player has hinted - time to close the dialog
		
		if (m_HintDlg->hintWasSelected()) {
			BOOL nil = m_HintDlg->nilBid();
			char bid = m_HintDlg->getHint();
					
			BYTE* p = CommBuff;
			*p++ = m_nCurrPlayer;
			*p++ = bid;
			*p++ = (nil) ? 1 : 0;
			int len = p-CommBuff;
			if (m_bLeader) {
				m_pComm->SendGameMessage(CommBuff, len, GMSG_BID, m_pComm->GetGameInstance()->GetGroupID());
			}
			else {
				m_pComm->SendGameMessage(CommBuff, len, GMSG_BID_REQ, m_pComm->GetGameInstance()->GetLeaderID());
			}

			// Finished with the Hint dialog

			m_HintDlg->DestroyWindow();

			return;
		}
	}
	else if (m_BidDlg) {

		// The player has bid - time to close the dialog
		
		if (m_BidDlg->bidWasSelected()) {
			BOOL nil = m_BidDlg->nilBid();
			char bid = m_BidDlg->getBid();
					
			BYTE* p = CommBuff;
			*p++ = m_nCurrPlayer;
			*p++ = bid;
			*p++ = (nil) ? 1 : 0;
			int len = p-CommBuff;
			if (m_bLeader) {
				m_pComm->SendGameMessage(CommBuff, len, GMSG_BID, m_pComm->GetGameInstance()->GetGroupID());
			}
			else {
				m_pComm->SendGameMessage(CommBuff, len, GMSG_BID_REQ, m_pComm->GetGameInstance()->GetLeaderID());
			}

			// Finished with the Bid dialog

			m_BidDlg->DestroyWindow();

			return;
		}
	}

	// A hint/bid dialog is open and we're waiting for an answer.
	// - If all players are here, keep track of an inactivity timer. 
	//   Pop the window to the top periodically, and use an audio prompt once.
	// - If not all here, reset the inactivity timer.

	if (AllHere()) {
		if (m_bMyTurn) {
			time_t now = time(0);
			if ((now - m_InactionTimer) > INACTION_TIME) {
				if (m_bAlerted && !m_bVoicePlayed) {
					m_cSound.Play("WAV_YOURTURN2");
					m_bVoicePlayed = TRUE;
				}
				m_InactionTimer = now;

				// if there's a hint/bid dialog open, pop it to the front
				if (m_BidDlg) {
					m_BidDlg->BringWindowToTop();
				}
				else if (m_HintDlg) {
					m_HintDlg->BringWindowToTop();
				}
				else if (m_BnOptDlg) {
					m_BnOptDlg->BringWindowToTop();
				}
			}
		}
	}

	// Reset the inaction timer if not all the players are here,
	// since the current player can't do anything now.

	else {
		m_InactionTimer = time(0);
	}
	return;
}

//////////////////////////////////////////////////////////////////////
// Open a hint or bid dialog in the game timer loop
//////////////////////////////////////////////////////////////////////
void
CVctApplet::OpenBidDialog() {
	
	// tell the game server we've started playing, 
	// which makes the game "official"

	if (!m_bStarted && m_bLeader) {
		m_bStarted = 1;
		ServiceStartGame();
	}
	
	char myHand = (char)m_nMySlot - 1;
	m_bMyTurn = (m_nCurrPlayer == myHand) ? TRUE : FALSE;
	char partner = m_nCurrPlayer + 2;
	if (partner >= NUM_PLAYERS)
		partner -= NUM_PLAYERS;

	int ta = m_nCurrPlayer + BID_TEXT_AREA;
	char pos = m_nBidPos[m_nCurrPlayer];
	CString s;
	if (pos < 3)
		s.LoadString(IDS_HINTING);
	else
		s.LoadString(IDS_BIDDING);
	m_pBoard->SetText(ta, s);

	// If it's my turn, open a hint/bid dialog now

	if (m_bMyTurn) {
		m_bWaitOnBid = TRUE;
				
		if (m_hands.canBlindNil(m_nCurrPlayer)) {
			m_cSound.Play("WAV_BLINDNIL");
			ASSERT(!m_BnOptDlg);
			CString bidString;
			if (pos < 3) {
				bidString.Empty();
			}

			// Partner declined the blind nil

			else {
				BOOL nil = m_hands.nilBid(partner);
				if (nil) {
					bidString.LoadString(IDS_PARTNER_NIL);
				}
				else {
					char bid = m_hands.getBid(partner);
					bidString.Format(IDS_PARTNER_HINT, bid);
				}
			}
			m_BnOptDlg = new BnOptDlg;
			m_BnOptDlg->Create(IDD_BLINDNIL);
			m_BnOptDlg->init(bidString);
			m_BnOptDlg->ShowWindow(SW_SHOW);
		}
		else {
			// first two players hint to their team mate
			if (pos < 3) {
				ASSERT(!m_HintDlg);
				m_HintDlg = new HintDlg;
				m_HintDlg->Create(IDD_HINT);
				m_HintDlg->ShowWindow(SW_SHOW);
			}
				// second two players bid for the team
			else {
				CString bidString;
				BOOL nil = m_hands.nilBid(partner);
				if (nil) {
					if (m_hands.blindNilBid(m_hands.getTeam(partner)))
						bidString.LoadString(IDS_PARTNER_BN);
					else
						bidString.LoadString(IDS_PARTNER_NIL);
				}
				else {
					char bid = m_hands.getBid(partner);
					bidString.Format(IDS_PARTNER_HINT, bid);
				}
			
				ASSERT(!m_BidDlg);
				m_BidDlg = new BidDlg;
				m_BidDlg->Create(IDD_BID);
				m_BidDlg->init(bidString);
				m_BidDlg->ShowWindow(SW_SHOW);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// A hands of cards is complete (all 13 tricks played).
// Time to update the team scores.
//////////////////////////////////////////////////////////////////////

BOOL
CVctApplet::UpdateScores() {
	int team1, team2, total1, total2;
	char handsPlayed;
	int winner = m_hands.scoreHand( &team1, &team2, &total1, &total2, &handsPlayed );
	ShowTeamScores( winner, team1, team2, total1, total2, handsPlayed );
	BOOL gameOver = (winner > 0) ? TRUE : FALSE;
	if (gameOver) {
		
		// clear cards off the table

		for (int i=0; i<NUM_PLAYERS; i++) {
			m_pCardPlayed[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
			m_pChair[i]->SetStatus(IMG_NOT_CURR_PLAYER);
			m_pArrow[i]->SetStatus(IMG_ARROW_OFF);
		}
	}
	return gameOver;
}

//////////////////////////////////////////////////////////////////////
// Display the team scores on the game table.
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowTeamScores() {
	if (m_bShuttingDown)
		return;
	int team1, team2, total1, total2;
	char handsPlayed;
	int winner = m_hands.getScores( &team1, &team2, &total1, &total2, &handsPlayed );

	ShowTeamScores( winner, team1, team2, total1, total2, handsPlayed );
}

void
CVctApplet::ShowTeamScores( int winner, int team1, int team2, int total1, int total2, char handsPlayed ) {
	if (m_bShuttingDown)
		return;

	int ta = SCORE_TEXT_AREA;
	m_pBoard->SetText(ta, "Team 1");
	ta++;
	m_pBoard->SetText(ta, "Team 2");
	ta++;
	m_pBoard->SetText(ta, "Last");
	ta++;

	char msg[100];
	if (handsPlayed > 0) {
		sprintf(msg, "%4.1d", team1);
		m_pBoard->SetText(ta, msg);
	}
	else {
		m_pBoard->SetText(ta, "");
	}
	ta++;
	if (handsPlayed > 0) {
		sprintf(msg, "%4.1d", team2);
		m_pBoard->SetText(ta, msg);
	}
	else {
		m_pBoard->SetText(ta, "");
	}
	ta++;
	m_pBoard->SetText(ta, "Total");
	ta++;
	sprintf(msg, "%4.1d", total1);
	m_pBoard->SetText(ta, msg);
	ta++;
	sprintf(msg, "%4.1d", total2);
	m_pBoard->SetText(ta, msg);

	// game over?

	if (winner > 0) {
		ta = WINNER_TEXT_AREA;
		m_pBoard->SetText(ta, "GAME OVER");
		ta++;
		if (winner == 3)	// a tie
			m_pBoard->SetText(ta, "  Tie score");
		else {
			m_pBoard->SetText(ta, "Winners:");
			ta++;
			if (winner == 1) {
				m_pBoard->SetText(ta, m_Name[0]);
				ta++;
				m_pBoard->SetText(ta, "and");
				ta++;
				m_pBoard->SetText(ta, m_Name[2]);
			}
			else {
				m_pBoard->SetText(ta, m_Name[1]);
				ta++;
				m_pBoard->SetText(ta, "and");
				ta++;
				m_pBoard->SetText(ta, m_Name[3]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Update the game state information
// - Update all the visual information on the game board
// - Save a snapshot of the game state to a file
//////////////////////////////////////////////////////////////////////

void 
CVctApplet::UpdateGameState() {

	if (AllHere()) {
		if (!m_bDealt) {
			Log::writeLog( "--------------------" );
			m_nHandState = HAND_STATE_BIDDING;
			m_bDealt = TRUE;
			m_nCardsPlayed = 0;
			m_cSound.Play("WAV_SHUFFLE");
		}
	}
	if (m_bDispatched) {
		ShowHand();
		ShowCardsOnTable();
		ShowBids();
		ShowDealer();
		ShowTeams();
		if (AllHere()) {
			ShowCurrPlayer();
		}
		ShowScores();
		ShowTeamScores();
		SaveStateToFile();
	}
}

//////////////////////////////////////////////////////////////////////
// Ask the VP server for a player's chat name
//////////////////////////////////////////////////////////////////////

void
CVctApplet::GetPlayerName( int slot, long id ) {

	ASSERT( slot<MAX_IN_GROUP );

	CString Fullname;	// these 3 attributes are returned
	CString Location;	// from getPresenceInfo(), but we
	CString Email;		// don't have any use for them

	m_pComm->getPresenceInfo(id, m_Name[slot], Fullname, Location, Email);
}

//////////////////////////////////////////////////////////////////////
// Show the card in a player's hand
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowHand() {
	if (!m_bPlayer || m_bShuttingDown)			// observers only see cards on the table
		return;
	if (!m_bDealt)					// don't show cards until all 4 players have arrived
		return;
	int x = HAND_CARD_X;
	int y = HAND_CARD_Y;
	char hand = (char)m_nMySlot - 1;
	for (int i=0; i<CARDS_IN_HAND+2; i++) {		// may temporarily have 2 extra cards in hand during passing
		if (m_hands.showState(hand, i) == CARD_UNPLAYED) {
			m_CardLoc[i].x = x;
			m_CardLoc[i].y = y;
			m_pCardPic[i]->ChangePos(m_CardLoc[i]);
			x += CARD_OVERLAP;
			if ((m_nHandState == HAND_STATE_BIDDING) && m_hands.canBlindNil(hand) && (!m_hands.nilBid(hand)))
				m_pCardPic[i]->SetStatus(IMG_IDX_CARD_BACK);
			else
				m_pCardPic[i]->SetStatus(m_hands.show((char)(m_nMySlot - 1), i)->getIndex());
		}
		else {
			m_pCardPic[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Show the cards played so far in a trick
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowCardsOnTable() {
	if (m_bShuttingDown)
		return;
	for ( int hand=0; hand<NUM_PLAYERS; hand++ ) {
		char t = m_hands.getCardPlayed(hand);
		if (t != -1) {
			m_pCardPlayed[hand]->ChangePos(m_CardPlayedLoc[hand]);
			m_pCardPlayed[hand]->SetStatus(m_hands.show( hand, t )->getIndex());
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Show what each player has hinted or bid
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowBids() {
	if (m_bShuttingDown)
		return;
	char bids = m_hands.getBids();
	int hand = m_nDealer+1;
	if (hand == NUM_PLAYERS)
		hand = 0;
	for ( int i=0; i<bids; i++ ) {
		ShowBid( hand );
		hand++;
		if (hand == NUM_PLAYERS)
			hand = 0;
	}
}

void
CVctApplet::ShowBid( char hand ) {
	if (m_bShuttingDown)
		return;

	char pos = m_nBidPos[hand];
	char bid = m_hands.getBid(hand);
	BOOL nil = m_hands.nilBid(hand);

	int ta = hand + BID_TEXT_AREA;
	CString msg;

	if (nil) {
		if (m_hands.blindNilBid(m_hands.getTeam(hand))) {
			msg.LoadString(IDS_BLIND_NIL);
		}
		else {
			msg.LoadString(IDS_NIL_BID);
		}
		m_pBoard->SetText(ta, (const char *)msg);
			
		// if one of the last 2 bids is a nil, the team bid is 
		// the partner's hint

		if (pos > 2) {
			hand += 2;
			if (hand >= NUM_PLAYERS)
				hand -= NUM_PLAYERS;
			if (m_hands.doubleNilBid(m_hands.getTeam(hand))) {
				msg.LoadString(IDS_DOUBLE_NIL);
			}
			else {
				msg.Format(IDS_TEAM_BID, m_hands.getTeamBid( hand ));
			}
			
			ta = hand + BID_TEXT_AREA;
			m_pBoard->SetText(ta, (const char *)msg);
		}
	}
	else {
		if (pos <= 2) {
			msg.Format(IDS_HINT, bid);
		}
		else {
			msg.Format(IDS_TEAM_BID, m_hands.getTeamBid( hand ));
		}
		m_pBoard->SetText(ta, (const char *)msg);
	}
}

//////////////////////////////////////////////////////////////////////
// Show how many tricks each player has taken
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowScores() {
	if (!AllHere())
		return;

	int ta = TRICK_TEXT_AREA;
	CString msg;
	for ( int hand=0; hand<NUM_PLAYERS; hand++ ) {
		if ((m_nHandState == HAND_STATE_BIDDING) || (m_nHandState == HAND_STATE_PASSING))
			msg.Empty();
		else {
			BOOL showTeamTricks = TRUE;
			char pos = m_nBidPos[hand];
			char partner = hand + 2;
			if (partner >= NUM_PLAYERS)
				partner -= NUM_PLAYERS;
			if (m_hands.doubleNilBid(m_hands.getTeam(hand))) {
				showTeamTricks = FALSE;
			}
			else {
				if (pos <= 2) {
					if (!m_hands.nilBid(partner)) {
						showTeamTricks = FALSE;
					}
				}
				else {
					if (m_hands.nilBid(hand)) {
						showTeamTricks = FALSE;
					}
				}
			}
			if (showTeamTricks) {
				msg.Format(IDS_TAKEN2, m_hands.getTricksTakenBy(hand), m_hands.getTeamTricks( hand ));
			}
			else {
				msg.Format(IDS_TAKEN1, m_hands.getTricksTakenBy(hand));
			}
		}
		m_pBoard->SetText(ta, (const char *)msg);
		ta++;
	}
}

//////////////////////////////////////////////////////////////////////
// Indicate which is the current player
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowCurrPlayer() {
	if (!AllHere())
		return;
	BOOL pause = (m_nHandState == HAND_STATE_TRICK_ENDED) || (m_nHandState == HAND_STATE_GAME_OVER);
	if (AllHere() && !pause) {
		for ( int i=0; i<NUM_PLAYERS; i++ ) {
			if ( i == m_nCurrPlayer) {
				m_pChair[i]->SetStatus(IMG_CURR_PLAYER);
				m_pArrow[i]->SetStatus(IMG_ARROW_ON);
			}
			else {
				m_pChair[i]->SetStatus(IMG_NOT_CURR_PLAYER);
				m_pArrow[i]->SetStatus(IMG_ARROW_OFF);
			}
		}
	}
	else {
		for ( int i=0; i<NUM_PLAYERS; i++ ) {
			m_pChair[i]->SetStatus(IMG_NOT_CURR_PLAYER);
			m_pArrow[i]->SetStatus(IMG_ARROW_OFF);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Indicate which player is the dealer
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowDealer() {
	if (!AllHere())
		return;
	int ta = DEALER_TEXT_AREA;
	CString d;
	d.LoadString(IDS_DEALER);
	for ( int i=0; i<NUM_PLAYERS; i++ ) {
		if ( i == m_nDealer )
			m_pBoard->SetText(ta, d);
		else 
			m_pBoard->SetText(ta, "");
		ta++;
	}
}

//////////////////////////////////////////////////////////////////////
// Show the names of the team members
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ShowTeams() {
	if (m_bShuttingDown)
		return;
	int ta = TEAM_TEXT_AREA;
	m_pBoard->SetText(ta, "Team 1");
	ta++;
	m_pBoard->SetText(ta, "Team 2");
	ta++;

	for ( int i=0; i<NUM_PLAYERS; i++, ta++ ) {
		// truncate long player names
		if (m_Name[i].GetLength() > MAX_NAME_TEXT) {
			CString n = m_Name[i].Left(MAX_NAME_TEXT-3) + "...";
			m_pBoard->SetText(ta, (const char*)n);
		}
		else
			m_pBoard->SetText(ta, (const char*)m_Name[i]);
	}
}

//////////////////////////////////////////////////////////////////////
// Determine if all 4 players are present at the table
//////////////////////////////////////////////////////////////////////

BOOL
CVctApplet::AllHere() {
	BOOL allHere = TRUE;
	for ( int i=0; i<NUM_PLAYERS; i++ ) {
		allHere = allHere && m_bSlotOccupied[i] && m_bPlayerApproved[i];
	}
	return allHere;
}

//////////////////////////////////////////////////////////////////////
// Save game state snapshot to a file
//////////////////////////////////////////////////////////////////////

void
CVctApplet::SaveStateToFile() {
	if (!m_bPlayer) {
		return;
	}
	FILE *fp;
    char *fname = STATE_FILENAME;
	char cwd[_MAX_PATH];

	_getcwd( cwd, _MAX_PATH );
	_chdir( m_BaseDir );
    if((fp=fopen(fname,"wb")) == NULL) {
		_chdir( cwd );
        return;
    }
	unsigned char* p = CommBuff;
	p = saveStateBuffer(p);
	long dataLen = p-CommBuff;
	ASSERT(dataLen < sizeof(CommBuff));
	fwrite(&dataLen, sizeof(dataLen), 1, fp);		// length of the game data
    fwrite(CommBuff, dataLen, 1, fp);				// the game data
	fclose(fp);
	_chdir( cwd );
}

//////////////////////////////////////////////////////////////////////
// Load game state snapshot from a file
//////////////////////////////////////////////////////////////////////

void
CVctApplet::LoadStateFromFile() {
	FILE *fp;
    char *fname = STATE_FILENAME;
	char cwd[_MAX_PATH];

	if(m_bLeader){		
		_getcwd( cwd, _MAX_PATH );
		_chdir( m_BaseDir );
		fp=fopen(fname,"rb");
		_chdir( cwd );	
        if (fp != NULL){
			long dataLen;
			fread(&dataLen, sizeof(dataLen),1,fp);	// length of the game data
			if ((dataLen < 0) || (dataLen > sizeof(CommBuff))) {
				fclose(fp);
				CorruptState();
				return;
			}
			unsigned char* p = CommBuff;
			int len = fread(p, 1, dataLen, fp);		// the game data
			if (len != dataLen) {
				fclose(fp);
				CorruptState();
				return;
			}
			fclose(fp);
			loadStateBuffer(p);

			// In case i'm restarting a game under another chat name,
			// e.g. a guest with a different suffix, reset the leader's
			// expected name
			m_ExpectedName[0] = m_Name[0];

			CTime time;
			time = CTime::GetCurrentTime();

			// If the last game ended normally, clear
			// the old game state and start over

			if (m_nHandState == HAND_STATE_GAME_OVER) {
				m_nDealer = -1;
				ResetState();
			}
			else {
				CString now = time.Format("Game in progress, resumed %b %d, %Y %I:%M %p %z");
				Log::writeLog(now);
				CString line = "Game resumed by: ";
				line += m_Name[0];
				Log::writeLog(line);
			}
		}
		// no state file
		else {
			ResetState();
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Saved state file contains bad data
//////////////////////////////////////////////////////////////////////

void
CVctApplet::CorruptState() {
	CString m;
	m.LoadString(IDS_GAME_NO_RESTORE);
	CMsgBox dlg;
	dlg.init(m);
	m_CurrDialog = &dlg;
	int ret = dlg.DoModal();
	m_CurrDialog = NULL;
	if (ret == IDABORT) {
		return;
	}

	ResetState();
}

//////////////////////////////////////////////////////////////////////
// Delete the game state file
//////////////////////////////////////////////////////////////////////

void
CVctApplet::EraseState() {
	char cwd[_MAX_PATH];
	_getcwd( cwd, _MAX_PATH );
	_chdir( m_BaseDir );
	int tmp = remove(STATE_FILENAME);
	_chdir( cwd );
}

//////////////////////////////////////////////////////////////////////
// Reset the game state and start over
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ResetState() {

	EraseState();	// delete the state file (if any)

	m_bDealt      = FALSE;
	m_bCardPlayed = FALSE;
	m_bMyTurn     = FALSE;
	m_bAlerted    = FALSE;
	m_bWaitOnBid  = FALSE;
	m_bStarted    = FALSE;
	m_nSelectedCard = -1;
	m_nHandState = HAND_STATE_BIDDING;
	m_nGameLoopDelay = 0;

	CloseDialogs();
	
	for (int i=0; i<NUM_PLAYERS; i++) {
		if (!m_bSlotOccupied[i]) {
			m_ExpectedName[i].Empty();
		}
	}

	ClearTheTable();

	if (m_bLeader) {
		Log::removeAll();		// clear old game log
		CTime time;
		time = CTime::GetCurrentTime();
		CString now = time.Format("Game started %b %d, %Y %I:%M %p %z");
		Log::writeLog(now);
		CString line = "Game started by: ";
		line += m_Name[0];
		Log::writeLog(line);
		NextHand(TRUE);
	}
}

//////////////////////////////////////////////////////////////////////
// Remove played cards from the table
//////////////////////////////////////////////////////////////////////

void
CVctApplet::ClearTheTable() {
	
	// clear cards off the table, if any

	for (int i=0; i<NUM_PLAYERS; i++) {
		m_pCardPlayed[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
	}
	for (i=0; i<2; i++) {
		m_pCardPassed[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
	}

	// clear current hand of cards

	for (i=0; i<CARDS_IN_HAND+2; i++) {		// may temporarily have 2 extra cards in hand during passing
		m_pCardPic[i]->ChangePos(CPoint(BOARD_WIDTH, 0));
	}
	
	// clear text areas

	int ta = BID_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		m_pBoard->SetText(ta, "");
	}
	ta = TRICK_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		m_pBoard->SetText(ta, "");
	}
	ta = DEALER_TEXT_AREA;
	for (i=0; i<NUM_PLAYERS; i++, ta++) {
		m_pBoard->SetText(ta, "");
	}
	ta = WINNER_TEXT_AREA;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
	ta = SCORE_TEAM_1_AREA;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
	ta = TOTAL_TEAM_1_AREA;
	m_pBoard->SetText(ta, "");
	ta++;
	m_pBoard->SetText(ta, "");
}

//////////////////////////////////////////////////////////////////////
// Start a new hand of cards
//////////////////////////////////////////////////////////////////////

void
CVctApplet::NextHand( BOOL newGame ) {

	ASSERT(m_bLeader);

	m_nDealer++;						// the deal rotates
	if (m_nDealer == NUM_PLAYERS)
		m_nDealer = 0;
	m_nCurrPlayer = m_nDealer + 1;		// left of the dealer
	if (m_nCurrPlayer == NUM_PLAYERS)
		m_nCurrPlayer = 0;
	int j = m_nCurrPlayer;
	for (int i=1; i<=NUM_PLAYERS; i++, j++) {
		if (j == NUM_PLAYERS) j = 0;
			m_nBidPos[j] = i;
	}
	m_nCardsPlayed = 0;

	// Initialize hands of cards

	m_deck.shuffle();
	m_hands.Reset(newGame);
	int hand = 0;
	for (i=CARDS_IN_DECK; i > 0; i--) {
		int val = genrand()%i;
		Card* card = m_deck.deal(val);
		m_hands.addTo(hand, card);
		hand++;
		if (hand == NUM_PLAYERS) {
			hand = 0;
		}
	}
	m_hands.setSlots();

	unsigned char* p = CommBuff;
	if (newGame) {
		p = saveStateBuffer(p);
		int len = p - CommBuff;
		ASSERT(len < sizeof(CommBuff));
		for (int i=1; i<MAX_IN_GROUP; i++) {
			if (m_bSlotOccupied[i]) {
				m_pComm->SendGameMessage(CommBuff, len, MSG_STATE_DISPATCH, m_PlayersID[i]);
			}
		}
		UpdateGameState();
	}
	else {
		for (int hand=0 ; hand<NUM_PLAYERS ; hand++) {
			for (int i=0; i<CARDS_IN_HAND; i++) {
				Card* c = m_hands.show( hand, i );
				*p++ = c->getSuit();
				*p++ = c->getValue();
			}
		}
		int len = p - CommBuff;
		m_pComm->SendGameMessage(CommBuff, len, GMSG_NEW_HAND, m_pComm->GetGameInstance()->GetGroupID());
	}
}

//////////////////////////////////////////////////////////////////////
// request current game state from the VP group leader
//////////////////////////////////////////////////////////////////////

void
CVctApplet::RequestState() {
  long version = GAME_VERSION;
  m_pComm->SendGameMessage((unsigned char *)&version, sizeof(version), MSG_STATE_REQUEST, m_pComm->GetGameInstance()->GetLeaderID());

}

/////////////////////////////////////////////////////////////////////////////
// Right-button menu message handlers
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CVctApplet, CUbqGameApplet)
	//{{AFX_MSG_MAP(COptMenu)
	ON_COMMAND(ID_GAMEOPTIONS, OnGameOptions)
	ON_COMMAND(ID_GAMEOPTIONS_ABOUTSPADES, OnAbout)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_COMMAND(ID_MENU_GFX, OnMenuGfx)
	ON_COMMAND(ID_MENU_HELP, OnMenuHelp)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_HISTORY, OnMenuHistory)
	ON_COMMAND(ID_MENU_SOUND, OnMenuSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CVctApplet::OnGameOptions() 
{
	COptionDlg dlg;
	m_OptDialog = &dlg;
	dlg.init(&m_hands, m_bLeader, m_bDealt);
	dlg.DoModal();	
	m_OptDialog = NULL;
	
	// If the options dialog is open when a bid dialog is opened,
	// closing the options dialog causes the bid dialog to close too.
	// Clear the flag to cause the bid dialog to reopen.

	if (m_bWaitOnBid) {
		m_bWaitOnBid = FALSE;
	}
	
	if (m_bLeader) {
		SaveStateToFile();		// save changes, if any
	}
}

void CVctApplet::OnAbout() 
{
	CVctAboutBox dlg;
	m_CurrDialog = &dlg;
	dlg.DoModal();
	m_CurrDialog = NULL;
}

void CVctApplet::OnMenuHistory() 
{
	if (!m_HistoryDlg) {
		m_HistoryDlg = new History;
		m_HistoryDlg->Create(IDD_HISTORY);
		m_HistoryDlg->init();

		Log::update();
	}
	m_HistoryDlg->ShowWindow(SW_SHOW);
}
void CVctApplet::OnMenuExit() 
{
	m_pComm->leaveGroup();
	
}

void CVctApplet::OnMenuGfx() 
{
	AfxMessageBox("Coming soon ...");
}

void CVctApplet::OnMenuHelp() 
{
	CString strOpp("open");
    CString url;
	url.LoadString(IDS_HELP_URL);
    CString strDir("C:\\");
    int nShow = 0;
    ShellExecute(m_pBoard->GetSafeHwnd(), strOpp, url, NULL, strDir, nShow);
}

void CVctApplet::OnMenuNew() 
{
	OnNewGameRequest(m_PlayersID[0]);
}

void CVctApplet::OnMenuSound() 
{
	if (m_cSound.IsMuted())
		m_cSound.UnMute();
	else
		m_cSound.Mute();
	
}

///////////////////////////////////////
// Write info about a card to the log
///////////////////////////////////////

void
CVctApplet::logPlayedCard( char hand, char slot ) {
	char suit = m_hands.show( hand, slot )->getSuit();
	char val = m_hands.show( hand, slot )->getValue();
	ASSERT((suit >= 0) && (suit <= 3));
	ASSERT((val >= 2) && (val <=14));

	char suitName[10] = "";
	char cardName[10] = "";
	switch (suit) {
	case 0:
		strcpy(suitName, "Diamonds");
		break;
	case 1:
		strcpy(suitName, "Clubs");
		break;
	case 2:
		strcpy(suitName, "Hearts");
		break;
	case 3:
		strcpy(suitName, "Spades");
		break;
	default:
		ASSERT(FALSE);
	}
	if (val < 11) {
		sprintf(&cardName[0], "%d", val);
	}
	else {
		switch (val) {
		case 11:
			strcpy(cardName, "Jack");
			break;
		case 12:
			strcpy(cardName, "Queen");
			break;
		case 13:
			strcpy(cardName, "King");
			break;
		case 14:
			strcpy(cardName, "Ace");
			break;
		default:
			ASSERT(FALSE);
		}
	}

	CString msg;
	msg.Format(IDS_PLAYED, m_Name[hand], cardName, suitName);
	Log::writeLog(msg, TRUE);
	return;
}

void
CVctApplet::OnGameTextMsg( CString& msg )
{
	TextMsgDlg dlg;
	dlg.init(msg);
	int ret = dlg.DoModal();
}
