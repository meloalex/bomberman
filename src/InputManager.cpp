#include "InputManager.h"

InputManager::InputManager()
{
	mousePosition = myType::Vector2();
	mousePressed = false;
	escPressed = false;
	spacePressed = false;
	rightCtrlPressed = false;
	wPressed = false;
	sPressed = false;
	aPressed = false;
	dPressed = false;
	upArrowPressed = false;
	downArrowPressed = false;
	leftArrowPressed = false;
	rightArrowPressed = false;
	quit = false;

	event = SDL_Event();
}

InputManager::~InputManager()
{

}

void InputManager::Update()
{
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			mousePressed = true;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) escPressed = true;
			if (event.key.keysym.sym == SDLK_SPACE) spacePressed = true;
			if (event.key.keysym.sym == SDLK_RCTRL) rightCtrlPressed = true;
			if (event.key.keysym.sym == SDLK_w) wPressed = true;
			if (event.key.keysym.sym == SDLK_s) sPressed = true;
			if (event.key.keysym.sym == SDLK_a) aPressed = true;
			if (event.key.keysym.sym == SDLK_d) dPressed = true;
			if (event.key.keysym.sym == SDLK_UP) upArrowPressed = true;
			if (event.key.keysym.sym == SDLK_DOWN) downArrowPressed = true;
			if (event.key.keysym.sym == SDLK_LEFT) leftArrowPressed = true;
			if (event.key.keysym.sym == SDLK_RIGHT) rightArrowPressed = true;
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) escPressed = false;
			if (event.key.keysym.sym == SDLK_SPACE) spacePressed = false;
			if (event.key.keysym.sym == SDLK_RCTRL) rightCtrlPressed = false;
			if (event.key.keysym.sym == SDLK_w) wPressed = false;
			if (event.key.keysym.sym == SDLK_s) sPressed = false;
			if (event.key.keysym.sym == SDLK_a) aPressed = false;
			if (event.key.keysym.sym == SDLK_d) dPressed = false;
			if (event.key.keysym.sym == SDLK_UP) upArrowPressed = false;
			if (event.key.keysym.sym == SDLK_DOWN) downArrowPressed = false;
			if (event.key.keysym.sym == SDLK_LEFT) leftArrowPressed = false;
			if (event.key.keysym.sym == SDLK_RIGHT) rightArrowPressed = false;
			break;

		case SDL_MOUSEMOTION:
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;

		default:
			break;
		}
	}
}