// Player.h - Header file for the player
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
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

	// Start checking from number
	// If can meld, return the number card that can be melded
	// If cannot meld, return NOT_POSSIBLE
	virtual int TestIfCanMeld (Cards& deck, vector<string> checkTheseCards) const;

	// Determines what card the player will discard
	virtual int WhatCardToDiscard (Cards deck) const;

	// Sorts the players hand
	void OrganizeHand();

	// Returns the card at this location
	virtual string ReturnCard (int number) const;

	// Pops the card at number from the Hand
	virtual void PopCard (int number);

	// Display the melded cards
	virtual void DisplayMeldedCards () const;

	// Populates melded cards and organizes them!
	virtual void PopulateMeldedCards (vector<int> CardSpotsIWillMeld);

	// Enters this method because the player wants to meld cards
	virtual vector<int> SecondTimeMeld (Cards& deck) const;

	// Call this function after each hand, need to reset the cards you have to 0!
	virtual void ClearHandAndMeldedCards();

protected:
	string Name;	// Player name
	int Score;		// Player score
	vector<string> MeldedCards;
	vector<string> Hand;
};