#include "AI.h"

#include <cmath>
#include <random>

#include <chrono>
#include <functional>

void MinMaxRobot::play()
{
	unsigned seed{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::default_random_engine engine{ seed };
	std::uniform_int_distribution<int> distribution(0, 3);
	auto generator = std::bind(distribution, engine);

	MoveDirection direction{ None };
	switch (generator())
	{
	case 0:
		direction = Right;
		break;
	case 1:
		direction = Left;
		break;
	case 2:
		direction = Up;
		break;
	case 3:
		direction = Down;
		break;
	}

	m_gameLogic.move(direction);
	//SDL_Delay(2000);
}

void RandomRobot::play()
{
	unsigned seed{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::default_random_engine engine{ seed };
	std::uniform_int_distribution<int> distribution(0, 3);
	auto generator = std::bind(distribution, engine);

	MoveDirection direction{ None };
	switch (generator())
	{
	case 0:
		direction = Right;
		break;
	case 1:
		direction = Left;
		break;
	case 2:
		direction = Up;
		break;
	case 3:
		direction = Down;
		break;
	}

   m_gameLogic.move(direction);
	//SDL_Delay(2000);
}
