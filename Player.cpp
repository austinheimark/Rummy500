// Player.cpp - Header file for the player
// Written by Austin Heimark

#include "Player.h"

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
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
	{
		string cardRank = MeldedCards[i].substr(0,MeldedCards[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + RANK_OFFSET)
			Score += TWO_THROUGH_NINE_PTS;
		else if (value >= Rank(8) + RANK_OFFSET && value <= Rank(11) + RANK_OFFSET)
			Score += TEN_THROUGH_KING_PTS;
		else 
			Score += ACE_POINTS;
	}
	
	for (unsigned int i = 0; i < Hand.size(); i++)
	{
		string cardRank = Hand[i].substr(0,Hand[i].find('-'));
		
		int value = atoi(cardRank.c_str());

		if (value < Rank(8) + RANK_OFFSET)
			Score -= TWO_THROUGH_NINE_PTS;
		else if (value >= Rank(8) + RANK_OFFSET && value <= Rank(11) + RANK_OFFSET)
			Score -= TEN_THROUGH_KING_PTS;
		else 
			Score -= ACE_POINTS;
	}
}

int Player::GetHandSize() const
{
	return Hand.size();
}

string Player::GetHandValue(const int& number) const
{
	return Hand[number];
}

void Player::InsertIntoHand(const string& card)
{
	Hand.push_back(card);
}

void Player::DisplayHand() const
{
	cout << "Your hand:\n";
	for (unsigned int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << "\n";
}

int Player::WhatDeckToPickFrom(const Cards& deck) const
{
	int choice;
	cout << "Would you like to pick up from the pick up pile? ";
	cin >> choice;

	// They want to use cards from the pick up pile to meld
	if (choice == YES)
	{
		int firstLocationFromDeck;
		
		cout << "\nWhat is the bottom card location you wish to pick up from the deck? ";
		cin >> firstLocationFromDeck;

		while (firstLocationFromDeck < 0 || firstLocationFromDeck >= deck.GetPickFromPileSize())
		{
			cout << "Invalid location. Try again: ";
			cin >> firstLocationFromDeck;
		}

		return firstLocationFromDeck;		// Must return the location that they want to initially pick from 
	} else
	{
		// They want to pick from the deck
		return PICK_FROM_DECK;
	}
}

int Player::WhatCardToDiscard () const
{
	int cardToDiscard;

	cout << "Which card would you like to discard? ";
	cin >> cardToDiscard;

	while (cardToDiscard < EMPTY || cardToDiscard >= GetHandSize())
	{
		cout << "That's an invalid indice. Try again! ";
		cin >> cardToDiscard;
	}

	return cardToDiscard;
}

void Player::OrganizeHand()
{
	sort(Hand.begin(),Hand.end());
}

string Player::ReturnCard (const int& number) const
{
	return Hand[number];
}

void Player::PopCard (const int& number)
{
	Hand.erase(Hand.begin() + number);
}

void Player::DisplayMeldedCards () const
{
	cout << "Your melded cards: \n";
	for (unsigned int i = 0; i < MeldedCards.size(); i++)
	{
		cout << MeldedCards[i];
		if (i < MeldedCards.size() - 1)
			cout << " ";
	}
	cout << "\n\n";
}

void Player::PopulateMeldedCards (const vector<int>& CardSpotsIWillMeld)
{
	// Want to populate 
	for (unsigned int i = 0; i < CardSpotsIWillMeld.size(); i++)
	{
		int locale = CardSpotsIWillMeld[i];
		string card = ReturnCard(locale);
		MeldedCards.push_back(card);	
		PopCard(locale);
	}
	// Then sorts the melded cards!
	sort(MeldedCards.begin(),MeldedCards.end());
}

vector<int> Player::SecondTimeMeld () const
{
	// Then must determine if they can meld cards after picking up or not
	int answer;
	cout << "\nWould you like to meld? ";
	cin >> answer;
	
	vector<int> cardsToMeld;

	if (answer == YES)
		cardsToMeld = RetrieveMeldSpots();
	
	return cardsToMeld;
}

void Player::ClearHandAndMeldedCards()
{
	Hand.clear();
	MeldedCards.clear();
}

vector<int> Player::CardsToMeld() const
{
	vector<int> cardsIWillMeld;
	cout << "\n";
	DisplayHand();
		
	cardsIWillMeld = RetrieveMeldSpots();

	return cardsIWillMeld;
}

void Player::GamePlay (Cards& deck, const vector<string>& compsMeldedCards, const string& compsName)
{
	cout << "Your turn!\n\n";

	cout << "Current pick up pile:\n";		// X represents the top of the deck
	deck.DisplayAvailableCards();		// Show the player's what they are working with

	OrganizeHand();
	DisplayHand();
	cout << "\n";
	// Show the player the melded cards
	DisplayMeldedCards();
	
	cout << compsName << "'s melded cards: \n";
	for (unsigned int i = 0; i < compsMeldedCards.size(); i++)
		cout << compsMeldedCards[i] << " ";
	cout << "\n\n";

	// First must choose cards to pick up
	int choice = WhatDeckToPickFrom(deck);

	if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
	{
		InsertFromPickFromPile(deck,choice);
			
		OrganizeHand();

		// Populate the players newly melded cards
		PopulateMeldedCards(CardsToMeld());

		cout << "\n";
		DisplayMeldedCards();
	} else {	// Picking up from the top of the deck
		InsertIntoHand(deck.TopDeckCard());
		deck.PopOffCard();
	
		// Only need to ask them to meld if they didn't want to the first time
		// This populates the users melded cards with a vector of cards that they are allowed to meld
		if (GetHandSize() > EMPTY)
		{
			cout << "\n";
			OrganizeHand();
			DisplayHand();
			PopulateMeldedCards(SecondTimeMeld());
		}
	}
	
	cout << "\n";

	// Finally, must discard a card
	if(GetHandSize() > EMPTY)
	{
		OrganizeHand();
		DisplayHand();
		cout << "\n";
		DiscardCard(deck,WhatCardToDiscard());
	}

	cout << "\n";
}

void Player::InsertFromPickFromPile (Cards& deck, const int& choice)
{
	for (int i = deck.GetPickFromPileSize()-NEXT; i >= choice; i--)
	{
		InsertIntoHand(deck.GetPickFromPileCard(i));	// Insert the card into their hand
		deck.PopPickFromPileCard();							// Remove that card from the pile
	}
}

void Player::DiscardCard (Cards& deck, const int& cardSpot)
{
	deck.InsertIntoPickFromPile(ReturnCard(cardSpot));	// First insert the card into the pick from pile
	PopCard(cardSpot);									// Then pop the card out of the user's hand
}

vector<string> Player::ReturnVectorOfMyMeldedCards () const
{
	return MeldedCards;
}

vector<int> Player::RetrieveMeldSpots () const
{
	vector<int> cardsToMeld;
	int location = EMPTY;

	cout << "\nWhich cards from your hand do you want to meld?\n";

	while (location != TERMINATE_NUMBER)
	{
		cin >> location;
		if (location != TERMINATE_NUMBER)
			cardsToMeld.push_back(location);
	}

	return cardsToMeld;
}