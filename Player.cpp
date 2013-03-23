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
	for (int i = 0; i < MeldedCards.size(); i++)
	{
		string card = MeldedCards[i];
		if(card[0] <= '9' && card[0] >= '2')
			Score+=5;
		else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
			Score+=10;
		else
			Score+=15;
	}
	
	for (int i = 0; i < Hand.size(); i++)
	{
		string card = Hand[i];
		if(card[0] <= '9' && card[0] >= '2')
			Score = Score - 5;
		else if (card[0] == 'T' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K')
			Score = Score - 10;
		else
			Score = Score - 15;
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
	cout << Name << "'s hand: ";
	for (int i = 0; i < Hand.size(); i++)
		cout << Hand[i] << " ";
	cout << endl;
}