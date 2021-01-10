#pragma once
#include "Types.h"

struct Wall
{
	myType::Rect position; // World Position
	bool destructable;
	int state;

	Wall()
	{
		position = myType::Rect(0, 0, 0, 0);
		destructable = false;
		state = -1;
	}

	Wall(myType::Rect _position, bool _destructable)
	{
		position = _position;
		destructable = _destructable;

		if (_destructable)
			state = 2;
		else
			state = -1;
	}
};