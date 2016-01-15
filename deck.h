#ifndef __CDECK
#define __CDECK

#define CARDS_IN_DECK	52

#define TWO 2
#define ACE 14

class CDeck {
  private:
    Card*	anchor;
    Card*	deck;

  public:
    CDeck();
    ~CDeck();
    void shuffle();
    Card* cardsLeft() { return deck; }
    Card* deal( char idx );
	Card* pick( char suit, char val );
};
#endif