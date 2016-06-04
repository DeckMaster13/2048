#include "GameObject.h"

#include "TextureHandler.h"
#include "Renderer.h"

GameObject::GameObject()
	: m_objectID("DefaultId"), m_textureWidth(0), m_textureHeight(0), m_numFrame(0), m_width(0), m_height(0)
{}

//create the object with the SDL_Rect for the source/destination of the texture
GameObject::GameObject(Vector2D position, int width, int height, int numFrame, std::string objectID, std::string textureID)
	: m_position(position), m_width(width), m_height(height), m_numFrame(numFrame), m_objectID(objectID), m_textureID(textureID), m_isHidden(false)
{}
//create the object with the SDL_Rect for the source/destination of the texture
GameObject::GameObject(Vector2D texturePosition, int textureWidth, int textureHeight, Vector2D position, int width, int height, int numFrame, std::string objectID, std::string textureID)
	: m_texturePosition(texturePosition)
	, m_textureWidth(textureWidth)
	, m_textureHeight(textureHeight)
	, m_position(position)
	, m_width(width)
	, m_height(height)
	, m_numFrame(numFrame)
	, m_objectID(objectID)
	, m_textureID(textureID)
	, m_isHidden(false)
{}


void GameObject::draw()
{
	if (m_isHidden) return;

	SDL_Rect srcRect, dstRect;
	dstRect.x = static_cast<int>(m_position.getX());
	dstRect.y = static_cast<int>(m_position.getY());
	dstRect.h = m_height;
	dstRect.w = m_width;

	srcRect.w = m_textureWidth;
	srcRect.h = m_textureHeight;
	srcRect.x = static_cast<int>(m_texturePosition.getX() + m_numFrame * srcRect.w);
	srcRect.y = static_cast<int>(m_texturePosition.getY());

	SDL_Texture *texture = TextureHandler::getTexturesMap()[m_textureID];//to remove, it should have an internal pointer to its own texture or the texture map should be passed as a parameter
	SDL_RenderCopy(Renderer::Instance().getRenderer(), texture, &srcRect, &dstRect);
	//SDL_RenderPresent(Renderer::Instance().getRenderer());
}
