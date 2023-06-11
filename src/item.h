#pragma once
// #include "world.h"
// #include "entity.h"
#include "utils.h"
#include "constids.h"
#include "assets.h"
#include "helperstructs.h"
#include <fstream>
using namespace std;
class CWorld;
class CEntity;
class CItem {
public:
    
    itemID id;
    int lastusedtick;
    CEntity* owner;
    int currentcount=1;
    int maxcount;
    CItem(itemID id, CEntity* owner,int stackcount1);
    CItem(itemread read);
    virtual void use(CWorld* world, vector2 clickpos)=0;
    itemread getitemread();
    virtual void savetofile(ostream & os);
    //virtual CEntity* spawnentity()=0;
    virtual ~CItem() = default;
};





SDL_Texture* getTexture(itemID id,CAssets* assets);