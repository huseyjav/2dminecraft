#pragma once
// #include "world.h"
// #include "entity.h"
#include "utils.h"
#include "constids.h"
#include "assets.h"
class CWorld;
class CEntity;
class CItem {
public:
    int stackcount;
    itemID id;
    int lastusedtick;
    CEntity* owner;
    CItem(itemID id, CEntity* owner,int stackcount);
    virtual void use(CWorld* world, vector2 clickpos)=0;
    //virtual CEntity* spawnentity()=0;
    virtual ~CItem() = default;
};





SDL_Texture* getTexture(itemID id,CAssets* assets);