#pragma once

class Dice
{
public:
	int getValue() const;

	void setLock(bool lock);

	bool isLocked() const;

	void changeLock();

	void rollDice();
private:
	int value;
	bool lock = false;
};

