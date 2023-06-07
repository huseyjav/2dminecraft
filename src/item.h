#pragma once
// #include "world.h"
// #include "entity.h"
#include "utils.h"
class CWorld;
class CEntity;
class CItem {
public:
    int itemID;
    int lastusedtick;
    CEntity* owner;
    CItem(int itemID, CEntity* owner);
    virtual void use(CWorld* world, vector2 clickpos)=0;
    //virtual CEntity* spawnentity()=0;
    virtual ~CItem() = default;
};
