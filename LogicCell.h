#ifndef __LOGICCELL__
#define __LOGICCELL__

#include "Vector2D.h"

class LogicCell
{
public:
	LogicCell(float x, float y)
		: m_position{x,y}
	{}

	void resetValue()
	{
		m_value = 0;
	}

	void doubleValue()
	{
		m_value *= 2;
	}

	unsigned getValue() const
	{
		return m_value;
	}

	void setValue(unsigned newValue)
	{
		m_value = newValue;
	}

	Vector2D getPosition() const
	{
		return m_position;
	}

private:
	Vector2D m_position{};
	unsigned m_value{ 0 };
};


#endif