#ifndef __AI__
#define __AI__

#include "GameLogic.h"

#include <map>

class IRobot
{
public:
   virtual ~IRobot(){};
	virtual void play() = 0;
};

class MinMaxRobot : public IRobot
{
public:
	MinMaxRobot(GameLogic& gameLogic)
      : m_gameLogic{ gameLogic }
   {}
	~MinMaxRobot() = default;
   virtual void play() override;
private:
   GameLogic& m_gameLogic;
};

class RandomRobot : public IRobot
{
public:
	RandomRobot(GameLogic& gameLogic)
		: m_gameLogic{ gameLogic }
	{}
	~RandomRobot() = default;
	virtual void play() override;
private:
	GameLogic& m_gameLogic;
};

#endif
