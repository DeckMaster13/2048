#ifndef __CELL__
#define __CELL__

#include "GameObject.h"
#include "LogicCell.h"

class Cell : public GameObject
{
public:
	//non virtual
	Cell()
	{}
	Cell(Vector2D texturePosition, int textureWidth, int textureHeight, Vector2D position, int width, int height, int numFrame, std::string objectID, std::string textureID, LogicCell* logicCell)
		: GameObject(texturePosition, textureWidth, textureHeight, position, width, height, numFrame, objectID, textureID), m_logicCell(logicCell), m_targetPosition(position)
	{
		m_isHidden = true;
		updateTextureWithValue();
	}

	~Cell()
	{}

	//pure virtual
	virtual void init();
	virtual void update();
	virtual void handleInputs();

	//virtual
	virtual void draw();

	void doubleValueFrom(const Cell* movingCell);
	void resetValue();

	unsigned int getValue() const
	{
		return m_logicCell ? m_logicCell->getValue() : 0;
	}
	void setValue(unsigned value)
	{
		m_logicCell->setValue(value);
		updateTextureWithValue();
	}

private:
	void updateTextureWithValue();
	LogicCell* m_logicCell {nullptr};
private:
	Vector2D m_targetPosition;
};

#endif