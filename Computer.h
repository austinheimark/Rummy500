// Computer.h - header file for the computer
// Written by Austin Heimark

#pragma once
#include <iostream>
#include "Player.h"

using namespace std;

// Sub-class of Player
class Computer: public Player
{
public:
	// Init-constructor calls base class
	Computer(string name, int score=0) : Player(name,score)
	{
		Name = name;
		Score = score;
	}

	// Overriding of the same method from Player class
	virtual int WhatDeckToPickFrom(Cards& deck) const;

	// Overriding of the same method from Player class
	virtual int WhatCardToDiscard (Cards& deck) const;

	// Overriding to display the computer's melded cards
	virtual void DisplayMeldedCards () const;

	// Returns true if the two card number d from the deck's pick from
	// pile is the same as card p from the player's hand
	bool CompareCardsOnPickFromPile (Cards& deck, const int& d, const int& p) const;

	// Determines if the comp wants to meld initially
	vector<int> FirstTimeMeld (Cards& deck) const;

	// Enters this method because the player wants to meld cards during the second chance
	virtual vector<int> SecondTimeMeld (Cards& deck) const;

	// Overriding GamePlay from the Player class
	virtual void GamePlay (Cards& deck, vector<string> compsMeldedCards);
};