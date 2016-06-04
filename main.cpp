#include "Game.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Renderer.h"
#include "TextureHandler.h"
#include "SDL.h"
#include "SDL_image.h"

#include <vector>

int main(int argc, char ** argv)
{
	/* Instantiating the variables */
	Uint32 frameStartTime, frameEllapsedTime;
	const int FPS = 10;
	const int DELAY_TIME = 1000.0f / FPS;

	TheGame::Instance().init();

	/* Running Loop */
	while (TheGame::Instance().isRunning())
	{
		frameStartTime = SDL_GetTicks();

		TheGame::Instance().render();
		TheGame::Instance().handleInputs();
		TheGame::Instance().update();

		frameEllapsedTime = SDL_GetTicks() - frameStartTime;
		if (frameEllapsedTime < DELAY_TIME){
			SDL_Delay((int)(DELAY_TIME - frameEllapsedTime));
		}
	}

	/* What to do if running ends */
	TheGame::Instance().quit();

	return 0;
}

