#ifndef __CARDS
#define __CARDS
#define CARDS_IN_DECK	52
#define CARDS_IN_HAND	(52/4)
#define NUM_PLAYERS		4

#define CLUBS		0
#define DIAMONDS	1
#define HEARTS		2
#define SPADES		3

//
// The Card class is used for a linked list of cards. 
// The CardSlot class is used for an array of cards corresponding to the player's current hand,
// where the array index corresponds to the physical position of the card on the game table.
//

class Card {
  private:
    Card*	next;
    Card*	tmpNext;
    char	suit;
    char	faceValue;

  public:
    Card(char suit, char faceValue);
    ~Card() {}
    Card* init( Card* anchor);
    Card* stack( Card* anchor);
    Card* nextCard();
    Card* getNext();
    void  setNext(Card* c);
    char  getSuit() { return this->suit; }
    char  getValue() { return this->faceValue; }
	char  getIndex() { return (this->suit * CARDS_IN_HAND) + this->faceValue; }
};

class CardSlot {
  private:
	Card*	card;
	char	state;
// card states
#define CARD_UNPLAYED	0
#define CARD_ON_TABLE	1
#define CARD_PLAYED		2
#define CARD_NOT_PRESENT		3

  public:
	CardSlot() {}
	~CardSlot() {}
	void	init(Card* card) { init(card, CARD_UNPLAYED); }
	void	init(Card* card, char state);
	char	getSuit()  { return this->card->getSuit(); }
	char	getValue() { return this->card->getValue(); }
	Card*	getCard()  { return this->card; }
	char	getState() { return this->state; }
	int		getIndex() { return (this->card->getIndex()); }
	void	setState(char s) { this->state = s; }
};
#endif