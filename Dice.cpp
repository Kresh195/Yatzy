#include "Dice.h"

int Dice::getNumber() const {
	return number;
}

bool Dice::isLocked() const {
	return lock;
}

void Dice::setNumber(int number) {
	this->number = number;
}

void Dice::setLock(bool lock) {
	this->lock = lock;
}
