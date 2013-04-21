// Player.cpp - Header file for the player
// Written by Austin Heimark

#include "Player.h"

#define PICK_FROM_DECK -1
#define NOT_POSSIBLE -1
#define YES 1
#define TERMINATE_NUMBER -1
#define RANK_OFFSET 2

Player::Player(string name, int score)
{
	Name = name;
	Score = score;
}

string Player::GetName() const
{
	return Name;
}

int Player::GetScore() const
{
	
	return Score;
}

void Player::CalculateScore()
{
	for (int i = 0; i < MeldedCards.size(); i++)
	{
		string cardRank = MeldedCards[i].substr(0,MeldedCards[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < 10)
			Score += 5;
		else if (value >= 10 && value <= 13)
			Score += 10;
		else 
			Score += 15;
	}
	
	for (int i = 0; i < Hand.size(); i++)
	{
		string cardRank = Hand[i].substr(0,Hand[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < 10)
			Score -= 5;
		else if (value >= 10 && value <= 13)
			Score -= 10;
		else 
			Score -= 15;
	}
}

int Player::GetHandSize() const
{
	return Hand.size();
}

string Player::GetHandValue(int number) const
{
	return Hand[number];
}

void Player::InsertIntoHand(string card)
{
	Hand.push_back(card);
}

void Player::DisplayHand() const
{
	cout << "Your hand:\n";
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

int Player::WhatDeckToPickFrom(Cards deck) const
{	
	int choice;
	cout << "Would you like to pick up from the pick up pile (" << YES << " = YES)? ";
	cin >> choice;

	if (choice == YES)	// They want to use cards from the pick up pile to meld but must check to see if it is possible!
	{		
		// Define a vector of the cards the player wants to meld
		vector<string> cardsIWantToUseToMeld;
		int firstLocationFromDeck;
		
		cout << "What is the bottom card location you wish to pick up from the deck? ";
		cin >> firstLocationFromDeck;

		if (firstLocationFromDeck == -1)
			return PICK_FROM_DECK;
		else
			return firstLocationFromDeck;		// Must return the location that they want to initially pick from 
	} else
	{
		// No option or they just want to pick from the deck
		return PICK_FROM_DECK;
	}
}

int Player::TestIfCanMeld (Cards& deck, vector<string> checkTheseCards) const
{
	// Must write the algorithm to determine if the supplied vector of strings are meldable
	return 0;
}

int Player::WhatCardToDiscard (Cards deck) const
{
	int cardToDiscard;

	cout << "Which card would you like to discard? ";
	cin >> cardToDiscard;

	return cardToDiscard;
}

void Player::OrganizeHand()
{
	sort(Hand.begin(),Hand.end());
}

string Player::ReturnCard (int number) const
{
	return Hand[number];
}

void Player::PopCard (int number)
{
	Hand.erase(Hand.begin() + number);
}

void Player::DisplayMeldedCards () const
{
	cout << "Your melded cards: \n";
	for (int i = 0; i < MeldedCards.size(); i++)
	{
		cout << MeldedCards[i];
		if (i < MeldedCards.size() - 1)
			cout << " ";
	}
	cout << "\n\n";
}

void Player::PopulateMeldedCards (vector<int> CardSpotsIWillMeld)
{
	// Want to populate 
	for(int i = 0; i < CardSpotsIWillMeld.size(); i++)
	{
		int locale = CardSpotsIWillMeld[i];
		string card = ReturnCard(locale);
		MeldedCards.push_back(card);	
		PopCard(locale);
	}
	// Then sorts the melded cards!
	sort(MeldedCards.begin(),MeldedCards.end());
}

vector<int> Player::SecondTimeMeld (Cards& deck) const
{
	// Then must determine if they can meld cards after picking up or not
	int answer;
	cout << "Would you like to meld (" << YES << " = YES)? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	if (answer == 1)
	{
		cout << "\nWhich cards from your hand do you want to meld (terminate with " << TERMINATE_NUMBER << ")?\n";
		int location = 0;
		while (location != TERMINATE_NUMBER)
		{
			cin >> location;
			if (location != TERMINATE_NUMBER)
				cardsToMeld.push_back(location);
		}
	}
	return cardsToMeld;
}

void Player::ClearHandAndMeldedCards()
{
	for (int i = 0; i < Hand.size(); i++)
	{
		Hand.pop_back();
	}

	for (int i = 0; i < MeldedCards.size(); i++)
	{
		MeldedCards.pop_back();
	}
}