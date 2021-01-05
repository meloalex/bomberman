#include "Ranking.h"

Ranking::Ranking()
{
}

Ranking::~Ranking()
{
}

void Ranking::Update(InputManager inputmanager)
{
}

void Ranking::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->Render();
}
