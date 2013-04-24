// Computer.cpp - implementation file for the computer
// Written by Austin Heimark

#include "Computer.h"

int Computer::WhatDeckToPickFrom(const Cards& deck) const
{
	int i = EMPTY; 
	while (i < GetHandSize() - 1)
	{
		// Retrieves the ranks of the cards at i and i + NEXT
		int value1 = ConvertRank(Hand[i]);
		int value2 = ConvertRank(Hand[i+NEXT]);

		// If value1 and value2 are the same, then look for another card in the
		// pick from pile that has the same value, if so return that index
		// of the pick from pile
		if (value1 == value2)
		{
			for (int j = 0; j < deck.GetPickFromPileSize(); j++)
			{
				int compareValue = ConvertRank(deck.GetPickFromPileCard(j));

				if (value1 == compareValue)
					return j;
			}
		}
		i++;
	}

	// No options, thus must just pick from the top of the deck
	return PICK_FROM_DECK;
}

int Computer::WhatCardToDiscard () const
{
	int compHandSize = GetHandSize();

	srand(time(NULL));

	int cardToDiscard = rand() % compHandSize;

	return cardToDiscard;
}

void Computer::DisplayMeldedCards () const
{
	cout << Name << "'s melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

vector<int> Computer::SecondTimeMeld () const
{
	vector<int> cardsCompWillMeld;

	// Checks to see if can meld cards in their hand that are all the same value
	unsigned int i = EMPTY; 
	while (i < Hand.size() - NUMBER_TO_CHECK)
	{
		// Convert the certain card's rank to an integer value so easily comparable
		int value1 = ConvertRank(Hand[i]);
		int value2 = ConvertRank(Hand[i+NEXT]);
		int value3 = ConvertRank(Hand[i+NEXT_NEXT]);

		// Then check to see if those three cards all have the same rank, if so then you can meld!
		if (value1 == value2 && value1 == value3)
		{
			cardsCompWillMeld.push_back(i+NEXT_NEXT);
			cardsCompWillMeld.push_back(i+NEXT);
			cardsCompWillMeld.push_back(i);

			// Because you have populated the pick from deck
			i = Hand.size() - NUMBER_TO_CHECK;
		} else
			i++;
	}

	// If true, could not successfully meld any cards with all the same rank
	// Now check to see if can meld cards with same suit and consecutive in order
	if (cardsCompWillMeld.size() == EMPTY)
	{
		unsigned int j = EMPTY;
		while (j < Hand.size() - NUMBER_TO_CHECK)
		{
			// Convert the certain card's rank to an integer value so easily comparable
			int value1 = ConvertRank(Hand[j]);
			int value2 = ConvertRank(Hand[j+NEXT]);
			int value3 = ConvertRank(Hand[j+NEXT_NEXT]);

			// Check if the three cards have consecutive values
			if (value3 == value2 + 1 && value2 == value1 + 1)
			{
				string cardSuit1 = RetrieveCardSuit(Hand[j]);
				string cardSuit2 = RetrieveCardSuit(Hand[j+NEXT]);
				string cardSuit3 = RetrieveCardSuit(Hand[j+NEXT_NEXT]);
					
				// Test to see if all the suits are also the same
				// If so you add those card locations to the vector of card locations that the comp will meld
				if (cardSuit1 == cardSuit2 && cardSuit2 == cardSuit3)
				{
					cardsCompWillMeld.push_back(j+NEXT_NEXT);
					cardsCompWillMeld.push_back(j+NEXT);
					cardsCompWillMeld.push_back(j);
					j = Hand.size() - NUMBER_TO_CHECK;
				} else
					j++;
			} else
				j++;
		}
	}

	return cardsCompWillMeld;
}

void Computer::GamePlay (Cards& deck)
{
	cout << Name << "'s turn!\n";
	
	OrganizeHand();

	// First must choose cards to pick up
	int choice = WhatDeckToPickFrom(deck);

	if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
	{
		InsertFromPickFromPile(deck,choice);
			
		OrganizeHand();

		// Populate the players newly melded cards
		PopulateMeldedCards(SecondTimeMeld());

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
		DiscardCard(deck,WhatCardToDiscard());

	cout << "\n";
}

int Computer::ConvertRank (const string& index) const
{
	// Retrieves the card rank of card index by retrieving a substring from
	// the start of index for the distance to DASH characters long
	string cardRank = index.substr(0,index.find(DASH));
	
	// Converts the Rank (all numbers) into an integer value
	int value = atoi(cardRank.c_str());
	
	// Returns that int value
	return value;
}

string Computer::RetrieveCardSuit (const string& index) const
{
	// Gets a substring from after the DASH until the end of the string, which is the rank
	string suit = index.substr(index.find(DASH)+NEXT,index.size() - (index.find(DASH)+NEXT));
	return suit;
}