#include "Menu.h"

Menu::Menu()
{
	soundOn = true;

	// Buttons
	buttons["lvl1"] = new Button("play_button", "Level One", myType::Vector2(0, 100), myType::Color(0, 0, 0, 255), myType::Color(255, 0, 0, 255), "gameplay", true);
	buttons["lvl2"] = new Button("play_button2", "Level Two", myType::Vector2(0, 200), myType::Color(0, 0, 0, 255), myType::Color(255, 0, 0, 255), "gameplay", true);
	buttons["ranking"] = new Button("ranking_button", "Ranking", myType::Vector2(0, 300), myType::Color(0, 0, 0, 255), myType::Color(255, 0, 0, 255), "gameplay", true);
	buttons["toggleSound"] = new Button("sound_button", "Sound ON", myType::Vector2(0, 400), myType::Color(0, 0, 0, 255), myType::Color(255, 0, 0, 255), "gameplay", true);
	buttons["exit"] = new Button("exit_button", "Exit", myType::Vector2(0, 500), myType::Color(0, 0, 0, 255), myType::Color(255, 0, 0, 255), "gameplay", true);
}

Menu::~Menu()
{
	for (std::pair<std::string, Button*> pair : buttons)
		delete(pair.second);
}

void Menu::Update(InputManager inputManager)
{
	//Update buttons
	for (std::pair<std::string, Button*> pair : buttons)
		pair.second->Update(inputManager.mousePosition);

	if (buttons["exit"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
		state = SceneState::EXIT;

	if (buttons["lvl1"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
		state = SceneState::GOTO_GAMEPLAY;

	if (buttons["lvl2"]->isPressed(inputManager.mousePosition, inputManager.mousePressed))
		state = SceneState::GOTO_GAMEPLAY2;
}

void Menu::Draw()
{
	Renderer::Instance()->Clear();

	//Draw each button
	for (std::pair<std::string, Button*> pair : buttons)
		pair.second->Draw();

	Renderer::Instance()->Render();
}
