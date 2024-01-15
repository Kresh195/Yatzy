#pragma once

#include "CalculateScore.h"
#include <iostream>

CalculateScore::CalculateScore(std::vector<int>& values) 
	: diceValues(values) {
	for (int i = 0; i < 6; i++) {
		diceValueCounts.emplace_back(0);
	}
	for (int i = 0; i < 5; i++) {
		int value = values[i];
		diceValueCounts[value-1] += 1;
	}
	std::cout << std::endl;
}

void CalculateScore::clear() {
	diceValueCounts.clear();
}

CalculateScore::~CalculateScore() {

}

std::vector<int> CalculateScore::getValuesSums() {
	std::vector<int> valueSums;
	int valueSum;
	for (int i = 0; i < 6; i++) {
		valueSum = diceValueCounts[i] * (i + 1);
		valueSums.emplace_back(valueSum);
	}
	return valueSums;
}

int CalculateScore::getThreeOfAKindScore() {
	int threeOfAKindScore = 0;
	for (int i = 0; i < 6; i++) {
		if (diceValueCounts[i] >= 3) {
			std::cout << "valueee " << diceValues[0] << std::endl;
			for (auto& value : diceValues) {
				/*std::cout << "value " << value << std::endl;*/
				threeOfAKindScore += value;
			}
			break;
		}
	}
	return threeOfAKindScore;
}

int CalculateScore::getFourOfAKindScore() {
	int fourOfAKindScore = 0;
	for (int i = 0; i < 6; i++) {
		if (diceValueCounts[i] >= 4) {
			for (auto& value : diceValues) {
				fourOfAKindScore += value;
			}
			break;
		}
	}
	return fourOfAKindScore;
}

int CalculateScore::checkFullHouse() {

	bool diceSet = 0;
	bool dicePair = 0;
	for (auto& value : diceValueCounts) {
		if (value == 3) {
			diceSet = 1;
		}
		if (value == 2) {
			dicePair = 1;
		}
	}
	if (diceSet && dicePair)
		return 25;
	return 0;
}

int CalculateScore::checkSmallStraight() {
	std::vector<bool> smallStraight = { 1, 1, 1, 1 };
	std::vector<bool> isValues;
	for (auto& valueNumber : diceValueCounts) {
		if (valueNumber > 0) {
			isValues.emplace_back(true);
		}
		else {
			isValues.emplace_back(false);
		}
	}
	if (std::search(isValues.begin(), isValues.end(),
		smallStraight.begin(), smallStraight.end()) != isValues.end()) {
		return 30;
	}
	return 0;

}

int CalculateScore::checkLargeStraight() {
	std::vector<int> largeStraight = { 1, 1, 1, 1, 1 };
	if (std::search(diceValueCounts.begin(), diceValueCounts.end(), largeStraight.begin(), largeStraight.end()) != diceValueCounts.end())
		return 40;
	return 0;
}

int CalculateScore::checkYatzy() {
	for (int i = 0; i < 6; i++) {
		if (diceValueCounts[i] == 5) {
			return 50;
		}
	}
	return 0;
}

int CalculateScore::getChanceScore() {
	int chanceScore = 0;
	for (auto& value : diceValues) {
		chanceScore += value;
	}
	return chanceScore;
}

void CalculateScore::nextTurn() {
	/*turn += 1;*/
}

int CalculateScore::getTurn() {
	return turn;
}