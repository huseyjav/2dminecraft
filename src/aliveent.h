#pragma once

#include "helperstructs.h"


class CAlive{
public:
    int health=100;
    int armor;
    bool alive=true;
    bool hurtanim=false;
    void hurt(int damage);
    CAlive()=default;
    CAlive(aliveread& a);

    aliveread getaliveread();
};