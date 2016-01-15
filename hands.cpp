//
// Hands (of cards) class implementation and
// individual Hand of cards
//
#include "stdafx.h"
#include "card.h"
#include "hands.h"
#include "deck.h"
#include "resource.h"
#include "Log.h"
#include "MsgBox.h"

/**
 * Constructor: single hand of cards
 */
CHand::CHand() {
	Reset();
}


/**
 * Constructor: hands of cards for all the players in the game
 */
CHands::CHands() {
  for (char i=0; i<NUM_PLAYERS; i++) {
    hands[i] = new CHand();
  }
  targetScore    = 250;
  nilScore       = 50;
  blindNilScore  = 100;
  doubleNilBonus = 100;
  doubleBnBonus  = 200;
  nilBidSolo	 = FALSE;
  m_CurrDialog   = NULL;
}

CHands::~CHands() {
	for (char i=0; i<NUM_PLAYERS; i++) {
		CHand* h = hands[i];
		if (h) delete h;
		name[i].Empty();
	}
}

void
CHands::closeDialog() {
	if (m_CurrDialog) {
		m_CurrDialog->EndDialog(IDABORT);
		m_CurrDialog = NULL;
	}
}

/**
 * Reset an individual hand
 */
void
CHand::Reset() {
  for (char i=0; i<CARDS_IN_HAND+2; i++) {	// may temporarily have 2 extra cards in hand during passing
	  if (i < CARDS_IN_HAND)
		  slots[i].init(NULL);
	  else
		slots[i].setState(CARD_NOT_PRESENT);
  }
  cardsInHand = 0;
  cardList    = NULL;
  cardPlayed  = -1;
  tricksTaken = 0;
  passCount   = 0;
  bid         = 0;
  nil         = FALSE;
  canBn       = FALSE;
  passedCard[0] = -1;
  passedCard[1] = -1;
}

/**
 * Reset the hands of cards. Optionally reset the entire game.
 */
void
CHands::Reset(BOOL newGame ) {
  for (char i=0; i<NUM_PLAYERS; i++) {
    hands[i]->Reset();
  }
  trick = 0;
  suitLead = -1;
  trumpBroken = FALSE;
  bids = 0;
  teamBid[0]   = teamBid[1]   = 0;
  teamNil[0]   = teamNil[1]   = FALSE;
  blindNil[0]  = blindNil[1]  = FALSE;
  doubleNil[0] = doubleNil[1] = FALSE;
  if (newGame) {
	handsPlayed = 0;
	teamScore[0] = 0;
	teamScore[1] = 0;
	lastHandScore[0] = 0;
	lastHandScore[1] = 0;
	sandBags[0] = sandBags[1] = 0;
  }
  BOOL bnOpt = ((teamScore[1] > teamScore[0]) && ((teamScore[1] - teamScore[0]) >= 100)) ? TRUE : FALSE;
  setBnOpt(0, bnOpt);	// team 1 consists of hands 0 and 2
  setBnOpt(2, bnOpt);

  bnOpt = ((teamScore[0] > teamScore[1]) && ((teamScore[0] - teamScore[1]) >= 100)) ? TRUE : FALSE;
  setBnOpt(1, bnOpt);	// team 2 consists of hands 1 and 3
  setBnOpt(3, bnOpt);

  if (m_CurrDialog) {
	m_CurrDialog->EndDialog(IDABORT);
	m_CurrDialog = NULL;
  }
}

/**
 * Update the hand state when a trick is ended (which clears the card from the table),
 * and increment the winner's trick count.
 */
void
CHand::trickEnded(BOOL winner) {
  slots[cardPlayed].setState(CARD_PLAYED);
  cardPlayed = -1;
  if (winner)
	  tricksTaken++;
}

/**
 * Associate names with players and teams
 */
