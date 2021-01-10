#pragma once
#include "Renderer.h"
#include "Types.h"
#include "Player.h"

#define POWER_UP_TIME_EFFECT 10

class PowerUp
{
protected:
	// Draw
	std::string texture;
	myType::Rect sprite;

	myType::Rect position;

	// Time
	float timer;

	
	Player* player;
	
public:
	PowerUp();
	PowerUp(myType::Rect _position);
	~PowerUp();
	bool activated;
	bool stopPls;
	virtual void Update(float dTime) = 0;
	virtual void Draw() = 0;

	myType::Rect GetPosition();

	virtual void Start(Player* _player) = 0;
	virtual void Stop() = 0;
};

