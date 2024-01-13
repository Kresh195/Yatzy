#pragma once

#include "CalculateScore.h"
#include <iostream>

CalculateScore::CalculateScore(std::vector<int>& values) 
	: diceValues(values) {
	for (int i = 0; i < 6; i++) {
		valueNumbers.emplace_back(0);
	}
	for (int i = 0; i < 5; i++) {
		int value = values[i];
		valueNumbers[value-1] += 1;
	}
	for (auto& num : valueNumbers) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
}

void CalculateScore::clear() {
	valueNumbers.clear();
}

CalculateScore::~CalculateScore() {

}

std::vector<int> CalculateScore::getValuesSums() {
	return valueNumbers;
}

int CalculateScore::getThreeOfAKindScore() {
	int threeOfAKindScore = 0;
	for (int i = 0; i < 6; i++) {
		if (valueNumbers[i] >= 3) {
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
		if (valueNumbers[i] >= 4) {
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
	for (auto& value : valueNumbers) {
		if (value == 3) {
			diceSet = 1;
			std::cout << "troika " << value << std::endl;
		}
		if (value == 2) {
			std::cout << "para " << value << std::endl;
			dicePair = 1;
		}
	}
	if (diceSet && dicePair)
		return 25;
	return 0;
}

int CalculateScore::checkSmallStraight() {
	std::vector<int> smallStraight1 = { 1, 2, 3, 4 };
	std::vector<int> smallStraight2 = { 2, 3, 4, 5 };
	std::vector<int> smallStraight3 = { 3, 4, 5, 6 };
	std::vector<int> sortedValues = diceValues;
	std::sort(sortedValues.begin(), sortedValues.end());
	if (std::search(sortedValues.begin(), sortedValues.end(), smallStraight1.begin(), smallStraight1.end()) != sortedValues.end()
		|| std::search(sortedValues.begin(), sortedValues.end(), smallStraight2.begin(), smallStraight2.end()) != sortedValues.end()
		|| std::search(sortedValues.begin(), sortedValues.end(), smallStraight3.begin(), smallStraight3.end()) != sortedValues.end())
		return 30;
	return 0;
	
}

int CalculateScore::checkLargeStraight() {
	std::vector<int> largeStraight = { 1, 1, 1, 1, 1 };
	if (std::search(valueNumbers.begin(), valueNumbers.end(), largeStraight.begin(), largeStraight.end()) != valueNumbers.end())
		return 40;
	return 0;
}

int CalculateScore::checkYatzy() {
	for (int i = 0; i < 6; i++) {
		if (valueNumbers[i] == 5) {
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