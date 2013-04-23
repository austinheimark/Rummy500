// Cards.h - Header file for the cards
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string> 
#include <algorithm>
#include <ctime>

using namespace std;

#define DECK_SIZE 52
#define CARDS_PER_PLAYER 7
#define NUMBER_OF_RANKS 13
#define NUMBER_OF_SUITS 4
#define RANK_OFFSET 2

enum Rank
{
	Two, 
	Three, 
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

enum Suit
{
	D,
	H,
	S,
	C
};

class Cards
{
public:
	// Initializes the deck with values
	void InitializeDeck();

	// Shuffles the deck
	void ShuffleDeck();

	// Displays the cards to choose from
	void DisplayAvailableCards() const;

	// Returns the card in the deck at number
	string ReturnCard(const int& number) const;

	// Pops a card off of the top of the deck
	void PopOffCard();

	// Returns the size of the deck
	int GetDeckSize() const;

	// Returns the size of the pick up pile
	int GetPickFromPileSize() const;

	// Populates the pick from
	void AdjustPickPile();

	// Returns card at number from the pick from pile
	string GetPickFromPileCard(const int& number) const;

	// Inserts card at the end of the pick from pile
	void InsertIntoPickFromPile(const string& card);

	// Pops the top card off of the pick up pile
	void PopPickFromPileCard();

	// Returns the top card from the deck
	string TopDeckCard () const;

private:
	vector<string> Deck;
	vector<string> PickFromPile;
};