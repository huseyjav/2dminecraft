#pragma once


#include "world.h"
#include "renderable.h"
#include "physics.h"
#include "entity.h"
#include "aliveent.h"
#include "melee.h"
class CWorld;

class CPlayer : public CEntity, public CAlive{
public:
    // implement inventory
    
    //int health=20;
    int respawnx=600;
    int respawny=600;

    CItem* activeitem;


    void update() override; // override update to decrease health on fall etc
    virtual void render(CCameraRenderer* camrenderer);
    CPlayer(int x, int y, int w, int h, int velocityX ,CWorld* world);
    void useactiveitem(vector2 worldpos);
    void respawn();
    virtual ~CPlayer();
};