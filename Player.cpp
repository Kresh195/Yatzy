#include "Player.h"

Player::Player(playerColors color) {
	this->color = color;
}

Player::Player() {

}

Player::~Player() {

}

int Player::getScore() {
	return score;
}

playerColors Player::getPlayerColor() {
	return color;
}

int Player::getRollsLeft() {
	return rollsLeft;
}

int Player::getBonusSum() {
	return bonusSum;
}

bool Player::checkBonus() {
	if (bonusSum >= 63 && !isBonusRecieved) {
		return true;
	}
	return false;
}

void Player::recieveBonus() {
	isBonusRecieved = true;
}

void Player::increaseScore(int value) {
	score += value;
}

void Player::increaseBonusSum(int value) {
	bonusSum += value;
}

void Player::resetRolls() {
	rollsLeft = 3;
}

void Player::rolled() {
	rollsLeft -= 1;
}
