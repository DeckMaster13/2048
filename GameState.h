#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string>
#include <vector>

#include "GameObject.h"

class GameState
{
public:
	GameState(){};

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual void handleInputs();
	virtual void update();
	virtual void render();

	virtual std::string getStateID() const = 0;

protected:
	std::vector<GameObject*> m_stateGameObjects;
};

#endif