void
CHands::setPlayerName( int hand, CString name ) {
	this->name[hand] = name;
	char team = getTeam(hand) + 1;
	char player = ((hand == 0) || (hand == 1)) ? 1 : 2;
	if (name.GetLength() > 0) {		// zero-length implies player left, and we're erasing his name
		CString msg;
		msg.Format(IDS_JOINED, (const char *)name, team, player);
		Log::writeLog(msg);
	}
}

void
CHands::getPlayerName( int hand, CString& name ) {
	name = this->name[hand];
}

/**
 * Add a dealt card to a hand, sorted by
 * suit (Clubs->Diamonds->Hearts->Spades) and sorted
 * by face value within a suit (2->..->10->J->Q->K->A)
 *
 */
void
CHands::addTo( char hand, Card* card) {
  CHand* h = hands[hand];
  h->addTo(card);
}
void
CHand::addTo( Card* card) {
  cardsInHand++;
  Card* c = cardList;
  Card* prev = NULL;
  while(c != NULL) {
    if (c->getSuit() >= card->getSuit()) {
      break;
    }
    prev = c;
    c = c->getNext();
  }
  while(c != NULL) {
    if (c->getSuit() != card->getSuit()) {
      break;
    }
    if (c->getValue() > card->getValue()) {
      break;
    }
    prev = c;
    c = c->getNext();
  }
  if (prev == NULL) {
    cardList = card;
  }
  else {
    prev->setNext(card);
  }
  card->setNext(c);
}

/**
 * After dealing the cards, set the card slot positions
 * for the whole deck
 *
 * The 'cardsInHand' variable should contain between 11 and 15 (if passing is in progress),
 * though typically the value is 13. There are 15 slots, to accomodate up to two extra 
 * cards during passing. 
 */
void
CHand::setSlots() {
  Card* c = cardList;
  char i = 0;
  while (i<cardsInHand) {
	if ((i == passedCard[0]) || (i == passedCard[1])) {
	  slots[i].init( c, CARD_ON_TABLE );
	}
	else {
	  slots[i].init( c, CARD_UNPLAYED );
	}
	c = c->getNext();
    i++;
  }
  while (i<CARDS_IN_HAND+2) {	// during passing there may be 2 fewer/extra cards in the hand
	  slots[i].setState(CARD_NOT_PRESENT);
	  i++;
  }
  cardPlayed = -1;
}

void
CHand::setSlot(char slot, Card* card, char state) {
  slots[slot].init( card, state );
  if (state == CARD_ON_TABLE)
	  cardPlayed = slot;
}

/**
 * While loading saved state, set a specific card slot position
 */
void
CHands::setSlots() {
  for (char i=0; i<NUM_PLAYERS; i++) {
    hands[i]->setSlots();
  }
}

void
CHands::setSlot( char hand, char slot, Card* card, char state ) {
  hands[hand]->setSlot( slot, card, state );
}

/**
 * Find a card given its index into the deck
 */
Card*
CHand::showByIdx( char idx ) {
  Card* c = cardList;
  char i = 0;
  while (i<cardsInHand) {
	if (c->getIndex() == idx) {
		return c;
	}
	c = c->getNext();
	i++;
  }
  ASSERT(FALSE);
  return NULL;
}

Card*
CHands::showByIdx( char hand, char idx ) {
	return hands[hand]->showByIdx(idx);
}

/**
 * Play a card
 */
Card*
CHand::play( char slot ) {
	if (cardPlayed != -1) {
		slots[cardPlayed].setState(CARD_PLAYED);
	}
	slots[slot].setState(CARD_ON_TABLE);
	cardPlayed = slot;
	Card* c = slots[slot].getCard();
	return c;
}

Card*
CHands::play( char hand, char slot ) {
  char suit = hands[hand]->show(slot)->getSuit();
  if (suitLead == -1)
	  suitLead = suit;
  if (suit == SPADES)
	  trumpBroken = TRUE;
  return hands[hand]->play(slot);
}

