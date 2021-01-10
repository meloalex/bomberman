#include "PowerUp.h"

PowerUp::PowerUp()
{
	
}

PowerUp::PowerUp(myType::Rect _position)
{
	position = _position;
	player = nullptr;
	activated = false;
	stopPls = false;
}

PowerUp::~PowerUp()
{
}

myType::Rect PowerUp::GetPosition()
{
	return position;
}