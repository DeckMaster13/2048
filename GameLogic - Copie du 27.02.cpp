#include "GameLogic.h"
#include "LogicCell.h"

#include <iostream>

#include <cmath>
#include <random>

#include <chrono>
#include <functional>

GameLogic::GameLogic()
{
	m_globalGridByLine = std::vector<std::vector<LogicCell*>>(m_linesNumber);
	for (unsigned int i = 0; i < m_linesNumber; ++i)
	{
		m_globalGridByLine[i] = std::vector<LogicCell*>(m_columnsNumber);
		for (unsigned int j = 0; j < m_columnsNumber; ++j)
		{
			LogicCell* cell = new LogicCell(i,j);
			m_globalGridByLine[i][j] = cell;
		}
	}
	m_globalGridByColumn = std::vector<std::vector<LogicCell*>>(m_columnsNumber);
	for (unsigned int j = 0; j < m_columnsNumber; ++j)
	{
		m_globalGridByColumn[j] = std::vector<LogicCell*>(m_linesNumber);
		for (unsigned i = 0; i < m_linesNumber; ++i)
		{
			m_globalGridByColumn[j][i] = m_globalGridByLine[i][j];
		}
	}

	addTwo();
}

template<typename T>
static void retrieveP1P2P3(T begin, T end, LogicCell** p1, LogicCell** p2, LogicCell** p3)
{
	auto p1It = begin;
	*p1 = *p1It;
	while (*p1 && (*p1)->getValue())
		*p1 = ++p1It != end ? *p1It : nullptr;

	auto p2It = begin;
	*p2 = *p2It;
	while (*p2 && !(*p2)->getValue())
		*p2 = ++p2It != end ? *p2It : nullptr;

	if (!*p2) return;//0 cell alive

	auto p3It = ++p2It;
	if (p3It == end)
	{
		*p3 = nullptr;
		return;
	}//1 cell alive
	*p3 = *p3It;
	while (*p3 && !(*p3)->getValue())
		*p3 = ++p3It != end ? *p3It : nullptr;
}

void GameLogic::handleRoundWithP1P2P3(LogicCell* p1, LogicCell* p2, LogicCell* p3, double p1p2delta)
{
	if (p1) std::cout << "eh non" << p1->getPosition().getX() << "," << p1->getPosition().getY() << std::endl;
	//here is a motherfucking bug
	//p1 is always fucking null
	//:) (fuck)

	if (p2)
	{
		if (!p3) //one cell
		{
			if (p1 && p1p2delta > 0)
			{
				if (p1) std::cout << "eh non" << p1->getPosition().getX() << "," << p1->getPosition().getY() << std::endl;
				p1->replaceBy(p2);
				p2->resetValue();
			}
		}
		else //two cells
		{
			if (p2->getValue() == p3->getValue())
			{
				if (p1 && p1p2delta > 0)
				{
					p1->doubleValueFrom(p2);
					p2->resetValue();
					p3->resetValue();
				}
				else
				{
					p2->doubleValueFrom(p2);
					p3->resetValue();
				}
				m_livingCells = -1;
			}
			else
			{
				if (p1 && p1p2delta > 0)
				{
					p1->replaceBy(p2);
					p2->resetValue();
				}
			}
		}
	}
}

void GameLogic::moveRight()
{
	for (unsigned i = 0; i < m_columnsNumber; ++i)
	{
		auto rbegin = m_globalGridByLine[i].rbegin();
		auto rend = m_globalGridByLine[i].rend();
		while (rbegin != rend)
		{
			LogicCell *p1{};
			LogicCell *p2{};
			LogicCell *p3{};

			retrieveP1P2P3<std::vector<LogicCell*>::reverse_iterator>(rbegin, rend, &p1, &p2, &p3);

			double p1p2delta{};
			if (p1 && p2)
				p1p2delta = p1->getPosition().getX() - p2->getPosition().getX();
			handleRoundWithP1P2P3(p1, p2, p3, p1p2delta);
			++rbegin;
		}
	}
}

