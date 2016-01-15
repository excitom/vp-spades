//
// Deck (deck of cards) class implementation
//
//
#include "stdafx.h"
#include "card.h"
#include "deck.h"
  
/**
 * Constructor - create all the cards in tne deck
 */
CDeck::CDeck() {
  anchor = NULL;
  for (int suit=0; suit<NUM_PLAYERS; suit++) {
    for (int faceValue=TWO; faceValue<=ACE; faceValue++) {
      Card* card = new Card(suit, faceValue);
      anchor = card->init(anchor);
    }
  }
}
CDeck::~CDeck() {
	while (anchor != NULL) {
		Card* c = anchor;
		anchor = c->nextCard();
		delete c;
	}
}
  
/**
 * Shuffle the deck
 * (Well, not really ... actually the cards are gathered up from the 
 *  permanent list and relinked to the temporary list. This is in
 *  preparation for dealing the cards, which is done by randomly
 *  taking cards out of the temporary list and linking them to 
 *  slots in each player's hand.)
 */
void
CDeck::shuffle() {
  deck = NULL;
  for (Card* card = anchor; card !=NULL; card = card->nextCard()) {
    deck = card->stack(deck);
  }
}

/**
 * Deal a card from the deck. This is intended for randomly pulling 
 * cards out of an ever-shortening linked list.
 */
Card*
CDeck::deal(char idx) {
  if (idx >= CARDS_IN_DECK) {
	ASSERT(FALSE);
    return NULL;
  }
  int i = 0;
  Card* c = deck;
  Card* prev = NULL;
  while (i < idx) {
    prev = c;
    c = c->getNext();
    i++;
  }
  Card* next = c->getNext();
  if (prev == NULL) {
    deck = next;	// dealing first card
  }
  else {
    prev->setNext(next);
  }
  return c;
}

/**
 * Pick a specific card out of the list. This is intended for
 * transferring state information from the game leader, who randomly
 * shuffled the deck, to the other game participants.
 */
Card*
CDeck::pick(char suit, char val) {
	if ((suit < 0) || (suit > NUM_PLAYERS) || (val < 2) || (val > ACE)) {
		ASSERT(FALSE);
		return NULL;
	}
	Card* c = deck;
	Card* prev = NULL;
	while (c != NULL) {
		if ((c->getSuit() == suit) && (c->getValue() == val)) {
			Card* next = c->getNext();
			if (prev == NULL) {
				deck = next;	// picking first card
			}
			else {
				prev->setNext(next);
			}
			return c;
		}
		prev = c;
		c = c->getNext();
	}
	ASSERT(FALSE);
	return NULL;
}