#include "Cell.h"

#include "TextureHandler.h"
#include "Renderer.h"
#include "InputHandler.h"

void Cell::init()
{}

void Cell::update()
{
	updateTextureWithValue();
}

void Cell::handleInputs()
{}

void Cell::draw()
{
	if (m_isHidden)
		return;

	SDL_Rect srcRect, dstRect;
	dstRect.x = static_cast<int>(m_position.getX());
	dstRect.y = static_cast<int>(m_position.getY());
	dstRect.h = m_height;
	dstRect.w = m_width;

	srcRect.w = m_textureWidth;
	srcRect.h = m_textureHeight;
	srcRect.x = static_cast<int>(m_texturePosition.getX() + m_numFrame * srcRect.w);
	srcRect.y = static_cast<int>(m_texturePosition.getY());
	SDL_Texture *texture = NULL;

	texture = TextureHandler::getTexturesMap()[m_textureID];//to remove, it should have an internal pointer to its own texture or the texture map should be passed as a parameter

	SDL_RenderCopy(Renderer::Instance().getRenderer(), texture, &srcRect, &dstRect);
}

void Cell::resetValue()
{
	m_isHidden = true;
	setValue(0);
	updateTextureWithValue();
}

void Cell::doubleValueFrom(const Cell* movingCell)
{
	m_isHidden = false;
	setValue(movingCell->getValue() * 2);
	updateTextureWithValue();
}

void Cell::updateTextureWithValue()
{
	unsigned int i = 0;
	unsigned int j = 0;
	switch (getValue())
	{
	case 2:
		break;
	case 4:
		j = 1;
		break;
	case 8:
		j = 2;
		break;
	case 16:
		j = 3;
		break;
	case 32:
		i = 1;
		j = 0;
		break;
	case 64:
		i = 1;
		j = 1;
		break;
	case 128:
		i = 1;
		j = 2;
		break;
	case 256:
		i = 1;
		j = 3;
		break;
	case 512:
		i = 2;
		j = 0;
		break;
	case 1024:
		i = 2;
		j = 1;
		break;
	case 2048:
		i = 2;
		j = 2;
		break;
	case 0:
	default:
		i = 3;
		j = 3;
		break;
	}

	m_texturePosition = Vector2D(8 + 121 * j, 8 + 121 * i);
}
