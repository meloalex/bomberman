#include "GameController.h"

GameController::GameController()
{
	gameRunning = true;
	gameState = GameState::MENU;
	currentScene = new Menu();
}

GameController::~GameController()
{
	delete(currentScene);
}

void GameController::Update()
{
	if (inputManager.quit) gameState = GameState::EXIT;

	switch (gameState)
	{
	case GameState::MENU:

		switch (currentScene->state)
		{
		case SceneState::GOTO_GAMEPLAY:
			gameState = GameState::GAMEPLAY;
			delete(currentScene);
			currentScene = new Gameplay("Level1");
			break;

		case SceneState::GOTO_GAMEPLAY2:
			gameState = GameState::GAMEPLAY2;
			delete(currentScene);
			currentScene = new Gameplay("Level2");
			break;

		case SceneState::GOTO_RANKING:
			gameState = GameState::RANKING;
			delete(currentScene);
			currentScene = new Ranking();
			break;

		case SceneState::EXIT:
			gameState = GameState::EXIT;
			break;

		default:
			break;
		}

		break;

	case GameState::GAMEPLAY:
		switch (currentScene->state)
		{
		case SceneState::GOTO_MENU:
			gameState = GameState::MENU;
			delete(currentScene);
			currentScene = new Menu();
			break;
		default:
			break;
		}
		break;

	case GameState::GAMEPLAY2:
		switch (currentScene->state)
		{
		case SceneState::GOTO_MENU:
			gameState = GameState::MENU;
			delete(currentScene);
			currentScene = new Menu();
			break;
		default:
			break;
		}
		break;

	case GameState::RANKING:
		switch (currentScene->state)
		{
		case SceneState::GOTO_MENU:
			gameState = GameState::MENU;
			delete(currentScene);
			currentScene = new Menu();
			break;
		default:
			break;
		}
		break;

	case GameState::EXIT:
		gameRunning = false;
		break;
	}

	inputManager.Update();
	currentScene->Update(inputManager);
	currentScene->Draw();
}