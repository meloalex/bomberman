#include "Gameplay.h"

Gameplay::Gameplay()
{
}

Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputManager inputmanager)
{
}

void Gameplay::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->Render();
}
