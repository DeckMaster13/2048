#include <SDL_image.h>
#include "Game.h"
#include "InputHandler.h"
#include "TextureHandler.h"
#include "PlayState.h"
#include "Renderer.h"

static bool running = true;

Game& Game::Instance()
{
	static std::unique_ptr<Game> singleton;
	if (!singleton)
		singleton.reset(new Game());

	return *singleton.get();
}

bool Game::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	gameStateMachine.reset(new GameStateMachine());
	gameStateMachine->pushState("PLAYSTATE");
	return true;
}

void Game::handleInputs()
{
	if (InputHandler::isKeyDown(SDL_SCANCODE_ESCAPE))
		running = false;

	InputHandler::updateInputs();

	if (InputHandler::askedForQuit())
	{
		running = false;
		return;
	}

	if (InputHandler::windowResized())
	{
		Renderer::Instance().updateRenderer();
	}

	if (InputHandler::isKeyDown(SDL_SCANCODE_RETURN))
		gameStateMachine->changeState("PLAYSTATE");

	gameStateMachine->getCurrentState()->handleInputs();
}

bool Game::update()
{
	gameStateMachine->getCurrentState()->update();
	return true;
}

bool Game::render()
{
	SDL_RenderClear(Renderer::Instance().getRenderer());
	gameStateMachine->getCurrentState()->render();

	return true;
}

bool Game::quit()
{
	while (gameStateMachine->getCurrentState())
	{
		gameStateMachine->popState();
	}
	SDL_Quit();
	return true;
}

bool Game::isRunning()
{
	return running;
}

GameStateMachine& Game::getGameStateMachine()
{
	return *gameStateMachine.get();
}

