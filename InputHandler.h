#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include "SDL.h"
#include "Vector2D.h"

//to move or rename
enum mouseButtonType
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler 
{
public:
	//should be moved somewhere else: no logic in this class
	//actually it should only returns keyboard and mouseInputs (and SDLInputs such as SDL_QUIT)
	static bool askedForQuit();
	static bool windowResized();
	static void onQuit();
	
	//keyboard
	static void updateInputs();
	static bool isKeyDown(SDL_Scancode key);

	//mouse
	static void onMouseMove(SDL_Event &event);
	static void setMouseCoordinates(float &x, float &y);
	static Vector2D getMouseCoordinates();
	static bool getMouseButtonsStates(mouseButtonType buttonType);
};

#endif