#pragma once
#include "item.h"
#include "SDL2/SDL.h"


class CMelee : public CItem{
public:
    int damage;
    unsigned int attackcooldown;
    uint lastused=0;
    CMelee(itemID id,CEntity* owner,int attackcooldown,int damage);
    void use(CWorld* world,vector2 clickpos) override;
    virtual ~CMelee() = default;
};