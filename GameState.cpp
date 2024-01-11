#pragma once

#include "GameState.h"

GameState::state GameState::getCurrentState() {
	return currentState;
}

void GameState::setCurrentState(state newCurrentState) {
	currentState = newCurrentState;
}