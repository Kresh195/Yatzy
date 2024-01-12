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

	void resetRolls();

	void rolled();

	void increaseScore(int value);
private:
	int score = 0;
	playerColors color;
	int rollsLeft = 3;
};
