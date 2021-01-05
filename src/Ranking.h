#pragma once
#include "Scene.h"

class Ranking : public Scene
{
public:
    Ranking();
    ~Ranking();

    void Update(InputManager inputmanager);
    void Draw();
};

