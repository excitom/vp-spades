/*
 * Card class implementation
 *
 * Cards are kept on two linked lists. When the deck is initialized
 * all the cards are linked onto a list and never are removed. This
 * is the anchored list. When the deck is reshuffled, the anchored list
 * is used to recreate the deck.
 * 
 * As cards are shuffled into the deck, they are linked onto another
 * list (the deck). As cards are dealt, they are removed from the deck
 * and the same link pointer is used to link the cards into a hand.
 *
 * The 'next' pointer is for the permanent, anchored list and the
 * 'tmpNext' pointer is for the temporary lists.
 */
#include "stdafx.h"
#include "card.h"

/**
 * Constructor
 */
Card::Card(char suit, char faceValue) {
  next = NULL;
  tmpNext = NULL;
  this->suit = suit;
  this->faceValue = faceValue;
}

/**
 * Link card to the permanent (anchored) list
 */
Card*
Card::init(Card* anchor) {
  this->next = anchor;
  return this;
}

/**
 * Link card to a temporary list
 */
Card*
Card::stack(Card* deck) {
  this->tmpNext = deck;
  return this;
}

/**
 * A get next card pointer from the anchored list
 */
Card*
Card::nextCard() {
  return this->next;
}

/**
 * A get next card pointer from a temporary list
 */
Card*
Card::getNext() {
  return this->tmpNext;	
}

/**
 * Link a card to a temporary list
 */
void
Card::setNext(Card* next) {
  this->tmpNext = next;
}

/**
 * Initialize a card slot
 */
void
CardSlot::init(Card* card, char state) { 
	this->card = card; 
	this->state = state;
}
