#pragma once
#include <sdl/SDL.h>
#include "Types.h"

class InputManager
{
public:
	myType::Vector2 mousePosition;
	bool mousePressed;
	bool escPressed;
	bool spacePressed;
	bool rightCtrlPressed;
	bool wPressed;
	bool sPressed;
	bool aPressed;
	bool dPressed;
	bool upArrowPressed;
	bool downArrowPressed;
	bool leftArrowPressed;
	bool rightArrowPressed;
	bool quit;

	SDL_Event event;

	InputManager();
	~InputManager();

	void Update();
};

