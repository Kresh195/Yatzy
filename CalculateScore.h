#pragma once

#include "Dice.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class CalculateScore
{
public:
	CalculateScore(std::vector<int>& values);

	~CalculateScore();

	std::vector<int> getDiceValuesPoints();

	int getThreeOfAKindScore();

	int getFourOfAKindScore();

	int checkFullHouse();

	int checkSmallStraight();

	int checkLargeStraight();

	int checkYatzy();

	int getChanceScore();

	std::vector<int> getCombinationsPoints();

	void clear();


private:
	std::vector<int>& diceValues; //значения на кубиках
	std::vector<int> diceValueCounts; //кол-во каждого значения на кубиках
	std::vector<int> diceValuesPoints; // очки за суммы 1-6
	std::vector<int> combinationsPoints; //очки за все комбинации
};

