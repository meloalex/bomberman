#pragma once
#include <time.h>
#include <math.h>
#include <iostream>

#include "Renderer.h"
#include "Types.h"
#include "Wall.h"
#include "Bomb.h"

#define ANIMATION_TIME 0.3
#define MOVEMENT_ANIMATION_KEYFRAMES 2
#define DIE_ANIMATION_OFFSET 4
#define PLAYER_HITBOX_CORRECTION 6

enum class Animation { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

class Player
{
private:
	
	std::vector<Wall*>* map;

	// Animation
	Animation currentAnimation, lastAnimation;
	int keyFrame;
	std::string texture;
	myType::Rect position;
	myType::Rect spritePosition;
	bool breakAnimation;

	// Time
	float timer;
	clock_t lastTime;
	float deltaTime;

	// Bomb
	std::vector<Bomb>* gameBombs;

	bool Collision(myType::Rect futurePosition);
	void Animate();
	void Move(bool _up, bool _down, bool _left, bool _right);
	void PlaceBomb();

public:
	int score;
	int lives;
	bool hasBombPlaced;
	float speed;
	bool hasShield;

	Player();
	Player(myType::Rect pos, std::vector<Wall*>* _map, std::string _texture, std::vector<Bomb>* _bombs);
	~Player();

	void Update(bool _up, bool _down, bool _left, bool _right, bool _bombKey);
	void Draw();

	myType::Rect GetPosition();
};

