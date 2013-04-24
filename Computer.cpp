// Computer.cpp - implementation file for the computer
// Written by Austin Heimark

#include "Computer.h"

int Computer::WhatDeckToPickFrom(Cards& deck) const
{
	int i = 0; 
	while (i < GetHandSize() - 1)
	{
		string cardRank1 = Hand[i].substr(0,Hand[i].find(DASH));
		int value1 = atoi(cardRank1.c_str());
		string cardRank2 = Hand[i+1].substr(0,Hand[i+1].find(DASH));
		int value2 = atoi(cardRank2.c_str());

		// Then look in the pick up pile for a card that matches the card values that are already the same in your hand
		if (value1 == value2)
		{
			for (int j = 0; j < deck.GetPickFromPileSize(); j++)
			{
				string theCard = deck.GetPickFromPileCard(j);
				string compareRank = theCard.substr(0,theCard.find(DASH));
				int compareValue = atoi(compareRank.c_str());

				if (value1 == compareValue)
					return j;
			}
		}
		i++;
	}

	// No options, thus must just pick from the top of the deck
	return PICK_FROM_DECK;
}

int Computer::WhatCardToDiscard (Cards& deck) const
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
	unsigned int i = 0; 
	while (i < Hand.size() - NUMBER_TO_CHECK)
	{
		// Set a string equal to everything before the dash of that hand value (the rank)
		// Then convert that to an int so you can easily compare
		string cardRank1 = Hand[i].substr(0,Hand[i].find(DASH));
		int value1 = atoi(cardRank1.c_str());
		string cardRank2 = Hand[i+1].substr(0,Hand[i+1].find(DASH));
		int value2 = atoi(cardRank2.c_str());
		string cardRank3 = Hand[i+2].substr(0,Hand[i+2].find(DASH));
		int value3 = atoi(cardRank3.c_str());

		// Then check to see if those three cards all have the same rank, if so then you can meld!
		if (value1 == value2 && value1 == value3)
		{
			cardsCompWillMeld.push_back(i+2);
			cardsCompWillMeld.push_back(i+1);
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
		unsigned int j = 0;
		while (j < Hand.size() - NUMBER_TO_CHECK)
		{
			// Sets a string cardRank to the value before the dash
			// Then converts that string value to an integer
			// Does this 3 times in a row
			string cardRank1 = Hand[j].substr(0,Hand[j].find(DASH));
			int value1 = atoi(cardRank1.c_str());
			
			string cardRank2 = Hand[j+1].substr(0,Hand[j+1].find(DASH));
			int value2 = atoi(cardRank2.c_str());
			
			string cardRank3 = Hand[j+2].substr(0,Hand[j+2].find(DASH));
			int value3 = atoi(cardRank3.c_str());

			// Check if the three cards have consecutive values
			if (value3 == value2 + 1 && value2 == value1 + 1)
			{
				string cardSuit1 = Hand[j].substr(Hand[j].find(DASH)+1,Hand[j].size() - (Hand[j].find(DASH)+1));
				string cardSuit2 = Hand[j+1].substr(Hand[j+1].find(DASH)+1,Hand[j].size() - (Hand[j+1].find(DASH)+1));
				string cardSuit3 = Hand[j+2].substr(Hand[j+2].find(DASH)+1,Hand[j].size() - (Hand[j+2].find(DASH)+1));
					
				// Test to see if all the suits are also the same
				// If so you add those card locations to the vector of card locations that the comp will meld
				if (cardSuit1 == cardSuit2 && cardSuit2 == cardSuit3)
				{
					cardsCompWillMeld.push_back(j+2);
					cardsCompWillMeld.push_back(j+1);
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
		DiscardCard(deck,WhatCardToDiscard(deck));

	cout << "\n";
}