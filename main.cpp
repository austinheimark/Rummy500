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
#define CARDS_DEALT 7
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

void gamePlay(Player& player, Computer& comp, Cards& deck, int count);

void discardCard (Player& user, Computer& comp, Cards& deck, int cardSpot, int count);

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
		// Initialize and shuffle up the deck
		Cards deck;
		deck.ShuffleDeck();

		cout << "Your current score: " << user.GetScore() << "\n" <<
			comp.GetName() << "'s current score: " << comp.GetScore() << "\n";

		// Deal the deck
		dealDeck(user,comp,deck);

		unsigned int count = 0;

		// Commence the game, game continues as long as both players have cards
		while( (user.GetHandSize() > 0) && (comp.GetHandSize() > 0) )
		{
			deck.DisplayAvailableCards();		// Show the player's what they are working with
			cout << " X ";						// X represents the top of the deck

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
		// First must choose cards to pick up
		if (user.WhatDeckToPickFrom(deck) == PICK_FROM_DECK)	// Picking from the top of the deck
		{
			user.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		} else {	// They can pick from the pick up pile


		}

		int number = 0;
		// Then must determine if you can meld cards or not
		while(user.TestIfCanMeld(deck,number) != NOT_POSSIBLE)
		{
			//Since they can meld, if they want to let them!
			
			number = user.TestIfCanMeld(deck,number);
		}

		// Finally, must discard a card
		discardCard(user,comp,deck,user.WhatCardToDiscard(deck),count);

	} else			// Computer's turn
	{
		if (comp.WhatDeckToPickFrom(deck) == PICK_FROM_DECK)	// Picking from the top of the deck
		{
			comp.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		} else {	// They can pick from the pick up pile


		}
		
		int number = 0;
		// Then must determine if you can meld cards or not
		while(user.TestIfCanMeld(deck,number) != NOT_POSSIBLE)
		{
			//Since they can meld, if they want to let them!
			
			
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
	} else				// Player is discarding a card
	{
		deck.InsertIntoPickFromPile(comp.ReturnCard(cardSpot));
		user.PopCard(cardSpot);
	}
}