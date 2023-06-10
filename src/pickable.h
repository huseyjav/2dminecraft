#pragma once
#include "entity.h"



class CPickable : public CEntity{
public:

    int stackcount;
    CPickable(entityID id,int x, int y, int w, int h,int velocityX,CWorld* world,int stackcount);
    virtual void update() override;
    virtual void render(CCameraRenderer * renderer) override;
};





SDL_Texture* getentTexture(CEntity* ent,CAssets* assets);