#ifndef __CHAND
#define __CHAND
#define NUM_TEAMS	2

class CHand {
  private:
    Card*	 cardList;
    CardSlot slots[CARDS_IN_HAND+2];	// there may temporarily be 2 extra cards while passing
	char	 cardsInHand;
	char	 cardPlayed;				// slot number of the card I just played
	char	 bid;
	BOOL	 nil;
	BOOL     canBn;						// I can bid Blind Nil
	char	 tricksTaken;
	char	 passCount;					// count of cards I have passed
	char	 passedCard[2];				// cards I am passing

  public:
    CHand();
    ~CHand() {}
	void  Reset();
    void  addTo(Card* card);
    void  setSlots();
	void  setSlot( char slot, Card* card, char state );
    Card* play(char slot);
	Card* show(char slot);
	Card* showByIdx( char idx );
	Card* passFrom(char idx);
	void  passTo( Card* c );
	char  getPassCount() { return passCount; }
	void  setPassCount() { passCount = 2; }
	void  clearPass();
	void  prePass( char slot );
	char  showState( char slot );
	void  setState( char slot, char state );
	char  getCardPlayed() { return cardPlayed; }
	BOOL  haveSuit( char suit );
	BOOL  allTrump();
	void  trickEnded(BOOL winner);
	char  getTricksTaken() { return tricksTaken; }
	void  setBid( char bid, BOOL nil ) { this->bid = bid; this->nil = nil; }
	char  getBid() { return bid; }
	BOOL  nilBid() { return nil; }
	BOOL  canBlindNil() { return canBn; }
	void  setBnOpt(BOOL opt) { canBn = opt; }
	unsigned char* saveState(unsigned char* p);
	unsigned char* loadState(unsigned char* p, class CDeck* d);
	char  getCardToPass( char idx );
};

class CHands {
  private:
    CHand* hands[NUM_PLAYERS];
	char   trick;
	char   suitLead;
	BOOL   trumpBroken;
	char   handsPlayed;
	char   bids;
	int    teamScore[NUM_TEAMS];
	int    lastHandScore[NUM_TEAMS];
	char   teamBid[NUM_TEAMS];
	char   sandBags[NUM_TEAMS];
	BOOL   teamNil[NUM_TEAMS];
	BOOL   blindNil[NUM_TEAMS];
	BOOL   doubleNil[NUM_TEAMS];
	CString name[NUM_PLAYERS];
	class  CDialog*	m_CurrDialog;

  public:
    CHands();
    ~CHands();
	void  Reset( BOOL newGame );
    void  addTo( char hand, Card* card );
    Card* play( char hand, char slot );
	Card* show( char hand, char slot );
	Card* showByIdx( char hand, char idx );
	Card* pass( char hand, char slot );
	void  clearPass( char hand );
	void  prePass( char hand, char slot );
	char  getCardToPass( char hand, char idx );
	char  showState( char hand, char slot );
	void  setState( char hand, char slot, char state );
    void  setSlots();												// set all the card slots for all players
	void  setSlots( char hand ) { hands[hand]->setSlots(); }		// set all the card slots for a specific player
	void  setSlot( char hand, char slot, Card* card, char state );	// set a specific card slot for a specific player
	char  getCardPlayed( char hand ) { return hands[hand]->getCardPlayed(); }
	char  getPassCount( char hand ) { return hands[hand]->getPassCount(); }
	void  setPassCount( char hand ) { hands[hand]->setPassCount(); }
	BOOL  isLegalPlay(char hand, char cardSlot);
	char  scoreTrick();
	int   scoreHand( int* team1, int* team2, int* total1, int* total2, char* handsPlayed );
	int	  calcNilScore( char hand );
	int   getScores( int* team1, int* team2, int* total1, int* total2, char* handsPlayed );
	char  getTricksTakenBy(char hand) { return hands[hand]->getTricksTaken(); }
	char  getTeamTricks(char hand);
	char  getTricksPlayed() { return trick; }
	BOOL  canBlindNil( char hand ) { return hands[hand]->canBlindNil(); }
	void  setBnOpt( char hand, BOOL opt );
	int   getTargetScore() { return targetScore; }
	void  setTargetScore( int t ) { targetScore = t; }
	char  setBid( char hand, char bid, BOOL nil );
	void  setPlayerName( int hand, CString name );
	void  getPlayerName( int hand, CString& name );
	char  getTeamBid( char hand ) { return teamBid[getTeam(hand)]; }
	int   getTeamScore( char hand ) { return teamScore[getTeam(hand)]; }
	char  getBids() { return bids; }		// number of bids
	char  getBid( char hand ) { return hands[hand]->getBid(); }
	BOOL  nilBid( char hand ) { return hands[hand]->nilBid(); }
	BOOL  blindNilBid( char team ) { return blindNil[team]; }
	BOOL  doubleNilBid( char team ) { return doubleNil[team]; }
	char  getTeam( char hand ) { return ((hand == 0) || (hand == 2)) ? 0 : 1; }
	unsigned char* saveState(unsigned char* p, char myHand);
	unsigned char* loadState(unsigned char* p, class CDeck* d);
	void  closeDialog();
	class CDialog* getCurrDialog() { return m_CurrDialog; }
	
	// game attributes (apply to all hands)

	int    targetScore;
	int    nilScore;
	int    blindNilScore;
	int    doubleNilBonus;
	int    doubleBnBonus;
	BOOL   nilBidSolo;
};

#endif