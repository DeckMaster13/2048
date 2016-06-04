#include "Renderer.h"
#include "SDL.h"
#include "Constants.h"

#include <memory>

Renderer::Renderer()
{
	m_windowPosition = Vector2D(100, 100);
	m_width = 300;//445;
	m_height = 300;//445
	updateTileSize((m_width / CELL_NUMBER_PER_LINE));
	m_window = SDL_CreateWindow("DeckGame", m_windowPosition.getX(), m_windowPosition.getY(), m_width, m_height, 0 /*SDL_WINDOW_RESIZABLE*/);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}

Renderer& Renderer::Instance()
{
	static std::unique_ptr<Renderer> singleton;
	if (!singleton)
		singleton.reset(new Renderer);

	return *singleton.get();
}

SDL_Renderer* Renderer::getRenderer()
{
	return m_renderer;
} 

void Renderer::updateRenderer()
{}


