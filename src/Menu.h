#pragma once
#include "Scene.h"

class Menu : public Scene
{
public:
    Menu();
    ~Menu();

    void Update(InputManager inputmanager);
    void Draw();
};

