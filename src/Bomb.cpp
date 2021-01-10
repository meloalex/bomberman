#include "Bomb.h"

Bomb::Bomb()
{
}

Bomb::Bomb(myType::Vector2 startPosition, std::string _propietary)
{
	propietary = _propietary;
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
	hasAlreadyExploded = false;

	// Setup explosion positions
	explosionsPositions[0] = myType::Rect(startPosition.x - 2 * SPRITESHEET_RECT_SIZE, startPosition.y, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[1] = myType::Rect(startPosition.x + 2 * SPRITESHEET_RECT_SIZE, startPosition.y, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[2] = myType::Rect(startPosition.x, startPosition.y - 2 * SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[3] = myType::Rect(startPosition.x, startPosition.y + 2 * SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[4] = myType::Rect(startPosition.x - 1 * SPRITESHEET_RECT_SIZE, startPosition.y, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[5] = myType::Rect(startPosition.x + 1 * SPRITESHEET_RECT_SIZE, startPosition.y, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[6] = myType::Rect(startPosition.x, startPosition.y - 1 * SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
	explosionsPositions[7] = myType::Rect(startPosition.x, startPosition.y + 1 * SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
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

	if (state == BombState::EXPLODING)
	{
		for (int i = 0; i < 8; i++)
		{
			Renderer::Instance()->PushSprite(explosionTexture, explosionsSprites[i],explosionsPositions[i]);
		}
	}
}

void Bomb::GoKaboom()
{
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
		
		sprite = myType::Rect(SPRITESHEET_RECT_SIZE * frame, 0, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);

		for (int i = 0; i < 4; i++)
			explosionsSprites[i] = myType::Rect(SPRITESHEET_RECT_SIZE * frame, SPRITESHEET_RECT_SIZE * (i + 1), SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
		
		explosionsSprites[4] = myType::Rect(SPRITESHEET_RECT_SIZE * frame, SPRITESHEET_RECT_SIZE * 5, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
		explosionsSprites[5] = myType::Rect(SPRITESHEET_RECT_SIZE * frame, SPRITESHEET_RECT_SIZE * 5, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
		explosionsSprites[6] = myType::Rect(SPRITESHEET_RECT_SIZE * frame, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
		explosionsSprites[7] = myType::Rect(SPRITESHEET_RECT_SIZE * frame, SPRITESHEET_RECT_SIZE * 6, SPRITESHEET_RECT_SIZE, SPRITESHEET_RECT_SIZE);
				
		reverse ? frame-- : frame++;

		if (frame == 3)
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

myType::Rect Bomb::GetPosition() {
	return position;
}