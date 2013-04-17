// Player.cpp - Header file for the player
// Written by Austin Heimark

#include "Player.h"

#define PICK_FROM_DECK -1
#define NOT_POSSIBLE -1
#define YES 1
#define TERMINATE_NUMBER -1

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
	cout << "Your hand:\n";
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

int Player::WhatDeckToPickFrom(Cards deck, vector<string> computersMeldedCards) const
{	
	int choice;
	cout << "Would you like to pick up from the pick up pile (" << YES << " = YES)? ";
	cin >> choice;

	if (choice == YES)	// They want to use cards from the pick up pile to meld but must check to see if it is possible!
	{
		cout << "\nRealize that you are only picking one set of cards to meld...\n\n";
		
		// Define a vector of the cards the player wants to meld
		vector<string> cardsIWantToUseToMeld;
		int firstLocationFromDeck;
		
		cout << "What is the bottom card location you wish to pick up from the deck? ";
		cin >> firstLocationFromDeck;

		/*
		cardsIWantToUseToMeld.push_back(deck.ReturnCard(firstLocationFromDeck));
		
		int location = 0;

		// Populate an array of cards that the player wants to meld 
		cout << "\nWhat cards from your hand will you use \nto meld (Terminate your entries with a -1)? ";
		while (location != -1)
		{
			cin >> location;
			if (location != -1)
				cardsIWantToUseToMeld.push_back(Hand[location]);
		}
				
		location = 0;
		cout << "\nWhat cards from your opponents melded cards will you use to meld  (Terminate your entries with a -1)? ";
		while (location != -1)
		{
			cin >> location;
			if (location != -1)
				cardsIWantToUseToMeld.push_back(computersMeldedCards[location]);
		}
		*/
		if (firstLocationFromDeck == -1  /*(TestIfCanMeld(deck,cardsIWantToUseToMeld) == -1)*/)
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

	cout << "\nWhich card would you like to discard? ";
	cin >> cardToDiscard;

	return cardToDiscard;
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
	MeldedCards.push_back("\n");
	sort(MeldedCards.begin(),MeldedCards.end());
}

vector<int> Player::SecondTimeMeld (Cards& deck, vector<string> otherPlayersCards) const
{
	// Then must determine if they can meld cards after picking up or not
	int answer;
	cout << "Would you like to meld (" << YES << " = YES)? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	if (answer == 1)
	{
		vector<string> cardsToTest;
		vector<int> listOfLocationsOfMyCardsIWillMeld;
		
		cout << "\nWhich cards from your hand do you want to meld (terminate with " << TERMINATE_NUMBER << ")? ";
		while (cin.peek() != TERMINATE_NUMBER)
		{
			int location;
			cin >> location;
			cardsToTest.push_back(Hand[location]);
			listOfLocationsOfMyCardsIWillMeld.push_back(location);
		}

		cout << "What cards from your opponents melded card pile will you meld with (terminate with " << TERMINATE_NUMBER << ")?";
		while (cin.peek() != TERMINATE_NUMBER)
		{
			int location;
			cin >> location;
			cardsToTest.push_back(otherPlayersCards[location]);
		}

		int result = TestIfCanMeld(deck,cardsToTest);
		if (result != TERMINATE_NUMBER)
		{
			for (int i = 0; i < listOfLocationsOfMyCardsIWillMeld.size(); i++)
				cardsToMeld.push_back(listOfLocationsOfMyCardsIWillMeld[i]);
		}

		cout << "Would you like to try to meld another set (" << YES << " = YES)? ";
		cin >> answer;
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