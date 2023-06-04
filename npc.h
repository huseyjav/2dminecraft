#pragma once


#include "entity.h"
#include "aliveent.h"

//class CCameraRenderer;

class CNpc : public CEntity , public CAlive{
public:
    CEntity* target;
    int oldx;
    int oldy;
    bool targetwithinproximinity();
    CNpc(int x, int y, int w, int h, int velocityX,CWorld* world, CEntity* target);
    
    virtual void render(CCameraRenderer * renderer) override;
    virtual void update() override;

};