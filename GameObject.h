#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "SDL.h"
#include "Vector2D.h"
#include <string>

class GameObject
{
public:
	//non virtual
	GameObject();
	GameObject(Vector2D position, int width, int height, int numFrame, std::string objectID, std::string textureID);
	GameObject(Vector2D texturePosition, int textureWidth, int textureHeight, Vector2D position, int width, int height, int numFrame, std::string objectID, std::string textureID);

	//virtual
	virtual void draw();

	//pure virtual
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void handleInputs() = 0;

	//operator overloading
	bool operator==(GameObject* g2)
	{
		if (g2)
		{
			return !(getObjectID().compare(g2->getObjectID()));
		}
		return false;
	}

	const Vector2D & getPosition() const { return m_position; }
	const int getWidth() const { return m_width; }
	const int getHeight() const { return m_height; }
	std::string getObjectID() const { return m_objectID; };
	bool getHidden() const { return m_isHidden; }//toRemove
	void setHidden(bool newValue) { m_isHidden = newValue; }//toRemove

protected:
	std::string m_objectID;
	std::string m_textureID;
	 
	Vector2D m_texturePosition;
	int m_textureWidth, m_textureHeight;

	Vector2D m_position;
	int m_width, m_height, m_numFrame;
	bool m_isHidden;
};

#endif