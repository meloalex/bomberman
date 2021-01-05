#pragma once
#include "Scene.h"

class Gameplay : public Scene
{
public:
    Gameplay();
    ~Gameplay();

    void Update(InputManager inputmanager);
    void Draw();
};

