#include "Shield.h"

Shield::Shield(myType::Rect _position) : PowerUp(_position)
{
	texture = "items";
	sprite = myType::Rect(SPRITESHEET_RECT_SIZE * 2, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
}

Shield::~Shield()
{
}

void Shield::Draw()
{
	if (!activated)
	{
		Renderer::Instance()->PushSprite(texture, sprite, position);
	}
}

void Shield::Update(float dTime)
{
	// Time Management
	timer -= dTime;

	if (timer < 0.0f && activated && !stopPls) Stop();
}

void Shield::Start(Player* _player)
{
	std::cout << "power up start \n";
	player = _player;
	_player->hasShield = true;
	timer = POWER_UP_TIME_EFFECT;
	activated = true;
}

void Shield::Stop()
{
	std::cout << "power up stop \n";
	player->hasShield = false;
	timer = 100000000000;
	stopPls = true;
}
