#pragma once

class GameState
{
public:
	enum state {
		gameMenu,
		inGame,
		finalScore,
		options,
		gameRules
	};

	state getCurrentState();

	void setCurrentState(state newCurrentState);


private:
	state currentState = gameMenu;
};

