// Cards.h - Header file for the cards
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string> 

using namespace std;

class Cards
{
public:
	// Shuffles and initializes the deck
	void ShuffleDeck();

	// Displays the cards to choose from
	void DisplayAvailableCards() const;

	// Returns the card in the deck at number
	string ReturnCard(int number) const;

	// Pops a card off of the vector
	void PopOffCard();

	// Returns the size of the deck
	int GetDeckSize() const;

	// Returns the size of the pick up pile
	int GetPickFromPileSize() const;

	// Populates the pick from
	void AdjustPickPile();

	// Returns card at number from the pick from pile
	string GetPickFromPileCard(int number) const;

	// Inserts card at the end of the pick from pile
	void InsertIntoPickFromPile(string card);

private:
	vector<string> Deck;
	vector<string> PickFromPile;
};
