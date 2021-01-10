#include "Gameplay.h"

Gameplay::Gameplay()
{
}

Gameplay::Gameplay(std::string level)
{
	internalState = GameplayState::GAME_START;
	std::cout << level << std::endl;
	LoadLevelData(level);

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
	BombCollision();
	PowerUpsCollision();

	for (PowerUp* p : powerUps)
		p->Update(deltaTime);

	if (playerOne.lives <= 0 || playerTwo.lives <= 0)
		state = SceneState::GOTO_MENU;
}

void Gameplay::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->PushImage("backgroundGameplay", "backgroundGameplay");

	for (Wall* w : map)
		w->Draw();

	for (PowerUp* p : powerUps)
		p->Draw();

	playerOne.Draw();
	playerTwo.Draw();

	hud.Draw();

	for (int i = 0; i < bombs.size(); i++)
		bombs[i].Draw();

	Renderer::Instance()->Render();
}

void Gameplay::LoadLevelData(std::string level)
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

		rapidxml::xml_node<>* pLevelOne = pRoot->first_node(level.c_str());

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
		{
			if (it->propietary == "playerOne")
				playerOne.hasBombPlaced = false;
			else if (it->propietary == "playerTwo")
				playerTwo.hasBombPlaced = false;

			it = bombs.erase(it);
		}
		else
			it++;
	}
}

void Gameplay::BombCollision() {
	for (auto it = bombs.begin(); it != bombs.end();)
	{
		if (it->state == BombState::EXPLODING && !it->hasAlreadyExploded)
		{
			bool hasHitPlayerOne = myType::RectRectCollision(playerOne.GetPosition(), it->GetPosition());

			for (int i = 0; i < 8; i++)
			{
				hasHitPlayerOne = myType::RectRectCollision(playerOne.GetPosition(), it->explosionsPositions[i]);
				if (hasHitPlayerOne) break;
			}

			if (hasHitPlayerOne && !playerOne.hasShield)
			{
				playerTwo.score += 100;
				playerOne.lives--;
				it->hasAlreadyExploded = true;
				std::cout << "has hit player one \n";
			}

			bool hasHitPlayerTwo = myType::RectRectCollision(playerTwo.GetPosition(), it->GetPosition());

			for (int i = 0; i < 8; i++)
			{
				hasHitPlayerTwo = myType::RectRectCollision(playerTwo.GetPosition(), it->explosionsPositions[i]);
				if (hasHitPlayerTwo) break;
			}

			if (hasHitPlayerTwo && !playerTwo.hasShield)
			{
				playerOne.score += 100;
				playerTwo.lives--;
				it->hasAlreadyExploded = true;
				std::cout << "has hit player two \n";
			}

			// Check walls
			for (int i = 0; i < map.size(); i++)
			{
				bool hasHitWall = false;

				for (int j = 0; j < 8; j++)
				{
					hasHitWall = myType::RectRectCollision(map[i]->position, it->explosionsPositions[j]);
					if (hasHitWall) break;
				}

				if (hasHitWall)
				{
					map[i]->TakeDamage();
					it->hasAlreadyExploded = true;
					std::cout << "has hit a wall \n";

					if (map[i]->state == 0)
					{
						map.erase(map.begin() + i);
						DropPowerUp(it->GetPosition());
						if (it->propietary == "playerOne")
						{
							playerOne.score += 15;
						}
						else if (it->propietary == "playerTwo")
						{
							playerTwo.score += 15;
						}
					}
				}
			}
		}

		it++;
	}
}

void Gameplay::DropPowerUp(myType::Rect startPosition)
{
	/* initialize random seed: */
	srand(time(NULL));
	bool dropProbability = (rand() % 100) < 20;

	if (!dropProbability) return; // No drop

	int powerUpProbab = (rand() % 100) < 50;
	if (powerUpProbab < 50)
	{
		powerUps.push_back(new Rollers(startPosition));
	}
	else
	{
		powerUps.push_back(new Shield(startPosition));
	}
}

void Gameplay::PowerUpsCollision()
{
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (myType::RectRectCollision(powerUps[i]->GetPosition(), playerOne.GetPosition()) && !powerUps[i]->activated)
		{
			powerUps[i]->Start(&playerOne);
		}

		if (myType::RectRectCollision(powerUps[i]->GetPosition(), playerTwo.GetPosition()) && !powerUps[i]->activated)
		{
			powerUps[i]->Start(&playerTwo);
		}

		if (powerUps[i]->stopPls)
		{
			powerUps.erase(powerUps.begin() + i);
		}
	}
}