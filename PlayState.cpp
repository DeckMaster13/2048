#include "PlayState.h"

#include <algorithm>
#include <iostream>
#include <SDL_image.h>

#include "Constants.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "TextureHandler.h"

#include "Cell.h"
#include "AI.h"

//beurk !
bool isLeftButtonClicked{ false };
bool isLeftButtonReleased{ true };
bool isRightButtonClicked{ false };
bool isRightButtonReleased{ true };

bool isRightArrowDown{ false };
bool isLeftArrowDown{ false };
bool isUpArrowDown{ false };
bool isDownArrowDown{ false };

bool isRobotPlaying{false};

PlayState::PlayState()
{}

void PlayState::update()
{
	if (m_gameLogic.hasLost())
	{
		std::cout << "You lost" << std::endl;
		return;
	}
	RandomRobot robot{m_gameLogic};
	if (isRobotPlaying)
	{
		robot.play();
	}
	GameState::update();
}

void PlayState::render()
{
	for (unsigned i = 0; i < m_stateGameObjects.size(); ++i)
	{
		m_stateGameObjects[i]->draw();
	}
	GameState::render();
	SDL_RenderPresent(Renderer::Instance().getRenderer());
}

bool PlayState::onEnter()
{
	//LogicCell* cell = new Cell(Vector2D(8 + 121 * j, 8 + 121 * i), TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE, Vector2D(/*0.05*TILE_SIZE + */TILE_SIZE*j, /*0.05*TILE_SIZE + */TILE_SIZE*i), TILE_SIZE, TILE_SIZE, 0, "Tile", textureID, 0);

	//TEMPORARY
	const char textureName[] = "sprites/board.png";

	SDL_Surface *image = IMG_Load(textureName);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::Instance().getRenderer(), image);
	std::string textureID = "board";
	TextureHandler::registerTexture(textureID, texture);
	SDL_FreeSurface(image);

	const std::vector<std::vector<LogicCell*>>& logicLines = m_gameLogic.getGlobalGridByLine();
	for (unsigned i = 0; i < logicLines.size(); ++i)
	{
		const std::vector<LogicCell*>& logicLine = logicLines[i];
		for (unsigned j = 0; j < logicLines.size(); ++j)
		{
			Cell* displayCell = new Cell(Vector2D(8 + 121 * j, 8 + 121 * i), TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE, Vector2D(/*0.05*TILE_SIZE + */TILE_SIZE*j, /*0.05*TILE_SIZE + */TILE_SIZE*i), TILE_SIZE, TILE_SIZE, 0, "Tile", textureID, logicLine[j]);
			displayCell->setHidden(false);
			m_stateGameObjects.push_back(displayCell);
		}
	}
	
	//BACKGROUND FOR IMPLEMETING THE INFAMOUSLY MOVE EFFECT
	//unsigned lineNumber{ 4 };//hardcoded
	//unsigned columnNumber{ 4 };//hardcoded

	//m_globalBackground = std::vector<std::vector<GameObject*>>(lineNumber);
	//for (unsigned int i = 0; i < lineNumber; ++i)
	//{
	//	m_globalBackground[i] = std::vector<GameObject*>(columnNumber);
	//	for (unsigned j = 0; j < columnNumber; ++j)
	//	{
	//		Cell* cell = new Cell(Vector2D(8 + 121 * j, 8 + 121 * i), TILE_TEXTURE_SIZE, TILE_TEXTURE_SIZE, Vector2D(/*0.05*TILE_SIZE + */TILE_SIZE*j, /*0.05*TILE_SIZE + */TILE_SIZE*i), TILE_SIZE, TILE_SIZE, 0, "Tile", textureID, 0);
	//		cell->setHidden(true);
	//		m_globalBackground[i][j] = cell;
	//		m_stateGameObjects.push_back(cell);
	//	}
	//}

	return true;
}

bool PlayState::onExit()
{
	//std::cout << "exiting PlayState\n";
	return true;
}

//beurk
static bool isArrowStillDown(SDL_Scancode arrowKey, bool& isArrowDown)
{
	if (isArrowDown)
	{
		if (!InputHandler::isKeyDown(arrowKey)) isArrowDown = false;
		else return true;
	}
	return false;
}

void PlayState::handleInputs()
{
	GameState::handleInputs();

	//isLeftButtonClicked = InputHandler::getMouseButtonsStates(mouseButtonType::LEFT);
	//if (isLeftButtonClicked)
	//{

	//	if (isLeftButtonReleased)
	//	{
	//		isLeftButtonReleased = false;
	//		Vector2D mouseCoordinates = InputHandler::getMouseCoordinates();
	//		unsigned int j = std::ceil((1.0*mouseCoordinates.getX()) / TILE_SIZE)-1;
	//		unsigned int i = std::ceil((1.0*mouseCoordinates.getY()) / TILE_SIZE)-1;

	//		if (i >= m_globalGridByLine.size() || j >= m_globalGridByLine[i].size()) return;

	//		GameObject* cell = m_globalGridByLine[i][j];
	//		cell->setHidden(!cell->getHidden());
	//	}
	//}
	//else
	//{
	//	isLeftButtonReleased = true;
	//}

	isRightButtonClicked = InputHandler::getMouseButtonsStates(mouseButtonType::RIGHT);
	if (isRightButtonClicked)
	{

		if (isRightButtonReleased)
		{
			isRightButtonReleased = false;
			isRobotPlaying = !isRobotPlaying;
		}
	}
	else
	{
		isRightButtonReleased = true;
	}

	if (isArrowStillDown(SDL_SCANCODE_RIGHT, isRightArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_LEFT, isLeftArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_UP, isUpArrowDown)
		|| isArrowStillDown(SDL_SCANCODE_DOWN, isDownArrowDown)
		) return;

	MoveDirection direction{ None };
	if (InputHandler::isKeyDown(SDL_SCANCODE_RIGHT))
	{
		isRightArrowDown = true;
		direction = Right;
	}
	else if (InputHandler::isKeyDown(SDL_SCANCODE_LEFT))
	{
		isLeftArrowDown = true;
		direction = Left;
	}
	else if (InputHandler::isKeyDown(SDL_SCANCODE_UP))
	{
		isUpArrowDown = true;
		direction = Up;
	}
	else if (InputHandler::isKeyDown(SDL_SCANCODE_DOWN))
	{
		isDownArrowDown = true;
		direction = Down;
	}

	m_gameLogic.move(direction);
}
