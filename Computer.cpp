// Computer.cpp - implementation file for the computer
// Written by Austin Heimark

#include "Computer.h"

#define PICK_FROM_DECK -1

int Computer::WhatDeckToPickFrom(Cards& deck) const
{
	//for (int d = 0; d < deck.GetPickFromPileSize(); d++)
	//{
	//	for (int p = 0; p < Hand.size(); p++)
	//	{
	//		if (CompareCardsOnPickFromPile(deck,d,p))
	//		{
	//			
	//		}
	//	}
	//}

	// No option
	return PICK_FROM_DECK;
}

int Computer::WhatCardToDiscard (Cards& deck) const
{
	// Start by automatically discarding the first card for the computer
	int cardToDiscard = 0;

	// Must do some calculations to determine which card to discard

	return cardToDiscard;
}

void Computer::DisplayMeldedCards () const
{
	cout << Name << "'s melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

bool Computer::CompareCardsOnPickFromPile (Cards& deck, const int& d, const int& p) const
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

vector<int> Computer::FirstTimeMeld (Cards& deck) const
{
	vector<int> cardsCompWillMeld;



	return cardsCompWillMeld;
}

vector<int> Computer::SecondTimeMeld (Cards& deck) const
{
	vector<int> cardsCompWillMeld;



	return cardsCompWillMeld;
}

void Computer::GamePlay (Cards& deck, vector<string> compsMeldedCards)
{
	cout << Name << "'s turn!\n";
		
	OrganizeHand();

	// First must choose cards to pick up
	int choice = WhatDeckToPickFrom(deck);

	if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
	{
		InsertFromPickFromPile(deck,choice);
			
		// Populate the players newly melded cards
		PopulateMeldedCards(FirstTimeMeld(deck));

	} else {	// Picking up from the top of the deck
		InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
		deck.PopOffCard();
	}

	OrganizeHand();

	// This populates the computers melded cards with a vector of cards they melded
	if (GetHandSize() > EMPTY)
		PopulateMeldedCards(SecondTimeMeld(deck));

	OrganizeHand();

	// Finally the computer must discard a card
	if(GetHandSize() > EMPTY)
		DiscardCard(deck,WhatCardToDiscard(deck));

	cout << "\n";
}