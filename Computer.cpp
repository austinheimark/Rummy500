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