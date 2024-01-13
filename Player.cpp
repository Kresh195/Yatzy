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