void GameLogic::moveLeft()
{
	for (unsigned i = 0; i < m_columnsNumber; ++i)
	{
		auto begin = m_globalGridByLine[i].begin();
		auto end = m_globalGridByLine[i].end();
		while (begin != end)
		{
			LogicCell *p1{};
			LogicCell *p2{};
			LogicCell *p3{};

			retrieveP1P2P3<std::vector<LogicCell*>::iterator>(begin, end, &p1, &p2, &p3);

			double p1p2delta{};
			if (p1 && p2)
				p1p2delta = p2->getPosition().getX() - p1->getPosition().getX();
			handleRoundWithP1P2P3(p1, p2, p3, p1p2delta);
			++begin;
		}
	}

}

void GameLogic::moveUp()
{
	for (unsigned j = 0; j < m_linesNumber; ++j)
	{
		auto begin = m_globalGridByColumn[j].begin();
		auto end = m_globalGridByColumn[j].end();
		while (begin != end)
		{
			LogicCell *p1{};
			LogicCell *p2{};
			LogicCell *p3{};

			retrieveP1P2P3<std::vector<LogicCell*>::iterator>(begin, end, &p1, &p2, &p3);

			double p1p2delta{};
			if (p1 && p2)
				p1p2delta = p2->getPosition().getY() - p1->getPosition().getY();
			handleRoundWithP1P2P3(p1, p2, p3, p1p2delta);
			++begin;
		}
	}
}

void GameLogic::moveDown()
{
	for (unsigned j = 0; j < m_linesNumber; ++j)
	{
		auto rbegin = m_globalGridByColumn[j].rbegin();
		auto rend = m_globalGridByColumn[j].rend();
		while (rbegin != rend)
		{
			LogicCell *p1{};
			LogicCell *p2{};
			LogicCell *p3{};

			retrieveP1P2P3<std::vector<LogicCell*>::reverse_iterator>(rbegin, rend, &p1, &p2, &p3);

			double p1p2delta{};
			if (p1 && p2)
				p1p2delta = p1->getPosition().getY() - p2->getPosition().getY();
			handleRoundWithP1P2P3(p1, p2, p3, p1p2delta);
			++rbegin;
		}
	}
}

void GameLogic::move(MoveDirection moveDirection)
{
	bool hasMoved = true;
	switch (moveDirection)
	{
	case Right:
		moveRight();
		break;
	case Left:
		moveLeft();
		break;
	case Up:
		moveUp();
		break;
	case Down:
		moveDown();
		break;
	case None:
	default:
		hasMoved = false;
	}
	if (hasMoved)
	{
		addTwo();
		std::cout << "score: " << m_score << std::endl;
	}
}

bool GameLogic::addTwo()
{
	bool hasSpace{ false };
	for (unsigned i = 0; i < m_columnsNumber; ++i)
	{
		for (unsigned j = 0; j < m_columnsNumber && !hasSpace; ++j)
		{
			LogicCell* cell = m_globalGridByLine[i][j];
			if (!cell->getValue()) hasSpace = true;
		}
	}

	if (!hasSpace) return false;

	unsigned seed{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::default_random_engine engine{ seed };

	std::uniform_int_distribution<int> distribution(0, m_linesNumber - 1);

	auto generator = std::bind(distribution, engine);

	LogicCell* current = nullptr;
	do
	{
		int i = generator();
		int j = generator();
		//std::cout << "i: " << i << std::endl;
		//std::cout << "j: " << j << std::endl;

		current = m_globalGridByLine[i][j];
	} while (current->getValue());

	if (current->getValue())
	{
		m_hasLost = true;
		return false;//gameOver
	}
	current->setValue(2);
	addToScore(2);
	m_livingCells += 1;
	std::cout << "score: " << m_score << std::endl;

	if (m_score > 2048) m_hasWon = true;//win

	return true;
}
