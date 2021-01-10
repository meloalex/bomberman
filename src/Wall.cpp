#include "Wall.h"

Wall::Wall()
{
	position = myType::Rect(0, 0, 0, 0);
	isDestructable = false;
	state = -1;
}

Wall::Wall(myType::Rect _position, bool _destructable)
{
	position = _position;
	isDestructable = _destructable;
	texture = "items";

	if (_destructable)
	{
		state = 2;
		sprite = myType::Rect(SPRITESHEET_RECT_SIZE, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	}
	else
	{
		state = -1;
		sprite = myType::Rect(0, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	}
		
}

void Wall::Update()
{

}

void Wall::Draw()
{
	Renderer::Instance()->PushSprite(texture, sprite, position);
}

void Wall::TakeDamage()
{
	state--;

	if (state == 1)
	{
		sprite = myType::Rect(SPRITESHEET_RECT_SIZE * 2, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	}
}