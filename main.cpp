// main.cpp - Rummy 500 test program
// Written by Austin Heimark

#include <iostream>
#include <vector>
#include "Player.h"
#include "Cards.h"
#include "Computer.h"

#define WINNING_SCORE 500
#define TWO_THROUGH_NINE_POINTS 5
#define TEN_THROUGH_KING_POINTS 10
#define ACE_HIGH_POINTS 15
#define ACE_LOW_POINTS 5
#define CARDS_DEALT 11
#define DECK_SIZE 52
#define PICK_FROM_DECK -1
#define NOT_POSSIBLE -1

using namespace std;

// Intro which includes rules for the game
void outputIntro();

// Outputs winner and ending
void outputEnding(Player& player, Computer& comp);

// Deals the deck
// Inserts a card into players hand, pops card off of the deck
// then inserts a card into computer's hand and pops a card off
// the deck. Continues till each player has a full hand
void dealDeck(Player& player, Computer& comp, Cards& deck);

// The main gameplay for the game, iterates through each turn of every hand
void gamePlay(Player& player, Computer& comp, Cards& deck, int count);

// Discards the card in the player's hand at spot cardSpot
void discardCard(Player& user, Computer& comp, Cards& deck, int cardSpot, int count);

// Must insert the cards from player's choice all the way up to the end of the pile into the player's hand
// Called if the player wants to pick from the pick up pile
void InsertPickFromPile(Player& user, Computer& comp, Cards& deck, int choice, int count);

// Populates a vector of the cards that the player will meld from their own hand
vector<int> CardsToMeld(Player& user, Computer& comp, int count);

void main ()
{
	// Outputs the rules for the game
	outputIntro();

	string name;

	// Retrieve user's name and initialize the Player
	cout << "\nEnter your name: ";
	getline(cin, name);
	Player user(name);

	// Retrieve a name for the computer and initialize the computer
	cout << "\nEnter a name for the computer: ";
	getline(cin,name);
	Computer comp(name);

	bool the = 1;
	// Game continues as long as neither player has over 500 points
	while ( the && (user.GetScore() < WINNING_SCORE) && (comp.GetScore() < WINNING_SCORE) )
	{
		cout << "Your current score: " << user.GetScore() << "\n" <<
			comp.GetName() << "'s current score: " << comp.GetScore() << "\n";

		// Initialize and shuffle up the deck
		Cards deck;
		deck.ShuffleDeck();

		// Deal the deck
		dealDeck(user,comp,deck);

		unsigned int count = 0;

		// Commence the game, game continues as long as both players have cards
		while( count < 1 && (user.GetHandSize() > 0) && (comp.GetHandSize() > 0) && (deck.GetDeckSize() > 0) )
		{
			cout << "Updated pick from pile:\nX ";		// X represents the top of the deck
			deck.DisplayAvailableCards();		// Show the player's what they are working with
			
			// Must call this every play through the hand
			gamePlay(user,comp,deck,count);

			count++;
		}

		// Calculate scores
		user.CalculateScore();
		comp.CalculateScore();
		the = 0;
	}

	// Someone has won by now
	outputEnding(user,comp);

	system("pause");
}

void outputIntro()
{
	cout << "Welcome to Rummy 500!\n";
	cout << "Written by Austin Heimark\n\n";

	// List the rules
	cout << "RULES OF THE GAME:\n" <<
		"It is you versus the computer.\n" <<
		"First player to " << WINNING_SCORE << " points wins.\n" <<
		"Each player is dealt " << CARDS_DEALT << " cards of a standard \n" <<
		DECK_SIZE << " card deck each hand.\n" <<
		"User (you) goes first; this alternates each hand.\n" <<
		"Players earn points by melding \ncards from their hand into the meld area.\n" <<
		"Players may meld a set of \ncards once they have at least 3 of a kind\n" <<
		"(ex: 3 Kings) or 3 in a row \nof the same suit (ex: 4,5,6 of spades).\n" <<
		"Each turns starts with picking \nup a card, and ends by discarding a card.\n" <<
		"The hand continues until \none player has used all of their cards.\n" <<
		"Points are tallied at the end of each hand.\n" <<
		"Point per card are as follows:\n" << 
		"2 ... 9 --> " << TWO_THROUGH_NINE_POINTS << " points\n" <<
		"10 ... King --> " << TEN_THROUGH_KING_POINTS << " points\n" <<
		"Ace high (ex: Queen,King,Ace\n of clubs, ex: 3 Aces) --> " << ACE_HIGH_POINTS << " points\n" <<
		"Ace low (ex: Ace,2,3 of hearts) --> " << ACE_LOW_POINTS << " points\n" <<
		"New hands keep being dealt \nuntil a player has over " << WINNING_SCORE << " points\n" <<
		"If both players end with over " << WINNING_SCORE << "\npoints, player with more points wins.\n" <<
		"In the event of two players being tied \nwith over " << WINNING_SCORE << " points:\n" <<
		"Another hand will be played.\n" <<
		"Hands will then continue to be \nplayed until one player has a higher score\n";
}

