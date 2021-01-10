#include "Rollers.h"

Rollers::Rollers(myType::Rect _position) : PowerUp(_position)
{
	texture = "items";
	sprite = myType::Rect(SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
}

Rollers::~Rollers()
{
}

void Rollers::Draw()
{
	if (!activated)
	{
		Renderer::Instance()->PushSprite(texture, sprite, position);
	}
}

void Rollers::Update(float dTime)
{
	// Time Management
	timer -= dTime;

	if (timer < 0.0f && activated && !stopPls) Stop();
}

void Rollers::Start(Player* _player)
{
	std::cout << "power up start \n";
	player = _player;
	_player->speed *= 1.8f;
	timer = POWER_UP_TIME_EFFECT;
	activated = true;
}

void Rollers::Stop()
{
	std::cout << "power up stop \n";
	player->speed /= 1.8f;
	timer = 100000000000;
	stopPls = true;
}

