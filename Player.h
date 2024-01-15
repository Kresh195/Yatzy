#pragma once

enum playerColors{
		green,
		red,
		blue,
		yellow
};
class Player
{
public:
	Player(playerColors color);

	Player();

	~Player();

	int getScore();

	playerColors getPlayerColor();

	int getRollsLeft();

	int getBonusSum();

	bool checkBonus();

	void recieveBonus();

	void resetRolls();

	void rolled();

	void increaseScore(int value);

	void increaseBonusSum(int value);
private:
	int score = 0;
	int bonusSum = 0;
	playerColors color;
	int rollsLeft = 3;
	bool isBonusRecieved = false;
};
