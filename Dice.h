#pragma once

class Dice
{
public:
	int getNumber() const;

	bool isLocked() const;

	void setNumber(int number);

	void setLock(bool lock);
private:
	int number;
	bool lock = 0;
};

