// Computer.cpp - implementation file for the computer
// Written by Austin Heimark

#include "Computer.h"

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

vector<int> Computer::SecondTimeMeld () const
{
	vector<int> cardsCompWillMeld;

	// Checks to see if can meld cards in their hand that are all the same value
	unsigned int i = 0; 
	while (i < Hand.size() - 2)
	{
		string cardRank1 = Hand[i].substr(0,Hand[i].find('-'));
		int value1 = atoi(cardRank1.c_str());
		string cardRank2 = Hand[i+1].substr(0,Hand[i+1].find('-'));
		int value2 = atoi(cardRank2.c_str());
		string cardRank3 = Hand[i+2].substr(0,Hand[i+2].find('-'));
		int value3 = atoi(cardRank3.c_str());

		if (value1 == value2 && value1 == value3)
		{
			cardsCompWillMeld.push_back(i+2);
			cardsCompWillMeld.push_back(i+1);
			cardsCompWillMeld.push_back(i);
			i = Hand.size() - 2;
		} else
			i++;
	}

	// If true, could not successfully meld any cards with all the same rank
	// Now check to see if can meld cards with same suit and consecutive in order
	if (cardsCompWillMeld.size() == EMPTY)
	{
		unsigned int j = 0;
		while (j < Hand.size() - 2)
		{
			string cardRank1 = Hand[j].substr(0,Hand[j].find('-'));
			int value1 = atoi(cardRank1.c_str());
			string cardRank2 = Hand[j+1].substr(0,Hand[j+1].find('-'));
			int value2 = atoi(cardRank2.c_str());
			string cardRank3 = Hand[j+2].substr(0,Hand[j+2].find('-'));
			int value3 = atoi(cardRank3.c_str());

			// You know that the three cards have consecutive values
			if (value3 == value2 + 1 && value2 == value1 + 1)
			{
				string cardSuit1 = Hand[j].substr(Hand[j].find('-')+1,Hand[j].size() - (Hand[j].find('-')+1));
				string cardSuit2 = Hand[j+1].substr(Hand[j+1].find('-')+1,Hand[j].size() - (Hand[j+1].find('-')+1));
				string cardSuit3 = Hand[j+2].substr(Hand[j+2].find('-')+1,Hand[j].size() - (Hand[j+2].find('-')+1));
					
				// Test to see if all the suits are also the same
				// If so you add those card locations to the vector of card locations that the comp will meld
				if (cardSuit1 == cardSuit2 && cardSuit2 == cardSuit3)
				{
					cardsCompWillMeld.push_back(j+2);
					cardsCompWillMeld.push_back(j+1);
					cardsCompWillMeld.push_back(j);
					j = Hand.size() - 2;
				} else
					j++;
			} else
				j++;
		}
	}

	return cardsCompWillMeld;
}

void Computer::GamePlay (Cards& deck, vector<string> usersMeldedCards)
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
		InsertIntoHand(deck.TopDeckCard());
		deck.PopOffCard();
	}

	OrganizeHand();

	// This populates the computers melded cards with a vector of cards they melded
	if (GetHandSize() > EMPTY)
		PopulateMeldedCards(SecondTimeMeld());

	OrganizeHand();

	// Finally the computer must discard a card
	if(GetHandSize() > EMPTY)
		DiscardCard(deck,WhatCardToDiscard(deck));

	cout << "\n";
}