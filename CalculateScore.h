#pragma once

#include "Dice.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class CalculateScore
{
public:
	CalculateScore(std::vector<int>& values);

	~CalculateScore();

	std::vector<int> getValuesSums();

	int getThreeOfAKindScore();

	int getFourOfAKindScore();

	int checkFullHouse();

	int checkSmallStraight();

	int checkLargeStraight();

	int checkYatzy();

	int getChanceScore();

	int getTurn();

	void nextTurn();

	void clear();

private:
	std::vector<int>& diceValues;
	std::vector<int> valueNumbers;
	int ones;
	int twos;
	int threes;
	int fours;
	int fives;
	int sixes;

	int turn = 1;
};

