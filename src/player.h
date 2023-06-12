#pragma once


#include "world.h"
#include "renderable.h"
#include "physics.h"
#include "entity.h"
#include "aliveent.h"
#include "melee.h"
#include "helperstructs.h"
class CWorld;

class CPlayer : public CEntity, public CAlive{
public:
    // implement inventory
    
    //int health=20;
    int respawnx=600;
    int respawny=600;

    int activeitem=0;

    vector<CItem*> hotbar;

    void update() override; // override update to decrease health on fall etc
    virtual void render(CCameraRenderer* camrenderer);
    CPlayer(int x, int y, int w, int h, int velocityX ,CWorld* world);
    CPlayer(playerread& oldstate,CWorld* world);
    /**
     * @brief returns struct used for saving game state and load for constructor
     * 
     * @return playerread 
     */
    playerread getplayerread();

    void useactiveitem(vector2 worldpos);
    void respawn();
    void setactiveitem(int slot);
    int stackitem(itemID id,int count);
    virtual ~CPlayer();
};