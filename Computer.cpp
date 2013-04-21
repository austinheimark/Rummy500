// Computer.cpp - implementation file for the computer
// Written by Austin Heimark

#include "Computer.h"

#define PICK_FROM_DECK -1

int Computer::WhatDeckToPickFrom(Cards deck) const
{
	for (int d = 0; d < deck.GetPickFromPileSize(); d++)
	{
		for (int p = 0; p < Hand.size(); p++)
		{
			if (CompareCardsOnPickFromPile(deck,d,p))
			{
				
			}
		}
	}

	// No option
	return PICK_FROM_DECK;
}

int Computer::WhatCardToDiscard (Cards deck) const
{
	int cardToDiscard;

	// Must do some calculations to determine which card to discard

	return cardToDiscard;
}

vector<string> Computer::ReturnVectorOfMyMeldedCards () const
{
	return MeldedCards;
}

void Computer::DisplayMeldedCards () const
{
	cout << Name << "'s melded cards: \n";
	for (int i = 0; i < MeldedCards.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

bool Computer::CompareCardsOnPickFromPile (Cards deck, int d, int p) const
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