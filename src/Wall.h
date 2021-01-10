#pragma once
#include "Types.h"
#include "Renderer.h"

class Wall
{
private:
	std::string texture;
	myType::Rect sprite;

public:
	myType::Rect position; // World Position
	bool isDestructable;
	int state;

	Wall();
	Wall(myType::Rect _position, bool _destructable);

	void Update();
	void Draw();
	void TakeDamage();
};