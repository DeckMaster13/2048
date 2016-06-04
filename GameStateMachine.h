#ifndef __GAMESTATEMACHINE__
#define __GAMESTATEMACHINE__

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
	void popState();
	void pushState(std::string stateID);
	void changeState(std::string stateID);
	GameState* getCurrentState();

private:
	std::vector<GameState*> gameStates;
};

#endif