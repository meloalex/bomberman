#pragma once
#include "PowerUp.h"

class Rollers :
    public PowerUp
{
private:

public:
    Rollers(myType::Rect _position);
    ~Rollers();

    void Draw();
    void Update(float dTime);

    void Start(Player* _player);
    void Stop();
};