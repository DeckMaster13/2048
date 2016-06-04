#ifndef __GAMELOGIC__
#define __GAMELOGIC__

#include <vector>

enum MoveDirection
{
	Right,
	Left,
	Up,
	Down,
	None
};

class LogicCell;

class GameLogic
{
public:
	GameLogic();

	//2048 specific command
	bool addRandomCell();
	void addToScore(unsigned valueToAdd) { m_score += valueToAdd; }
	void move(MoveDirection direction);
	bool hasWon() const
	{
		return m_hasWon;
	}
	bool hasLost() const
	{
		return m_hasLost;
	}
	unsigned getScore() const
	{
		return m_score;
	}
	const std::vector<std::vector<LogicCell*>>& getGlobalGridByLine() const
	{
		return m_globalGridByLine;
	}

public://public for unit test
	static void moveOneLine(std::vector<LogicCell*>& line);
	static void resolveOneLine(std::vector<LogicCell*>& line);
	static void compressOneLine(std::vector<LogicCell*>& line);
private:
	//board
	std::vector<std::vector<LogicCell*>> m_globalGridByLine{};
	std::vector<std::vector<LogicCell*>> m_globalGridByColumn{};
	std::vector<std::vector<LogicCell*>> m_reversedGlobalGridByLine{};
	std::vector<std::vector<LogicCell*>> m_reversedGlobalGridByColumn{};
	unsigned m_columnsNumber{ 4 };
	unsigned m_linesNumber{ 4 };

	//other infos
	unsigned m_score{ 0 };
	bool m_hasLost{ false };
	bool m_hasWon{ false };
	//audit
	unsigned m_livingCells{ 0 };

	friend class AI;
	friend class UnitTest;
};

#endif