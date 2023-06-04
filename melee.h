#pragma once
#include "item.h"
#include "SDL2/SDL.h"


class CMelee : public CItem{
public:
    int damage;
    int attackcooldown;
    uint lastused;
    CMelee(int itemID,CEntity* owner,int attackcooldown,int damage);
    void use(CWorld* world,vector2 clickpos) override;
};