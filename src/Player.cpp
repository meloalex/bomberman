#include "Player.h"

Player::Player()
{

}

Player::Player(myType::Rect pos, std::vector<Wall*>* _map, std::string _texture, std::vector<Bomb>* _bombs)
{
	texture = _texture;
	map = _map;
	hasBombPlaced = false;

	position = pos;

	gameBombs = _bombs;

	// Time
	timer = ANIMATION_TIME;
	deltaTime = 0;
	lastTime = clock();

	// Animation
	keyFrame = 0;
	currentAnimation = Animation::MOVE_UP;
	breakAnimation = false;
	spritePosition = myType::Rect(0, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	speed = 1;
	score = 0;
	lives = 3;
	hasShield = false;
}

Player::~Player()
{

}

void Player::Update(bool _up, bool _down, bool _left, bool _right, bool _bombKey)
{
	Move(_up, _down, _left, _right);
	Animate();
	
	if (_bombKey) PlaceBomb();
}

void Player::Draw()
{
	Renderer::Instance()->PushSprite(texture, spritePosition, position);
}

void Player::Move(bool _up, bool _down, bool _left, bool _right) 
{
	myType::Vector2 direction;
	myType::Rect futurePosition = position;

	if (_up)
	{
		breakAnimation = lastAnimation != Animation::MOVE_UP;

		direction = myType::Vector2(0, -1);
		currentAnimation = Animation::MOVE_UP;
	}
	else if (_down)
	{
		breakAnimation = lastAnimation != Animation::MOVE_DOWN;

		direction = myType::Vector2(0, 1);
		currentAnimation = Animation::MOVE_DOWN;
	}
	else if (_left)
	{
		breakAnimation = lastAnimation != Animation::MOVE_LEFT;

		direction = myType::Vector2(-1, 0);
		currentAnimation = Animation::MOVE_LEFT;
	}
	else if (_right)
	{
		breakAnimation = lastAnimation != Animation::MOVE_RIGHT;

		direction = myType::Vector2(1, 0);
		currentAnimation = Animation::MOVE_RIGHT;
	}

	// Compute next position
	futurePosition.position.x += direction.x * speed;
	futurePosition.position.y += direction.y * speed;

	if (Collision(futurePosition)) return;
	
	// Update last animation
	lastAnimation = currentAnimation;

	// Apply movement
	position = futurePosition;
}

void Player::Animate()
{
	// Time Management
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	timer -= deltaTime;

	if (timer < 0.0 || breakAnimation)
	{
		timer = ANIMATION_TIME;
		deltaTime = 0;
		lastTime = clock();

		if (breakAnimation) keyFrame = 0;	// Start animation

		switch (currentAnimation)
		{
		case Animation::MOVE_UP:
			spritePosition.position.x = keyFrame * SPRITESHEET_RECT_SIZE;
			spritePosition.position.y = 0;
			break;

		case Animation::MOVE_DOWN:
			spritePosition.position.x = keyFrame * SPRITESHEET_RECT_SIZE;
			spritePosition.position.y = SPRITESHEET_RECT_SIZE * 2;
			break;

		case Animation::MOVE_LEFT:
			spritePosition.position.x = keyFrame * SPRITESHEET_RECT_SIZE;
			spritePosition.position.y = SPRITESHEET_RECT_SIZE;
			break;

		case Animation::MOVE_RIGHT:
			spritePosition.position.x = keyFrame * SPRITESHEET_RECT_SIZE;
			spritePosition.position.y = SPRITESHEET_RECT_SIZE * 3;
			break;
		}

		keyFrame++;
		if (keyFrame > 2) keyFrame = 0;
	}
}

void Player::PlaceBomb()
{
	if (!hasBombPlaced)
	{
		Bomb bomb = Bomb(position.position, texture);
		gameBombs->push_back(bomb);
		hasBombPlaced = true;
	}
}

bool Player::Collision(myType::Rect futurePosition)
{
	myType::Rect correctedRect = futurePosition;
	correctedRect.position.x += PLAYER_HITBOX_CORRECTION;
	correctedRect.position.y += PLAYER_HITBOX_CORRECTION;
	correctedRect.w -= PLAYER_HITBOX_CORRECTION * 2;
	correctedRect.h -= PLAYER_HITBOX_CORRECTION * 2;

	// Collision with Walls
	for (auto it = map->begin(); it != map->end(); ++it)
	{
		Wall* wall = *it;
		myType::Rect rect = wall->position;

		if (myType::RectRectCollision(correctedRect, rect))
			return true;
	}

	// World Collision
	if (futurePosition.position.x < SPRITESHEET_RECT_SIZE || futurePosition.position.x > SCREEN_WIDTH - SPRITESHEET_RECT_SIZE * 2)
	{
		return true;
	}

	if (futurePosition.position.y < HUD_HEIGHT + SPRITESHEET_RECT_SIZE || futurePosition.position.y > SCREEN_HEIGHT - SPRITESHEET_RECT_SIZE * 2)
	{
		return true;
	}

	return false;
}

myType::Rect Player::GetPosition()
{
	return position;
}