// main.cpp - Rummy 500 test program
// Written by Austin Heimark

// Line count --> 933

#include <iostream>
#include <vector>
#include "Player.h"
#include "Cards.h"
#include "Computer.h"

#define WINNING_SCORE 500
#define TWO_THROUGH_NINE_POINTS 5
#define TEN_THROUGH_KING_POINTS 10
#define ACE_POINTS 15
#define CARDS_DEALT 11
#define DECK_SIZE 52
#define PICK_FROM_DECK -1
#define NOT_POSSIBLE -1
#define EMPTY 0
#define TERMINATE_NUMBER -1
#define RANK_OFFSET 2
#define EVEN_ODD 2

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
vector<int> CardsToMeld(Player& user);

// Outputs the scores of each player after how many rounds
void ScoreOutput(Player& user, Computer& comp, int count);

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
	cout << "\n";

	unsigned int count = EMPTY;
	unsigned int roundCount = EMPTY;

	// Game continues as long as neither player has over WINNING_SCORE points
	while ( (user.GetScore() < WINNING_SCORE) && (comp.GetScore() < WINNING_SCORE) )
	{
		// Output scores
		ScoreOutput(user,comp,roundCount);

		// Initialize and shuffle up the deck
		Cards deck;
		deck.InitializeDeck();
		deck.ShuffleDeck();

		// Must clear up both the players and computers hands and melded card piles
		user.ClearHandAndMeldedCards();
		comp.ClearHandAndMeldedCards();

		// Deal the deck
		dealDeck(user,comp,deck);

		// Reassure that the count is set back to 0
		count = 0;

		// Commence the game, game continues as long as both players have cards
		while( (user.GetHandSize() > EMPTY) && (comp.GetHandSize() > EMPTY) && (deck.GetDeckSize() > EMPTY) )
		{
			cout << "Current pick from pile:\n";		// X represents the top of the deck
			deck.DisplayAvailableCards();		// Show the player's what they are working with
			
			// Must call this every play through the hand
			gamePlay(user,comp,deck,count);

			count+=2;
		}
		roundCount++;

		// Calculate scores
		user.CalculateScore();
		comp.CalculateScore();
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
		"(ex: 3 " << Rank(5) << "s) or 3 in a row \nof the same suit (ex: 4,5,6 of spades).\n" <<
		"Each turns starts with picking \nup a card, and ends by discarding a card.\n" <<
		"The hand continues until \none player has used all of their cards.\n" <<
		"Points are tallied at the end of each hand.\n" <<
		"Point per card are as follows:\n" << 
		Rank(0) + RANK_OFFSET << " ... " << Rank(8) + RANK_OFFSET << " --> " << TWO_THROUGH_NINE_POINTS << " points\n" <<
		Rank(9) + RANK_OFFSET << " ... " << Rank(11) + RANK_OFFSET << " --> " << TEN_THROUGH_KING_POINTS << " points\n" <<
		Rank(12) + RANK_OFFSET << " --> " << ACE_POINTS << " points. " <<
		"New hands keep being dealt \nuntil a player has over " << WINNING_SCORE << " points\n" <<
		"If both players end with over " << WINNING_SCORE << "\npoints, player with more points wins.\n" <<
		"In the event of two players being tied \nwith over " << WINNING_SCORE << " points:\n" <<
		"Another hand will be played.\n" <<
		"Hands will then continue to be \nplayed until one player has a higher score.\n" <<
		"When you are prompted for card \\n" <<
		"locations, it is zero based. That is\n" <<
		"if you want the first card from your hand\n" <<
		"you would enter '0'. If choosing multiple cards\n" <<
		"use one space between numbers.\n" <<
		"The first letter or number is the rank\n" <<
		"and after the dash is the suit of the card\n" <<
		"H = Hearts, S = Spades, D = Diamonds, C = Clubs.\n" <<
		"Please not that the face cards will not be sorted in your hand,\n" <<
		"However, the non face cards will be sorted!\n";
}

