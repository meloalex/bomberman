#pragma once
#include "Scene.h"
#include <unordered_map>
#include "Button.h"

class Menu : public Scene
{
private:
    std::unordered_map<std::string, Button*> buttons;
    bool soundOn;

public:
    Menu();
    ~Menu();

    void Update(InputManager inputmanager);
    void Draw();
};

