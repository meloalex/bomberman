#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::Bomb(myType::Vector2 startPosition)
{
	explosionTexture = "explosion";
	explosionSprite = myType::Rect(0, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	bombTexture = "items";
	bombSpriteRect = myType::Rect(0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	position = myType::Rect(startPosition, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

	kaboomTimer = KABOOM_TIME;
	explosionTimer = 0.0f;

	texture = bombTexture;
	sprite = bombSpriteRect;
	frame = 0;
	state = BombState::PLACED;
	reverse = false;
}

Bomb::~Bomb()
{
}

void Bomb::Update(float dTime)
{
	kaboomTimer -= dTime;

	if (kaboomTimer < 0.0f)
		GoKaboom();
}

void Bomb::Draw()
{
	Renderer::Instance()->PushSprite(texture, sprite, position);
}

void Bomb::GoKaboom()
{
	//std::cout << "KABOOOM !" << std::endl;
	state = BombState::EXPLODING;

	texture = explosionTexture; // TODO textures must be macros
	
	// Play animation
	// Time Management
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	explosionTimer -= deltaTime;

	if (explosionTimer < 0.0f)
	{
		explosionTimer = EXPLOSION_ANIMATION_TIME;
		deltaTime = 0;
		lastTime = clock();
		
		std::cout << "Frame: " << frame << std::endl;
		sprite = myType::Rect(SPRITESHEET_RECT_SIZE * frame, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
		reverse ? frame-- : frame++;

		if (frame == 4)
		{
			reverse = true;
		}
		if (reverse && frame < 0)
		{
			state = BombState::GONE;
			kaboomTimer = KABOOM_TIME;
		}
	}
}