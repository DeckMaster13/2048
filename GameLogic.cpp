#include "GameLogic.h"
#include "LogicCell.h"

#include <algorithm>
#include <iostream>

#include <cmath>
#include <random>

#include <chrono>
#include <functional>

bool isEmpty(LogicCell* cell)
{
	return (cell->getValue() == 0);
}

bool hasEmptyCell(const std::vector<LogicCell*>& line)
{
	return std::find_if(line.begin(), line.end(), isEmpty) != line.end();
}

bool isNotEmpty(LogicCell* cell)
{
	return (cell->getValue() != 0);
}

//on compacte tout dans le sens dans lequel on appuie
void GameLogic::compressOneLine(std::vector<LogicCell*>& line)
{
	std::vector<LogicCell*>::reverse_iterator emptyCellIt;
	std::vector<LogicCell*>::reverse_iterator nonEmptyCellIt;
	do
	{
		emptyCellIt = std::find_if(line.rbegin(), line.rend(), isEmpty);
		nonEmptyCellIt = std::find_if(emptyCellIt, line.rend(), isNotEmpty);

		if (emptyCellIt == line.rend() || nonEmptyCellIt == line.rend()) return;

		(*emptyCellIt)->setValue((*nonEmptyCellIt)->getValue());
		(*nonEmptyCellIt)->resetValue();
	}
	while (nonEmptyCellIt > emptyCellIt);
}

void GameLogic::resolveOneLine(std::vector<LogicCell*>& line)
{
	std::size_t i { line.size()-1 };

	LogicCell* currentCell;
	LogicCell* previousCell;
	do
	{
		currentCell = line[i];
		previousCell = line[i-1];

		if (currentCell->getValue() == previousCell->getValue())
		{
			currentCell->doubleValue();
			previousCell->resetValue();
		}
		i--;
	} while (i > 0 && line[i-1]->getValue() != 0);
		
}

void GameLogic::moveOneLine(std::vector<LogicCell*>& line)
{
	//compress, resolve and compress again: 2 2 2 2 => 0 4 0 4 => 0 0 4 4  ||  2 0 2 2 => 0 2 2 2 => 0 2 0 4 => 0 0 2 4
	compressOneLine(line);
	resolveOneLine(line);
	compressOneLine(line);
}

GameLogic::GameLogic()
{
	m_globalGridByLine = std::vector<std::vector<LogicCell*>>(m_linesNumber);
	m_reversedGlobalGridByLine = std::vector<std::vector<LogicCell*>>(m_linesNumber);
	for (unsigned int i = 0; i < m_linesNumber; ++i)
	{
		m_globalGridByLine[i] = std::vector<LogicCell*>(m_columnsNumber);
		m_reversedGlobalGridByLine[i] = std::vector<LogicCell*>(m_columnsNumber);
		for (unsigned int j = 0; j < m_columnsNumber; ++j)
		{
			LogicCell* cell = new LogicCell(i,j);
			m_globalGridByLine[i][j] = cell;
			m_reversedGlobalGridByLine[i][m_columnsNumber - j - 1] = cell;
		}
	}
	m_globalGridByColumn = std::vector<std::vector<LogicCell*>>(m_columnsNumber);
	m_reversedGlobalGridByColumn = std::vector<std::vector<LogicCell*>>(m_columnsNumber);
	for (unsigned int j = 0; j < m_columnsNumber; ++j)
	{
		m_globalGridByColumn[j] = std::vector<LogicCell*>(m_linesNumber);
		m_reversedGlobalGridByColumn[j] = std::vector<LogicCell*>(m_linesNumber);
		for (unsigned i = 0; i < m_linesNumber; ++i)
		{
			m_globalGridByColumn[j][i] = m_globalGridByLine[i][j];
			m_reversedGlobalGridByColumn[j][m_linesNumber - i - 1] = m_reversedGlobalGridByLine[i][j];
		}
	}

	addRandomCell();
}

void GameLogic::move(MoveDirection moveDirection)
{
	bool hasMoved = true;
	switch (moveDirection)
	{
	case Right:
		std::for_each(m_globalGridByLine.begin(), m_globalGridByLine.end(), moveOneLine);
		break;
	case Left:
		std::for_each(m_reversedGlobalGridByLine.begin(), m_reversedGlobalGridByLine.end(), moveOneLine);
		break;
	case Up:
		std::for_each(m_reversedGlobalGridByColumn.begin(), m_reversedGlobalGridByColumn.end(), moveOneLine);
		break;
	case Down:
		std::for_each(m_globalGridByColumn.begin(), m_globalGridByColumn.end(), moveOneLine);
		break;
	case None:
	default:
		hasMoved = false;
	}
	if (hasMoved)
	{
		addRandomCell();
		std::cout << "score: " << m_score << std::endl;
	}
}

bool GameLogic::addRandomCell()
{
	bool hasSpace = std::find_if(m_globalGridByLine.begin(), m_globalGridByLine.end(), hasEmptyCell) != m_globalGridByLine.end();

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
	unsigned seed2{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::default_random_engine engine2{ seed2 };
	std::uniform_int_distribution<int> distribution2(0, 10);
	auto generator2 = std::bind(distribution2, engine2);
	
	unsigned valueToAdd = 2;
	if (generator2() == 1) valueToAdd = 4;

	current->setValue(valueToAdd);
	addToScore(valueToAdd);
	m_livingCells += 1;
	std::cout << "score: " << m_score << std::endl;

	if (m_score > 2048) m_hasWon = true;//win

	return true;
}
