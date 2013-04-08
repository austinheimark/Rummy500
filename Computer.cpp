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