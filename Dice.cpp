#include "Dice.h"
#include <cstdlib>
#include <ctime>

int Dice::getValue() const {
	return value;
}

void Dice::setLock(bool lock) {
	this->lock = lock;
}

bool Dice::isLocked() const {
	return lock;
}

void Dice::changeLock() {
	lock = !lock;
}

void Dice::rollDice() {
	value =  std::rand() % 6 + 1;
}
