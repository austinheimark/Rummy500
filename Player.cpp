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
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << endl;
}

int Player::WhatDeckToPickFrom(Cards deck, vector<string> computersMeldedCards) const
{	
	int choice;
	cout << "What deck would you like to pick up from (1 == pick up pile, -1 = not pick up pile)? ";
	cin >> choice;

	if (choice == 1)	// They want to use cards from the pick up pile to meld but must check to see if it is possible!
	{
		cout << "Realize that you are only picking one set of cards to meld...\n\n";
		// Define a vector of the cards the player wants to meld
		vector<string> cardsIWantToUseToMeld;
		int firstLocationFromDeck;
		
		cout << "What is the bottom card location you wish to pick up from the deck? ";
		cin >> firstLocationFromDeck;

		cardsIWantToUseToMeld.push_back(deck.ReturnCard(firstLocationFromDeck));

		// Populate an array of cards that the player wants to meld 
		cout << "What cards from your hand will you use to meld (Terminate your entries with a -1)? ";
		while (cin.peek() != -1)
		{
			int location;
			cin >> location;
			cardsIWantToUseToMeld.push_back(Hand[location]);
		}
		
		cout << "What cards from your opponents melded cards will you use to meld  (Terminate your entries with a -1)? ";
		while (cin.peek() != -1)
		{
			int location;
			cin >> location;
			cardsIWantToUseToMeld.push_back(computersMeldedCards[location]);
		}

		if (TestIfCanMeld(deck,cardsIWantToUseToMeld) == -1)
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

}

int Player::WhatCardToDiscard (Cards deck) const
{
	int cardToDiscard;

	cout << "Which card would you like to discard? ";
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

void Player::OrganizeHand () const
{
	
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
	cout << Name << "'s Melded Cards: \n";
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n\n";
}

void Player::PopulateMeldedCards (vector<int> CardSpotsIWillMeld)
{
	// Want to populate 
	for(int i = 0; i < CardSpotsIWillMeld.size(); i++)
	{
		MeldedCards.push_back(Hand[CardSpotsIWillMeld[i]]);	
		PopCard(CardSpotsIWillMeld[i]);
	}
}

vector<int> Player::SecondTimeMeld (Cards& deck, vector<string> otherPlayersCards) const
{
	// Then must determine if they can meld cards after picking up or not
	int answer;
	cout << "Would you like to meld (1=yes)? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	while (answer == 1)
	{
		vector<string> cardsToTest;
		vector<int> listOfLocationsOfMyCardsIWillMeld;
		
		cout << "Which cards from your hand do you want to meld (terminate with -1)? ";
		while (cin.peek() != -1)
		{
			int location;
			cin >> location;
			cardsToTest.push_back(Hand[location]);
			listOfLocationsOfMyCardsIWillMeld.push_back(location);
		}

		cout << "What cards from your opponents melded card pile will you meld with (terminate with -1)?";
		while (cin.peek() != -1)
		{
			int location;
			cin >> location;
			cardsToTest.push_back(otherPlayersCards[location]);
		}

		int result = TestIfCanMeld(deck,cardsToTest);
		if (result != -1)
		{
			for (int i = 0; i < listOfLocationsOfMyCardsIWillMeld.size(); i++)
				cardsToMeld.push_back(listOfLocationsOfMyCardsIWillMeld[i]);
		}

		cout << "Would you like to try to meld another set (1=yes)? ";
		cin >> answer;
	}
	return cardsToMeld;
}