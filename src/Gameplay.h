#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Scene.h"
#include "Button.h"
#include "Wall.h"
#include "Player.h"
#include "HUD.h"
#include "Bomb.h"
#include "PowerUp.h"
#include "Rollers.h"
#include "Shield.h"

#include "../dep/inc/xml/rapidxml.hpp"
#include "../dep/inc/xml/rapidxml_iterators.hpp"
#include "../dep/inc/xml/rapidxml_print.hpp"
#include "../dep/inc/xml/rapidxml_utils.hpp"

#define CONFIG_FILE_PATH "../res/files/config.xml"
#define MAP_SIZE_HORIZONTAL 15
#define MAP_SIZE_VERTICAL 13

enum class GameplayState { GAME_START, RUNNING, PAUSED, GAME_OVER };

class Gameplay : public Scene
{
private:
    GameplayState internalState;

    // UI
    std::unordered_map<std::string, Button*> buttons;
    HUD hud;

    // Gameplay
    Player playerOne, playerTwo;
    std::vector<Wall*> map;

    int livesPlayerOne, livesPlayerTwo;

    myType::Rect playerOnePosition, playerTwoPosition;
    myType::Rect defaultWallSprite, destructibleWallSprite, toDestroyWallSprite;

    // Time
    float gameTime;
    clock_t lastTime;
    float deltaTime;

    std::vector<Bomb> bombs;
    std::vector<PowerUp*> powerUps;

    void LoadLevelData(std::string level);
    void StartTime();
    void UpdateTime();
    void ClearExplodedBombs();
    void BombCollision();
    void DropPowerUp(myType::Rect startPosition);
    void PowerUpsCollision();
public:
    Gameplay();
    Gameplay(std::string level);
    ~Gameplay();

    void Update(InputManager inputmanager);
    void Draw();
};

