// Cards.h - Header file for the cards
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string> 

using namespace std;

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

private:
	vector<string> Deck;
	vector<string> PickFromPile;
};