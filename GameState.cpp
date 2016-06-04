#include "GameState.h"
#include "Renderer.h"

//const std::string GameState::stateID = "GAMESTATE";

void GameState::update()
{
	for (std::size_t i = 0; i < m_stateGameObjects.size(); i++)
	{
		(m_stateGameObjects[i])->update();
	}
}

void GameState::handleInputs()
{
	for (std::size_t i = 0; i < m_stateGameObjects.size(); i++)
	{
		(m_stateGameObjects[i])->handleInputs();
	}
}

void GameState::render()
{
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
	for (std::vector<GameObject*>::iterator it = m_stateGameObjects.begin(); it != m_stateGameObjects.end(); ++it)
	{
		(*it)->draw();
	}
}

