#pragma once

class GameState
{
public:
	enum state {
		gameMenu,
		Game,
		finalScore,
		options,
		gameRules
	};

	state getCurrentState();

	void setCurrentState(state newCurrentState);


private:
	state currentState = gameMenu;
};

