// Computer.h - header file for the computer
// Written by Austin Heimark

#pragma once
#include <iostream>
#include "Player.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

#define DASH "-"

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
	// Computer needs to have intelligent decisions
	virtual int WhatDeckToPickFrom(Cards& deck) const;

	// Overriding of the same method from Player class
	// Discards a random card out of the computer's hand
	virtual int WhatCardToDiscard (Cards& deck) const;

	// Overriding to display the computer's melded cards (because want to display the name of the computer)
	virtual void DisplayMeldedCards () const;

	// Enters this method because the player wants to meld cards during the second chance
	// Will first test to see if it can meld cards that are all of the same rank
	// If it cannot, then it will test to meld cards of consecuitve rank and the same suit
	virtual vector<int> SecondTimeMeld () const;

	// Overriding GamePlay from the Player class, because the computer has different methods
	// to determine it's gameplay
	void GamePlay (Cards& deck);
};