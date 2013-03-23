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

using namespace std;

// Intro which includes rules for the game
void outputIntro();

// Outputs winner and ending
void outputEnding(Player& player, Computer& comp);

void dealDeck(Player& player, Computer& comp, Cards& deck);

void main ()
{
	// Outputs the rules for the game
	outputIntro();

	string name;

	// Another test

	// Retrieve user's name and initialize the Player
	cout << "\nEnter your name: ";
	getline(cin, name);
	Player user(name);

	// Retrieve a name for the computer and initialize the computer
	cout << "\nEnter a name a for the computer: ";
	getline(cin,name);
	Computer comp(name);

	bool the = 1;
	// Game continues as long as neither player has over 500 points
	while ( the && (user.GetScore() < WINNING_SCORE) && (comp.GetScore() < WINNING_SCORE) )
	{
		// Initialize and shuffle up the deck
		Cards deck;
		deck.ShuffleDeck();

		cout << "User's current score: " << user.GetScore() << "\n" <<
			"Comp's current score: " << comp.GetScore() << "\n";

		// Deal the deck
		dealDeck(user,comp,deck);

		// Commence the game, game continues as long as both players have cards
		//while( (user.GetHandSize() > 0) && (comp.GetHandSize() > 0) )
		//{



		//	
		//}

		// Calculate scores
		user.CalculateScore();
		comp.CalculateScore();
		the = 0;
	}

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
		"The hand continues until one player has used all of their cards.\n" <<
		"Points are tallied at the end of each hand.\n" <<
		"2 ... 9 --> " << TWO_THROUGH_NINE_POINTS << " points\n" <<
		"10 ... King --> " << TEN_THROUGH_KING_POINTS << " points\n" <<
		"Ace high (ex: Queen,King,Ace of clubs, ex: 3 Aces) --> " << ACE_HIGH_POINTS << " points\n" <<
		"Ace low (ex: Ace,2,3 of hearts) --> " << ACE_LOW_POINTS << " points\n" <<
		"New hands keep being dealt until a player has over " << WINNING_SCORE << " points\n" <<
		"If both players end with over " << WINNING_SCORE << "\npoints, player with more points wins.\n" <<
		"In the event of two players being tied \nwith over " << WINNING_SCORE << " points:\n" <<
		"Another hand will be played.\n" <<
		"Hands will then continue to be \nplayed until one player has a higher score\n";
}

void outputEnding(Player& player, Computer& comp)
{
	// Whichever player has the higher score wins
	if ( player.GetScore() >= comp.GetScore() )
		cout << "\n\nCongratulations " << player.GetName() << "! You beat the computer in Rummy 500!";
	else
		cout << "\n\nSorry, " << comp.GetName() << " defeated you!";

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
	deck.PopulatePickPile();
}