/**
 * Remove selected card from hand, in preparation for passing to team mate
 */
Card*
CHand::passFrom( char idx ) {
	cardsInHand--;
	Card* c = cardList;
	Card* prev = NULL;
	BOOL found = FALSE;
	while(c != NULL) {
		if (c->getIndex() == idx) {
			found = TRUE;
			break;
		}
		prev = c;
		c = c->getNext();
	}
	ASSERT(found);
	if (prev == NULL) {
		cardList = c->getNext();
	}
	else {
		prev->setNext(c->getNext());
	}
	setSlots();			// update the slots
	return c;
}

void
CHand::passTo( Card* c ) {
	addTo( c );
	setSlots();
}

Card*
CHands::pass( char hand, char idx ) {
	Card* c = hands[hand]->passFrom(idx);
	char partner = hand + 2;
	if (partner >= NUM_PLAYERS)
		partner -= NUM_PLAYERS;
	hands[partner]->passTo(c);
	return c;
}

void
CHand::clearPass() {
	passedCard[0] = -1;
	passedCard[1] = -1;
	setSlots();
	passCount = 0;
}

void
CHands::clearPass( char hand ) {
	hands[hand]->clearPass();
}

char
CHand::getCardToPass( char idx ) {
	ASSERT((idx ==0) || (idx == 1));
	ASSERT(passCount == 2);
	char c = passedCard[idx];
	ASSERT(c != -1);
	passedCard[idx] = -1;
	return c;
}

char
CHands::getCardToPass( char hand, char idx ) {
	return hands[hand]->getCardToPass(idx);
}

void
CHand::prePass( char slot ) {
	ASSERT(passCount < 2);
	ASSERT(passedCard[passCount] == -1);
	passedCard[passCount] = slots[slot].getCard()->getIndex();
	slots[slot].setState(CARD_ON_TABLE);
	passCount++;
}

void
CHands::prePass( char hand, char slot ) {
	hands[hand]->prePass(slot);
}

/**
 * Show a card in a hand
 */
Card*
CHand::show( char slot ) {
	Card* c = slots[slot].getCard();
	return c;
}

Card*
CHands::show( char hand, char slot ) {
	return hands[hand]->show(slot);
}

/**
 * Show the state of a card in a hard
 * (e.g. unplayed, on the table, or played)
 */
char
CHand::showState( char slot ) {
	return slots[slot].getState();
}

char
CHands::showState( char hand, char slot ) {
	return hands[hand]->showState(slot);
}

/**
 * Uodate card state
 */
void
CHand::setState( char slot, char state ) {
	slots[slot].setState(state);
}

void
CHands::setState( char hand, char slot, char state ) {
	hands[hand]->setState( slot, state );
}

/**
 * Set the bid for a hand
 */
char
CHands::setBid( char hand, char bid, BOOL nil ) {
	
	bids++;
	CString msg;
	char partner = hand + 2;
	char team = getTeam(hand);
	if (partner >= NUM_PLAYERS) partner -= NUM_PLAYERS;

	// if 3rd or 4th bidder, set the team bid

	if (bids > 2) {
			
		// if 3rd or 4th bidder goes nil, team bid is partner's hint

		if (nil) {
			ASSERT(bid == 0);
			msg.Format(IDS_BID_NIL, name[hand]);
			Log::writeLog( msg );
			hands[hand]->setBid( bid, nil );
			bid = hands[partner]->getBid();
			teamBid[team] = bid;
			if (canBlindNil(hand)) {
				msg.LoadString(IDS_BLIND_NIL_BID);
				Log::writeLog( msg );
				blindNil[team] = TRUE;
			}
		}
		else {
			msg.Format(IDS_BID_FOR_TEAM, name[hand], bid);
			Log::writeLog(msg);
			teamBid[team] = bid;
			bid -= hands[partner]->getBid();	// infer hint from team bid
			hands[hand]->setBid( bid, nil );	// ... not necessary, but may be useful
		}
	}

	// if 1st or 2nd bidder, this is just a hint

	else {
		if (nil) {
			ASSERT(bid == 0);
			msg.Format(IDS_BID_NIL, name[hand]);
			Log::writeLog( msg );
		}
		else {
			msg.Format(IDS_HINTED, name[hand], bid);
			Log::writeLog(msg);
		}
		hands[hand]->setBid( bid, nil );
		if (nil && canBlindNil(hand)) {
			msg.LoadString(IDS_BLIND_NIL_BID);
			Log::writeLog( msg );
			blindNil[team] = TRUE;
			setBnOpt(partner, FALSE);			// don't offer blind nil to partner
		}
	}
	teamNil[team] |= nil;
	doubleNil[team] = nil && hands[partner]->nilBid();
	if (doubleNil[team]) {
		msg.Format(IDS_DOUBLE_NIL_BID, (team+1));
		Log::writeLog(msg);
	}

	if (bids == 4) {
		Log::writeLog( "--------------------" );
	}
	
	return bids;
}

