#pragma once
#include "PowerUp.h"
class Shield :
    public PowerUp
{
public:
    Shield(myType::Rect _position);
    ~Shield();

    void Draw();
    void Update(float dTime);

    void Start(Player* _player);
    void Stop();
};

