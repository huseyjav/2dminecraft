#pragma once


#include "entity.h"
#include "aliveent.h"

//class CCameraRenderer;

class CNpc : public CEntity , public CAlive{
public:
    CEntity* target;
    int oldx=0;
    int oldy=0;
    bool targetwithinproximinity();
    CNpc(int x, int y, int w, int h, int velocityX,CWorld* world, CEntity* target);
    
    virtual void render(CCameraRenderer * renderer) override;
    virtual void update() override;
    virtual ~CNpc() = default;
};