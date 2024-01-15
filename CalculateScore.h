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
	std::vector<int>& diceValues; //�������� �� �������
	std::vector<int> diceValueCounts; //���-�� ������� �������� �� �������
	std::vector<int> diceValuesPoints; // ���� �� ����� 1-6
	std::vector<int> combinationsPoints; //���� �� ��� ����������
};

