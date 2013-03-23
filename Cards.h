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


	void PopulatePickPile();
private:
	vector<string> Deck;
	vector<string> PickFromPile;
};