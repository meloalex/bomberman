#pragma once
#include "InputManager.h"
#include "Types.h"
#include "Renderer.h"

enum class SceneState { RUNNING, PAUSED, GOTO_MENU, GOTO_GAMEPLAY, GOTO_RANKING, EXIT };

class Scene
{
protected:
	std::string backgroundTexture;
	myType::Rect backgroundRect;

public:
	Scene();
	~Scene();

	SceneState state;

	virtual void Update(InputManager inputManager) = 0;
	virtual void Draw() = 0;
};

