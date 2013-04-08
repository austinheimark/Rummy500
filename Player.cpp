// Player.cpp - Header file for the player
// Written by Austin Heimark

#include "Player.h"

#define PICK_FROM_DECK -1
#define NOT_POSSIBLE -1

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
		string card = MeldedCards[i];
		if(card[0] <= '9' && card[0] >= '2')
			Score += 5;
		else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
			Score += 10;
		else
			Score += 15;
	}
	
	for (int i = 0; i < Hand.size(); i++)
	{
		string card = Hand[i];
		if(card[0] <= '9' && card[0] >= '2')
			Score -= 5;
		else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
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
	cout << Name << "'s hand: ";
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << endl;
}

int Player::WhatDeckToPickFrom(Cards deck) const
{
	for (int d = 0; d < deck.GetPickFromPileSize(); d++)
	{
		for (int p = 0; p < Hand.size(); p++)
		{
			if (CompareCardsOnPickFromPile(deck,d,p))
			{
				// Must then test if the player even wants to pick up from there
				// Must now check if they can meld
				if(Player.TestIfCanMeld(deck))
				{
					int number;
					cout << "Would you like to pick up from the pick up pile? (Yes = 1, No = -1) ";
					cin >> number;
					if (number != PICK_FROM_DECK)
						return number;
				}
			}
		}
	}

	// No option or they just want to pick from the deck
	return PICK_FROM_DECK;
}

// Start checking from number
// If can meld, return the number card that can be melded
// If cannot meld, return NOT_POSSIBLE
int Player::TestIfCanMeld (Cards deck, int number) const
{

}

int Player::WhatCardToDiscard (Cards deck) const
{

}

bool Player::CompareCardsOnPickFromPile (Cards deck, int d, int p) const
{
	string card = deck.GetPickFromPileCard(d);

	// They are the same value
	if (Hand[p][0] == card[0])
		return true;
	else if (Hand[p][2] == card[2])	// The cards are same suit
	{
		if (card[0] <= '9' && card[0] >= '2')
		{
			if (card[0] + 1 == Hand[p][0] || card[0] - 1 == Hand[p][0])
				return true;
		}
		switch(card[0])
		{
		case ('2'):
		case ('3'):
		case ('4'):
		case ('5'):
		case ('6'):
		case ('7'):
		case ('8'):
		case ('9'):
			if (card[0] + 1 == Hand[p][0] || card[0] - 1 == Hand[p][0])
				return true;
		case ('T'):
			if (Hand[p][0] == '9' || Hand[p][0] == 'J')
				return true;
		case ('J'):
			if (Hand[p][0] == 'T' || Hand[p][0] == 'Q')
				return true;
		case ('Q'):
			if (Hand[p][0] == 'J' || Hand[p][0] == 'K')
				return true;
		case ('K'):
			if (Hand[p][0] == 'Q' || Hand[p][0] == 'A')
				return true;
		case ('A'):
			if (Hand[p][0] == 'K')
				return true;
		}
	}
	return false;
}

void Player::OrganizeHand () const
{

}

string Player::ReturnCard (int number)
{
	return Hand[number];
}

// MUST COMPLETE THIS FUNCTION
void Player::PopCard (int number)
{
	
}