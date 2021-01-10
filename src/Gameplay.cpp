#include "Gameplay.h"

Gameplay::Gameplay()
{
	internalState = GameplayState::GAME_START;
	LoadLevelData();

	Renderer::Instance()->LoadRect("backgroundGameplay", myType::Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	
	playerOne = Player(playerOnePosition, &map,"playerOne", &bombs);
	playerTwo = Player(playerTwoPosition, &map, "playerTwo", &bombs);

	hud = HUD();

	StartTime();

	defaultWallSprite = myType::Rect(0, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	destructibleWallSprite = myType::Rect(SPRITESHEET_RECT_SIZE, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	toDestroyWallSprite = myType::Rect(SPRITESHEET_RECT_SIZE * 2, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
}

Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputManager inputManager)
{
	UpdateTime();

	playerOne.Update(inputManager.upArrowPressed, inputManager.downArrowPressed, inputManager.leftArrowPressed, inputManager.rightArrowPressed, inputManager.spacePressed);
	playerTwo.Update(inputManager.wPressed, inputManager.sPressed, inputManager.aPressed, inputManager.dPressed, inputManager.rightCtrlPressed);

	hud.Update(playerOne.score, playerTwo.score, playerOne.lives, playerTwo.lives, gameTime);

	for (int i = 0; i < bombs.size(); i++)
		bombs[i].Update(deltaTime);

	ClearExplodedBombs();
}

void Gameplay::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->PushImage("backgroundGameplay", "backgroundGameplay");

	for (int i = 0; i < map.size(); i++)
	{
		if (map[i]->destructable)
		{
			if (map[i]->state == 2)
				Renderer::Instance()->PushSprite("items", destructibleWallSprite, map[i]->position);
			else if (map[i]->state == 1)
				Renderer::Instance()->PushSprite("items", toDestroyWallSprite, map[i]->position);
		}
		else
		{
			Renderer::Instance()->PushSprite("items", defaultWallSprite, map[i]->position);
		}
	}

	playerOne.Draw();
	playerTwo.Draw();

	hud.Draw();

	for (int i = 0; i < bombs.size(); i++)
		bombs[i].Draw();

	Renderer::Instance()->Render();
}

void Gameplay::LoadLevelData()
{
	try {
		rapidxml::xml_document<> doc;
		std::ifstream file(CONFIG_FILE_PATH);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		rapidxml::xml_node<>* pRoot = doc.first_node();	// Game node

		rapidxml::xml_node<>* pLevelOne = pRoot->first_node("Level1");

		rapidxml::xml_node<>* pPlayers = pLevelOne->first_node(); // Players Node

		rapidxml::xml_node<>* pNode = pPlayers->first_node(); // Player 1

		// Read lives player One
		rapidxml::xml_attribute<>* pPlayerLives = pNode->first_attribute();

		livesPlayerOne = std::stoi(pPlayerLives->value());
		
		rapidxml::xml_node<>* pPlayerPosition = pNode->first_node(); // Player 1 position
		
		rapidxml::xml_attribute<>* pAttribute = pPlayerPosition->first_attribute();

		int x = std::stoi(pAttribute->value());
		int y = std::stoi(pAttribute->next_attribute()->value());
		playerOnePosition = myType::Rect(x * SPRITESHEET_RECT_SIZE + SPRITESHEET_RECT_SIZE, y * SPRITESHEET_RECT_SIZE + HUD_HEIGHT + SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

		pNode = pNode->next_sibling();
		pPlayerLives = pNode->first_attribute();
		livesPlayerTwo = std::stoi(pPlayerLives->value());

		pPlayerPosition = pNode->first_node();
		pAttribute = pPlayerPosition->first_attribute();
		x = std::stoi(pAttribute->value());
		y = std::stoi(pAttribute->next_attribute()->value());
		playerTwoPosition = myType::Rect(x * SPRITESHEET_RECT_SIZE + SPRITESHEET_RECT_SIZE, y * SPRITESHEET_RECT_SIZE + HUD_HEIGHT + SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

		// Map
		rapidxml::xml_node<>* pMap = pPlayers->next_sibling();
		for (rapidxml::xml_node<>* wNode = pMap->first_node(); wNode; wNode = wNode->next_sibling())
		{
			rapidxml::xml_attribute<>* pAttribute = wNode->first_attribute();

			
			bool destructible;
			std::string destructibleString = pAttribute->value();
			std::istringstream(destructibleString) >> std::boolalpha >> destructible;

			pAttribute = pAttribute->next_attribute();
			int x = std::stoi(pAttribute->value());
			int y = std::stoi(pAttribute->next_attribute()->value());

			myType::Rect wallPosition = myType::Rect(x * SPRITESHEET_RECT_SIZE + SPRITESHEET_RECT_SIZE, y * SPRITESHEET_RECT_SIZE + HUD_HEIGHT + SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

			map.push_back(new Wall(wallPosition, destructible));
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: ";
		std::cout << e.what() << std::endl;
	}
}

void Gameplay::StartTime()
{
	gameTime = 80.0f;
	deltaTime = 0.0f;
	lastTime = clock();
}

void Gameplay::UpdateTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	gameTime -= deltaTime;

	if (gameTime < 0.0f)
		state = SceneState::GOTO_MENU;
}

void Gameplay::ClearExplodedBombs()
{
	for (auto it = bombs.begin(); it != bombs.end();)
	{
		if (it->state == BombState::GONE)
			it = bombs.erase(it);
		else
			it++;
	}
}