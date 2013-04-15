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

	// Overriding of the same function from Player class
	virtual int WhatDeckToPickFrom(Cards deck) const;

	// Overriding of the same function from Player class
	virtual int WhatCardToDiscard (Cards deck) const;

	vector<string> ReturnVectorOfMyMeldedCards () const;

	virtual void DisplayMeldedCards () const;


};