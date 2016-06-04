#include "GameStateMachine.h"
#include "PlayState.h"

#include <iostream>

void GameStateMachine::popState()
{
	if (gameStates.empty())
		return;

	if (gameStates.back()->onExit())
	{
		delete gameStates.back();
		gameStates.pop_back();
	}
}

void GameStateMachine::pushState(std::string stateID)
{
	if (stateID == "PLAYSTATE")
		gameStates.push_back(new PlayState);
	else
		std::cout << "ERROR: STATE NOT FOUND";

	gameStates.back()->onEnter();
}

void GameStateMachine::changeState(std::string stateID)
{
	popState();
	pushState(stateID);
}

GameState* GameStateMachine::getCurrentState()
{
	if (!gameStates.empty())
	{
		return gameStates.back();
	}
	return NULL;
}