void outputEnding(Player& player, Computer& comp)
{
	// Whichever player has the higher score wins
	if ( player.GetScore() >= comp.GetScore() )
		cout << "\nCongratulations, " << player.GetName() << "! You beat the computer in Rummy 500!";
	else
		cout << "\nSorry, " << comp.GetName() << " defeated you!";

	// Thanks to the players
	cout << "\n\nI hope you enjoyed my program." <<
		"\nFeedback please to: ach5306@psu.edu\n\n";
}

void dealDeck(Player& user, Computer& comp, Cards& deck)
{
	int i = 0;
	while (i < 2*CARDS_DEALT)
	{
		user.InsertIntoHand(deck.ReturnCard(i));
		deck.PopOffCard();
		i++;
		comp.InsertIntoHand(deck.ReturnCard(i));
		deck.PopOffCard();
		i++;
	}
	deck.AdjustPickPile();
}

void gamePlay(Player& user, Computer& comp, Cards& deck, int count)
{
	if (count%2==0)	// User's turn
	{
		cout << "Your hand:\n";
		user.DisplayHand();
		
		// Show the player the melded cards
		user.DisplayMeldedCards();
		comp.DisplayMeldedCards();

		// First must choose cards to pick up
		int choice = user.WhatDeckToPickFrom(deck,comp.ReturnVectorOfMyMeldedCards());
		if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
		{
			InsertPickFromPile(user,comp,deck,choice,count);

			// Force them to meld right now!
			vector<int> locationsOfCardsIWillMeld = CardsToMeld(user,comp,count);
			
			// Populate the players newly melded cards
			user.PopulateMeldedCards(locationsOfCardsIWillMeld);

		} else {	// Picking up from the top of the deck
			user.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		}

		cout << "Your updated hand:\n";
		user.DisplayHand();

		user.DisplayMeldedCards();
		comp.DisplayMeldedCards();
		
		// This populates the users melded cards with a vector of cards that they are allowed to meld
		user.PopulateMeldedCards(user.SecondTimeMeld(deck,comp.ReturnVectorOfMyMeldedCards()));
		
		// Finally, must discard a card
		discardCard(user,comp,deck,user.WhatCardToDiscard(deck),count);

	} else			// Computer's turn
	{
		// First must choose cards to pick up
		int choice = comp.WhatDeckToPickFrom(deck);
		if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
		{
			InsertPickFromPile(user,comp,deck,choice,count);
		} else {	// Picking up from the top of the deck
			comp.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		}

		int number = 0;
		// Then must determine if you can meld cards or not
		while(comp.TestIfCanMeld(deck,number) != NOT_POSSIBLE)
		{
			//Since they can meld, if they want to let them!
			
			number = comp.TestIfCanMeld(deck,number);
		}

		// Finally, must discard a card
		discardCard(user,comp,deck,comp.WhatCardToDiscard(deck),count);
	}

}

void discardCard (Player& user, Computer& comp, Cards& deck, int cardSpot, int count)
{
	if (count%2==0)		// User is discarding a card
	{
		deck.InsertIntoPickFromPile(user.ReturnCard(cardSpot));	// First insert the card into the pick from pile
		user.PopCard(cardSpot);									// Then pop the card out of the user's hand
	} else				// Computer is discarding a card
	{
		deck.InsertIntoPickFromPile(comp.ReturnCard(cardSpot));
		comp.PopCard(cardSpot);
	}
}

void InsertPickFromPile(Player& user, Computer& comp, Cards& deck, int choice, int count)
{
	if (count%2==0)		// User is inserting from pick from pile
	{
		for (int i = deck.GetPickFromPileSize()-1; i >= choice; i--)
		{
			user.InsertIntoHand(deck.GetPickFromPileCard(i));
			deck.PopOffCard();
		}
	} else				// Computer is discarding a card
	{
		for (int i = deck.GetPickFromPileSize()-1; i >= choice; i--)
		{
			comp.InsertIntoHand(deck.GetPickFromPileCard(i));
			deck.PopOffCard();
		}
	}

}

vector<int> CardsToMeld(Player& user, Computer& comp, int count)
{
	if(count%2==0)	// the player is up
	{
		vector<int> cardsIWillMeld;
		cout << "Enter the locations from your hand of the cards that you wish to meld (terminating with -1): ";
		while (cin.peek() != -1)
		{
			int location;
			cin >> location;
			cardsIWillMeld.push_back(location);
		}
		return cardsIWillMeld;
	}
}