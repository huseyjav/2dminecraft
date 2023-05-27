#pragma once


#include "world.h"
#include "renderable.h"
#include "physics.h"
#include "entity.h"
//#include "aliveent.h"

class CWorld;

class CPlayer : public CEntity {
public:
    // implement inventory
    bool alive=true;
    int health=20;
    int respawnx=600;
    int respawny=600;




    void update() override; // override update to decrease health on fall etc
    virtual void render(CCameraRenderer* camrenderer);
    CPlayer(int x, int y, int w, int h, CWorld* world);
    void respawn();
};