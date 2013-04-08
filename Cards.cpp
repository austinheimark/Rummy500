// Cards.cpp - Header file for the deck of cards
// Written by Austin Heimark

#include "Cards.h"
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define CARDS_PER_PLAYER 7

void Cards::ShuffleDeck()
{
	srand(time(NULL));
	int A[13][4];
	while(Deck.size() < DECK_SIZE)
	{
		int number = rand() % 13;
		int suit = rand() % 4;

		if(A[number][suit] != 1)
		{
			string card;
			A[number][suit] = 1;
			
			switch(number)
			{
			case(12):
				card = "A";
				break;
			case(11):
				card = "K";
				break;
			case(10):
				card = "Q";
				break;
			case(9):
				card = "J";
				break;
			case(8):
				card = "T";
				break;
			case(7):
				card = "9";
				break;
			case(6):
				card = "8";
				break;
			case(5):
				card = "7";
				break;
			case(4):
				card = "6";
				break;
			case(3):
				card = "5";
				break;
			case(2):
				card = "4";
				break;
			case(1):
				card = "3";
				break;
			case(0):
				card = "2";
				break;
			}

			switch(suit)
			{
			case(0):
				card.append("-S");
				break;
			case(1):
				card.append("-C");
				break;
			case(2):
				card.append("-H");
				break;
			case(3):
				card.append("-D");
			}

			Deck.push_back(card);
		}
	}
}

void Cards::DisplayAvailableCards() const
{
	for (int i = 0; i < PickFromPile.size(); i++)
		cout << PickFromPile[i] << " ";
}

string Cards::ReturnCard(int number) const
{
	return Deck[number];
}

void Cards::PopOffCard()
{
	Deck.pop_back();
}

int Cards::GetDeckSize() const
{
	return Deck.size();
}

void Cards::AdjustPickPile()
{
	int number = Deck.size() - 1;
	string copy = Deck[number];
	Deck.pop_back();
	PickFromPile.push_back(copy);
}

int Cards::GetPickFromPileSize() const
{
	return PickFromPile.size();
}

string Cards::GetPickFromPileCard(int number) const
{
	return PickFromPile[number];
}

void Cards::InsertIntoPickFromPile(string card)
{
	PickFromPile.push_back(card);
}