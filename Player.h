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

#define PICK_FROM_DECK -1
#define YES 1
#define TERMINATE_NUMBER -1
#define RANK_OFFSET 2
#define TWO_THROUGH_NINE_PTS 5
#define TEN_THROUGH_KING_PTS 10
#define ACE_POINTS 15
#define EMPTY 0
#define NUMBER_TO_CHECK 2

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
	virtual string GetHandValue(const int& number) const;

	// Inserts card into the hand at the end of the handS
	virtual void InsertIntoHand(const string& card);

	// Displays the hand
	// Does not need to be virtual (once done testing)
	virtual void DisplayHand() const;

	// Determine what deck the player will pick from 
	virtual int WhatDeckToPickFrom(Cards& deck) const;

	// Determines what card the player will discard
	virtual int WhatCardToDiscard () const;

	// Sorts the players hand
	void OrganizeHand();

	// Returns the card at this location
	virtual string ReturnCard (const int& number) const;

	// Pops the card at number from the Hand
	virtual void PopCard (const int& number);

	// Display the melded cards
	virtual void DisplayMeldedCards () const;

	// Populates melded cards and organizes them!
	virtual void PopulateMeldedCards (vector<int>& CardSpotsIWillMeld);

	// Enters this method because the player wants to meld cards
	virtual vector<int> SecondTimeMeld () const;

	// Call this function after each hand, need to reset the cards you have to 0!
	virtual void ClearHandAndMeldedCards();

	// Populates a vector of the cards that the player will meld from their own hand
	vector<int> CardsToMeld() const;

	// The main gameplay for the game, iterates through each turn of every hand
	virtual void GamePlay (Cards& deck, vector<string>& compsMeldedCards, const string& compsName);

	// Must insert the cards from player's choice all the way up to the end of the pile into the player's hand
	// Called if the player wants to pick from the pick up pile
	virtual void InsertFromPickFromPile (Cards& deck, const int& choice);

	// Discards the card in the player's hand at spot cardSpot
	virtual void DiscardCard (Cards& deck, const int& cardSpot);

	// Retruns a vector of the computer's melded cards
	virtual vector<string> ReturnVectorOfMyMeldedCards () const;

	// Returns a vector of the card locations that the player wants to meld
	vector<int> RetrieveMeldSpots () const;

protected:
	string Name;
	int Score;
	vector<string> MeldedCards;
	vector<string> Hand;
};