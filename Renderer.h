#ifndef __RENDERER__
#define __RENDERER__

#include "Vector2D.h"
#include "SDL.h"

class Renderer
{
public:
	static Renderer& Instance();
	SDL_Renderer* getRenderer();
	void updateRenderer();
	
private:
	Renderer();
	Renderer(const Renderer& rhs) = delete;
	Renderer& operator=(const Renderer& rhs) = delete;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;

	Vector2D m_windowPosition;
	int m_width;
	int m_height;
};

#endif
