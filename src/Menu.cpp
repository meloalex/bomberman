#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{
}

void Menu::Update(InputManager inputmanager)
{
}

void Menu::Draw()
{
	Renderer::Instance()->Clear();

	Renderer::Instance()->Render();
}
