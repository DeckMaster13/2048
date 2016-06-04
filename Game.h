#ifndef __GAME__
#define __GAME__

#include <SDL.h>
#include "GameStateMachine.h"

#include <memory>

class Game
{
public:
	static Game& Instance();

	~Game() = default;
	
	bool init();
	void handleInputs();
	bool update();
	bool render();
	bool quit();
	bool isRunning();
	GameStateMachine& getGameStateMachine();
private:
	Game() = default;
	Game(const Game& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	std::unique_ptr<GameStateMachine> gameStateMachine;
};
typedef Game TheGame;

#endif