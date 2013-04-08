// Player.h - Header file for the player
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cards.h"

using namespace std;

class Player
{
public:
	// Init-constructor, gets the player name and 
	Player(string name, int score = 0);

	// Returns the player's name
	virtual string GetName() const;

	// Returns the player's score
	virtual int GetScore() const;

	// Returns the size of the player's hand
	virtual int GetHandSize() const;

	// Calculates the players score
	// Adds up the score of the player's melded cards
	// Then subtracts the cards left in the player's hand
	virtual void CalculateScore();

	// Returns the Value of the hand at number
	virtual string GetHandValue(int number) const;

	// Inserts card into the hand at the end of the handS
	virtual void InsertIntoHand(string card);

	// Displays the hand
	// Does not need to be virtual (once done testing)
	virtual void DisplayHand() const;

	// Determine what deck the player will pick from 
	virtual int WhatDeckToPickFrom(Cards deck) const;

	// Returns true if the two card number d from the deck's pick from
	// pile is the same as card p from the player's hand
	virtual bool CompareCardsOnPickFromPile (Cards deck,int d,int p) const;

	// Returns true if the player can meld and false if cannot
	virtual int TestIfCanMeld (Cards deck, int number) const;

	// Determines what card the player will discard
	virtual int WhatCardToDiscard (Cards deck) const;

	// Group the players cards together to make the hand easier to view
	virtual void OrganizeHand () const;

	// Returns the card at this location
	virtual string ReturnCard (int number);

	virtual void PopCard (int number);

protected:
	string Name;	// Player name
	int Score;		// Player score
	vector<string> MeldedCards;
	vector<string> Hand;
};