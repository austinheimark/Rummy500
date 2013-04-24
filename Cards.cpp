// Cards.cpp - Header file for the deck of cards
// Written by Austin Heimark

#include "Cards.h"

void Cards::InitializeDeck()
{
	for (int r = 0; r < NUMBER_OF_RANKS; r++)
	{
		for (int s = 0; s < NUMBER_OF_SUITS; s++)
		{
			string card;
			Rank cardRank = Rank(r);
			switch (cardRank)
			{
			case(Two):
			case(Three):
			case(Four):
			case(Five):
			case(Six):
			case(Seven):
			case(Eight):
			case(Nine):
				card += cardRank + RANK_OFFSET + '0';
				break;
			case(Ten):
				card = "10";
				break;
			case(Jack):
				card = "11";
				break;
			case(Queen):
				card = "12";
				break;
			case(King):
				card = "13";
				break;
			case(Ace):
				card = "14";
			}
			
			Suit cardSuit = Suit(s);
			switch (cardSuit)
			{
			case(D):
				card.append("-D" );
				break;
			case(H):
				card.append("-H");
				break;
			case(S):
				card.append("-S");
				break;
			case(C):
				card.append("-C");
			}
			Deck.push_back(card);
		}
	}
}

void Cards::ShuffleDeck()
{
	srand ( unsigned ( time(0) ) );
	random_shuffle(Deck.begin(),Deck.end());
}

void Cards::DisplayAvailableCards() const
{
	for (unsigned int i = 0; i < PickFromPile.size(); i++)
		cout << PickFromPile[i] << " ";
	cout << "\n\n";
}

string Cards::ReturnCard(const int& number) const
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

string Cards::GetPickFromPileCard(const int& number) const
{
	return PickFromPile[number];
}

void Cards::InsertIntoPickFromPile(const string& card)
{
	PickFromPile.push_back(card);
}

void Cards::PopPickFromPileCard()
{
	PickFromPile.pop_back();
}

string Cards::TopDeckCard () const
{
	return Deck[GetDeckSize()-1];
}