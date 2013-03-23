// Player.h - Header file for the player
// Written by Austin Heimark

#pragma once
#include <iostream>
#include <vector>
#include <string>

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

protected:
	string Name;	// Player name
	int Score;		// Player score
	vector<string> MeldedCards;
	vector<string> Hand;
};