void
CHands::setBnOpt( char hand, BOOL opt ) {
	hands[hand]->setBnOpt( opt );
}

/**
 * Check if a card is a valid play
 */
BOOL
CHands::isLegalPlay( char hand, char slot ) {
	char suit = hands[hand]->show(slot)->getSuit();
	char val  = hands[hand]->show(slot)->getValue();
	if ((suitLead != -1) && (suit != suitLead)) {
		if (hands[hand]->haveSuit(suitLead)) {			// must follow suit
			CString m;
			m.LoadString(IDS_FOLLOW_SUIT);
			CMsgBox dlg;
			dlg.init(m);
			m_CurrDialog = &dlg;
			dlg.DoModal();
			m_CurrDialog = NULL;
			return FALSE;
		}
	}
	if (suit == SPADES) {
		if (trick == 0) {
			if (!hands[hand]->allTrump()) {				// can't trump the first trick
				CString m;
				m.LoadString(IDS_TRUMP1);
				CMsgBox dlg;
				dlg.init(m);
				m_CurrDialog = &dlg;
				dlg.DoModal();
				m_CurrDialog = NULL;
				return FALSE;
			}
		}
		else {
			if ((suitLead == -1) && (!trumpBroken)) {	// can't lead trump unless trump is broken
				if (!hands[hand]->allTrump()) {
					CString m;
					m.LoadString(IDS_TRUMP2);
					CMsgBox dlg;
					dlg.init(m);
					m_CurrDialog = &dlg;
					dlg.DoModal();
					m_CurrDialog = NULL;
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

/**
 * Check if player has any cards in a specific suit
 */
BOOL
CHand::haveSuit( char suit ){
	for (int i=0; i<CARDS_IN_HAND; i++) {
		if ((slots[i].getSuit() == suit) && (slots[i].getState() == CARD_UNPLAYED))
			return TRUE;
	}
	return FALSE;
}

/**
 * Check if a player's hand contains only trump cards
 */
BOOL
CHand::allTrump() {
	for (int i=0; i<CARDS_IN_HAND; i++) {
		if ((slots[i].getSuit() != SPADES) && (slots[i].getState() == CARD_UNPLAYED))
			return FALSE;
	}
	return TRUE;
}

/**
 * Figure out who won the trick
 */
char
CHands::scoreTrick() {
	char winner = -1;
	BOOL trumped = FALSE;
	char hiScore = 0;

	for (int i=0; i<NUM_PLAYERS; i++) {
		char slot = getCardPlayed(i);
		char s = hands[i]->show(slot)->getSuit();
		char v = hands[i]->show(slot)->getValue();
		if (s == suitLead) {
			if ((v > hiScore) && (!trumped)) {
				hiScore = v;
				winner = i;
			}
		}
		else {
			if (s == SPADES) {
				if (trumped) {
					if (v > hiScore) {
						hiScore = v;
						winner = i;
					}
				}
				else {
					trumped = TRUE;
					hiScore = v;
					winner = i;
				}
			}
		}
	}
	ASSERT(winner > -1);
	Log::writeLog( name[winner] + " took the trick" );
	for (i=0; i<NUM_PLAYERS; i++) {
		BOOL w = (winner == i) ? TRUE : FALSE;
		hands[i]->trickEnded(w);
	}
	Log::trickEnded();
	suitLead = -1;
	trick++;
	return winner;
}

/**
 * Figure out who won the hand, and update the game scores
 */
int
CHands::scoreHand( int* team1, int* team2, int* total1, int* total2, char* handsPlayed ) {

	// Get team 1 results

	char bid = teamBid[0];
	char taken, t[4];
	CString msg;

	// player must make the bid solo if partner went nil ?

	t[0] = hands[0]->getTricksTaken();
	t[2] = hands[2]->getTricksTaken();
	if (nilBidSolo) {
		if (hands[0]->nilBid()) {
			msg.Format(IDS_NIL_TRICKS, (const char*)name[0], t[0]);
			Log::writeLog(msg);
			t[0] = 0;
		}
		if (hands[2]->nilBid()) {
			msg.Format(IDS_NIL_TRICKS, (const char*)name[2], t[2]);
			Log::writeLog(msg);
			t[2] = 0;
		}
	}
	taken = t[0] + t[2];

	char bags;
	int  score;
	char word[10] = "trick";
	if (bid != 1)
		strcat(word, "s");
	msg.Format(IDS_TEAM_RESULTS, 1, bid, word, taken);
	Log::writeLog(msg);

	// Team 1 made its bid 

	if (taken >= bid) {
		bags = (taken - bid);
		score = (bid * 10) + bags;
		sandBags[0] += bags;
		strcpy(word, "sandbag");
		if (bags != 1)
			strcat(word, "s");
		msg.Format(IDS_TEAM_SCORE, 1, bags, word, sandBags[0]);
		Log::writeLog(msg);

		// Team 1 took too many bags

		if (sandBags[0] >= 10) {
			msg.Format(IDS_SANDBAG, 1);
			Log::writeLog( msg );
			sandBags[0] -= 10;
			score -= 100;
		}
	}
	else {
		msg.Format(IDS_BID_SET, 1);
		Log::writeLog( msg );
		score = -10 * bid;
	}

	// Check if either team member bid nil

	if (hands[0]->nilBid()) {
		score += calcNilScore(0);
	}

	if (hands[2]->nilBid()) {
		score += calcNilScore(2);
	}

	msg.Format(IDS_TEAM_SUMMARY, 1, score);
	Log::writeLog(msg);
	*team1 = score;

	// Get team 2 results

	bid = getTeamBid(1);
	t[1] = hands[1]->getTricksTaken();
	t[3] = hands[3]->getTricksTaken();
	
	// player must make the bid solo if partner went nil ?

	if (nilBidSolo) {
		if (hands[1]->nilBid()) {
			msg.Format(IDS_NIL_TRICKS, (const char*)name[1], t[1]);
			Log::writeLog(msg);
			t[1] = 0;
		}
		if (hands[3]->nilBid()) {
			msg.Format(IDS_NIL_TRICKS, (const char*)name[3], t[3]);
			Log::writeLog(msg);
			t[3] = 0;
		}
	}
	taken = t[1] + t[3];

	strcpy(word, "trick");
	if (bid != 1)
		strcat(word, "s");
	msg.Format(IDS_TEAM_RESULTS, 2, bid, word, taken);
	Log::writeLog(msg);

	// Team 2 made its bid 

	if (taken >= bid) {
		bags = (taken - bid);
		score = (bid * 10) + bags;
		sandBags[1] += bags;
		strcpy(word, "sandbag");
		if (bags != 1)
			strcat(word, "s");
		msg.Format(IDS_TEAM_SCORE, 2, bags, word, sandBags[1]);
		Log::writeLog(msg);

		// Team 2 took too many bags

		if (sandBags[1] >= 10) {
			msg.Format(IDS_SANDBAG, 2);
			Log::writeLog( msg );
			sandBags[1] -= 10;
			score -= 100;
		}
	}
	else {
		msg.Format(IDS_BID_SET, 2);
		Log::writeLog( msg );
		score = -10 * bid;
	}
	
	// Check if either team member bid nil

	if (hands[1]->nilBid()) {
		score += calcNilScore(1);
	}

	if (hands[3]->nilBid()) {
		score += calcNilScore(3);
	}

	msg.Format(IDS_TEAM_SUMMARY, 2, score);
	Log::writeLog(msg);
	*team2 = score;
	
	this->handsPlayed++;
	*handsPlayed = this->handsPlayed;
	lastHandScore[0] = *team1;
	lastHandScore[1] = *team2;
	teamScore[0] += *team1;
	teamScore[1] += *team2;
	*total1 = teamScore[0];
	*total2 = teamScore[1];
	msg.Format(IDS_TEAM_TOTALS, teamScore[0], teamScore[1]);
	Log::writeLog(msg);

	if ((teamScore[0] > teamScore[1]) && (teamScore[0] > targetScore)) {
		msg.Format(IDS_TEAM_WINNERS, 1, (const char*)name[0], (const char*)name[2]);
		Log::writeLog(msg);
		return 1;
	}
	if ((teamScore[1] > teamScore[0]) && (teamScore[1] > targetScore)) {
		msg.Format(IDS_TEAM_WINNERS, 2, (const char*)name[0], (const char*)name[2]);
		Log::writeLog(msg);
		return 2;
	}
	if ((teamScore[0] == teamScore[1]) && (teamScore[1] > targetScore)) {
		msg.LoadString(IDS_TIE_GAME);
		Log::writeLog(msg);
		return 3;
	}
	
	if ((teamScore[0] < teamScore[1]) && (teamScore[0] < (0-targetScore))) {
		msg.Format(IDS_BACKDOOR, 1);
		Log::writeLog(msg);
		msg.Format(IDS_TEAM_WINNERS, 2, (const char*)name[0], (const char*)name[2]);
		Log::writeLog(msg);
		return 2;
	}
	if ((teamScore[1] < teamScore[0]) && (teamScore[1] < (0-targetScore))) {
		msg.Format(IDS_BACKDOOR, 2);
		Log::writeLog(msg);
		msg.Format(IDS_TEAM_WINNERS, 1, (const char*)name[0], (const char*)name[2]);
		Log::writeLog(msg);
		return 1;
	}
	if ((teamScore[0] == teamScore[1]) && (teamScore[1] < (0-targetScore))) {
		msg.LoadString(IDS_DOUBLE_BACKDOOR);
		Log::writeLog(msg);
		msg.LoadString(IDS_TIE_GAME);
		Log::writeLog(msg);
		return 3;
	}
	Log::writeLog( "--------------------" );
	return 0;		// game not over
}

/**
 * Calculate the score for a Nil bid
 */
int
CHands::calcNilScore( char hand ) {
	CString msg;
	int score = 0;
	char team = getTeam(hand);

	// Nil was set

	if (hands[hand]->getTricksTaken() > 0) {
		if (blindNil[team]) {
			if (doubleNil[team]) {
				msg.Format(IDS_DBN_SET, (const char*)name[hand], doubleBnBonus);
				score -= doubleBnBonus;
			}
			else {
				msg.Format(IDS_BN_SET, (const char*)name[hand], blindNilScore);
				score -= blindNilScore;
			}
		}
		else {
			if (doubleNil[team]) {
				msg.Format(IDS_DN_SET, (const char*)name[hand], doubleNilBonus);
				score -= doubleNilBonus;
			}
			else {
				msg.Format(IDS_NIL_SET, (const char*)name[hand], nilScore);
				score -= nilScore;
			}
		}
	}

	// Nil was made

	else {
		if (blindNil[team]) {
			if (doubleNil[team]) {
				msg.Format(IDS_DBN_MADE, (const char*)name[hand], doubleBnBonus);
				score += doubleBnBonus;
			}
			else {
				msg.Format(IDS_BN_MADE, (const char*)name[hand], blindNilScore);
				score += blindNilScore;
			}
		}
		else {
			if (doubleNil[team]) {
				msg.Format(IDS_DN_MADE, (const char*)name[hand], doubleNilBonus);
				score += doubleNilBonus;
			}
			else {
				msg.Format(IDS_NIL_MADE, (const char*)name[hand], nilScore);
				score += nilScore;
			}	
		}
	}
	Log::writeLog(msg);
	return score;
}

/**
 * Return scoring details
 */
int
CHands::getScores( int* team1, int* team2, int* total1, int* total2, char* handsPlayed ) {
	*team1 = lastHandScore[0];
	*team2 = lastHandScore[1];
	*total1 = teamScore[0];
	*total2 = teamScore[1];
	*handsPlayed = this->handsPlayed;

	// check for a winner

	if ((teamScore[0] > teamScore[1]) && (teamScore[0] > targetScore))
		return 1;	// team 1 won
	if ((teamScore[1] > teamScore[0]) && (teamScore[1] > targetScore))
		return 2;	// team 2 won
	if ((teamScore[0] == teamScore[0]) && (teamScore[1] > targetScore))
		return 3;	// tie

	// check if someone went out the back door

	if ((teamScore[0] < teamScore[1]) && (teamScore[0] < (0 - targetScore)))
		return 2;	// team 2 won
	if ((teamScore[1] < teamScore[0]) && (teamScore[1] < (0 - targetScore)))
		return 1;	// team 1 won
	if ((teamScore[0] == teamScore[0]) && (teamScore[0] < (0 - targetScore)))
		return 3;	// tie

	return 0;		// game not over
}

/**
 * Return tricks taken by a team (input = hand)
 */
char
CHands::getTeamTricks( char hand ) {
	char partner = hand + 2;
	if (partner >= NUM_PLAYERS)
		partner -= NUM_PLAYERS;
	return (hands[hand]->getTricksTaken() + hands[partner]->getTricksTaken());
}

/**
 * save/restore game state
 */
unsigned char*
CHands::saveState(unsigned char* p, char myHand) {
	*p++ = trick;
	*p++ = suitLead;
	*p++ = (trumpBroken) ? 1 : 0;
	*p++ = handsPlayed;
	*p++ = bids;
	int myTeam = ((myHand == 0) || (myHand == 2)) ? 0 : 1;
	int i,j,hand;
	for (i=myTeam, j=0; j<NUM_TEAMS; i++, j++ ) {
		if (i == NUM_TEAMS)
			i = 0;
		memcpy(p, &teamScore[i], sizeof(teamScore[i]));
		p += sizeof(teamScore[i]);
		memcpy(p, &lastHandScore[i], sizeof(lastHandScore[i]));
		p += sizeof(lastHandScore[i]);
		*p++ = teamBid[i];
		*p++ = (teamNil[i]) ? 1 : 0;
		*p++ = (blindNil[i]) ? 1 : 0;
		*p++ = (doubleNil[i]) ? 1 : 0;
		*p++ = sandBags[i];
	}
	for (hand=myHand, j=0 ; j<NUM_PLAYERS ; j++, hand++) {
		if (hand >= NUM_PLAYERS)
			hand = 0;
		p = hands[hand]->saveState(p);
	}
	memcpy(p, &targetScore, sizeof(targetScore));
	p += sizeof(targetScore);
	memcpy(p, &nilScore, sizeof(nilScore));
	p += sizeof(nilScore);
	memcpy(p, &blindNilScore, sizeof(blindNilScore));
	p += sizeof(blindNilScore);
	memcpy(p, &doubleNilBonus, sizeof(doubleNilBonus));
	p += sizeof(doubleNilBonus);
	memcpy(p, &doubleBnBonus, sizeof(doubleBnBonus));
	p += sizeof(doubleBnBonus);
	*p++ = (nilBidSolo) ? 1 : 0;

	return p;
}

unsigned char*
CHand::saveState( unsigned char* p ) {
	*p++ = cardPlayed;
	*p++ = bid;
	*p++ = (nil) ? 1 : 0;
	*p++ = (canBn) ? 1 : 0;
	*p++ = tricksTaken;
	*p++ = passCount;
	*p++ = cardsInHand;
	*p++ = passedCard[0];
	*p++ = passedCard[1];
	char inHand = 0;
	for ( int i=0; i<CARDS_IN_HAND+2; i++) {
		char state = slots[i].getState();
		if (state != CARD_NOT_PRESENT) {
		  Card* c = slots[i].getCard();
		  *p++ = c->getSuit();
		  *p++ = c->getValue();
		  *p++ = state;
		  inHand++;
		}
	}
	ASSERT(inHand == cardsInHand);
	return p;
}

unsigned char*
CHands::loadState(unsigned char* p, CDeck* d) {
	trick = *p++;
	suitLead = *p++;
	trumpBroken = (*p++) ? 1 : 0;
	handsPlayed = *p++;
	bids = *p++;
	for (int i=0; i<NUM_TEAMS; i++ ) {
		memcpy(&teamScore[i], p, sizeof(teamScore[i]));
		p += sizeof(teamScore[i]);
		memcpy(&lastHandScore[i], p, sizeof(lastHandScore[i]));
		p += sizeof(lastHandScore[i]);
		teamBid[i]     = *p++;
		teamNil[i]     = (*p++) ? 1 : 0;
		blindNil[i]    = (*p++) ? 1 : 0;
		doubleNil[i]   = (*p++) ? 1 : 0;
		sandBags[i]    = *p++;
	}
	for (int hand=0 ; hand<NUM_PLAYERS ; hand++) {
		p = hands[hand]->loadState(p, d);
	}
	memcpy(&targetScore, p, sizeof(targetScore));
	p += sizeof(targetScore);
	memcpy(&nilScore, p, sizeof(nilScore));
	p += sizeof(nilScore);
	memcpy(&blindNilScore, p, sizeof(blindNilScore));
	p += sizeof(blindNilScore);
	memcpy(&doubleNilBonus, p, sizeof(doubleNilBonus));
	p += sizeof(doubleNilBonus);
	memcpy(&doubleBnBonus, p, sizeof(doubleBnBonus));
	p += sizeof(doubleBnBonus);
	nilBidSolo = (*p++) ? 1 : 0;
	return p;
}

unsigned char*
CHand::loadState( unsigned char* p, CDeck* d ) {
	cardPlayed = *p++;
	bid = *p++;
	nil = (*p++) ? 1 : 0;
	canBn = (*p++);
	tricksTaken = *p++;
	passCount = *p++;
	char cards = *p++;
	passedCard[0] = *p++;
	passedCard[1] = *p++;
	for ( int i=0; i<cards; i++) {
		char suit  = *p++;
		char val   = *p++;
		char state = *p++;
		ASSERT(state != CARD_NOT_PRESENT);
		Card* card = d->pick(suit, val);
		addTo( card );
		setSlot( i, card, state );
	}
	ASSERT(cardsInHand == cards);
	for (i=cards; i<CARDS_IN_HAND+2; i++) {
		setState( i, CARD_NOT_PRESENT );
	}
	return p;
}