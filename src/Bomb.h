#pragma once
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <vector>

#include "Renderer.h"
#include "Types.h"

#define BOMB_ANIMATION_TIME 0.1
#define KABOOM_TIME 3
#define EXPLOSION_ANIMATION_TIME 0.3

enum class BombState { PLACED, EXPLODING, GONE };

class Bomb
{
private:
	// Draw
	std::string texture;
	myType::Rect sprite;

	std::string bombTexture;
	myType::Rect bombSpriteRect;

	// Animation
	int frame;
	std::string explosionTexture;
	myType::Rect explosionSprite;

	// Time
	float kaboomTimer;
	float deltaTime;
	clock_t lastTime;
	float explosionTimer;

	myType::Rect position;
	bool isExploding;
	bool reverse;
	
	myType::Rect explosionsSprites[8];
	
	void GoKaboom();
public:
	Bomb();
	Bomb(myType::Vector2 startPosition, std::string _propietary);
	~Bomb();

	std::string propietary;
	myType::Rect explosionsPositions[8];
	BombState state;
	bool hasAlreadyExploded;

	void Update(float dTime);
	void Draw();

	myType::Rect GetPosition();
};