void outputEnding(Player& player, Computer& comp)
{
	// Whichever player has the higher score wins
	if ( player.GetScore() >= comp.GetScore() )
		cout << "\nCongratulations, " << player.GetName() << "! You beat the computer in Rummy 500!";
	else
		cout << "\nSorry, " << comp.GetName() << " defeated you!";

	// Thanks to the players
	cout << "\n\nI hope you enjoyed my game!" <<
		"\nFeedback please to: ach5306@psu.edu\n\n";
}

void dealDeck(Player& user, Computer& comp, Cards& deck)
{
	int i = 0;
	while (i < EVEN_ODD*CARDS_DEALT)
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
	// Check if it is an even or odd number
	if (count%EVEN_ODD==0)	// User's turn since count is an even number
	{
		user.OrganizeHand();
		user.DisplayHand();
		
		// Show the player the melded cards
		user.DisplayMeldedCards();
		comp.DisplayMeldedCards();

		// First must choose cards to pick up
		int choice = user.WhatDeckToPickFrom(deck);

		if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
		{
			InsertPickFromPile(user,comp,deck,choice,count);
			
			// Populate the players newly melded cards
			user.PopulateMeldedCards(CardsToMeld(user));

		} else {	// Picking up from the top of the deck
			user.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		}
		
		if (choice == PICK_FROM_DECK && user.GetHandSize() > EMPTY)
		{
			cout << "\n";
			user.OrganizeHand();
			user.DisplayHand();
		}
		// This populates the users melded cards with a vector of cards that they are allowed to meld
		if (user.GetHandSize() > EMPTY)
		{
			user.PopulateMeldedCards(user.SecondTimeMeld(deck,comp.ReturnVectorOfMyMeldedCards()));
			if (user.GetHandSize() > EMPTY)
			{
				user.OrganizeHand();
				user.DisplayHand();
			}
		}
		cout << "\n";

		// Finally, must discard a card
		if(user.GetHandSize() > EMPTY)
			discardCard(user,comp,deck,user.WhatCardToDiscard(deck),count);

		cout << "\n";
	} else			// Computer's turn
	{
		cout << "Comp's turn!\n";
		
		comp.OrganizeHand();

		// First must choose cards to pick up
		int choice = comp.WhatDeckToPickFrom(deck);

		if (choice != PICK_FROM_DECK)	// Picking from the pick up pile
		{
			InsertPickFromPile(user,comp,deck,choice,count);
			
			// Populate the players newly melded cards
			comp.PopulateMeldedCards(comp.FirstTimeMeld(deck));

		} else {	// Picking up from the top of the deck
			comp.InsertIntoHand(deck.ReturnCard(deck.GetDeckSize()-1));
			deck.PopOffCard();
		}

		// This populates the computers melded cards with a vector of cards they melded
		if (comp.GetHandSize() > EMPTY)
			comp.PopulateMeldedCards(comp.SecondTimeMeld(deck));

		// Finally the computer must discard a card
		if(comp.GetHandSize() > EMPTY)
			discardCard(user,comp,deck,user.WhatCardToDiscard(deck),count);

		cout << "\n";
	}

}

void discardCard (Player& user, Computer& comp, Cards& deck, int cardSpot, int count)
{
	if (count%EVEN_ODD==0)		// User is discarding a card
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
	if (count%EVEN_ODD==0)		// User is inserting from pick from pile
	{
		for (int i = deck.GetPickFromPileSize()-1; i >= choice; i--)
		{
			user.InsertIntoHand(deck.GetPickFromPileCard(i));
			deck.PopPickFromPileCard();
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

vector<int> CardsToMeld(Player& user)
{
	vector<int> cardsIWillMeld;
	cout << "\n";
	user.DisplayHand();
		
	int location = 0;

	cout << "Enter the locations from your hand of the \ncards that you wish to meld (terminating with" <<  TERMINATE_NUMBER << "), \nin decreasing location order:\n";
	while (location != TERMINATE_NUMBER)
	{
		cin >> location;
		if (location != TERMINATE_NUMBER)
			cardsIWillMeld.push_back(location);
	}

	return cardsIWillMeld;
}

void ScoreOutput(Player& user, Computer& comp, int count)
{
	cout << "\nAfter " << count << " rounds\n" <<		
		"Your current score: " << user.GetScore() << "\n" <<
		comp.GetName() << "'s current score: " << comp.GetScore() << "\n" <<
		"And the game continues...\n\n";
}