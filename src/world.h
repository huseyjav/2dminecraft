#pragma once

#include <vector>
#include "SDL2/SDL.h"

#include "utils.h"

#include "tile.h"
#include "renderable.h"
#include "entity.h"
#include "melee.h"
#include "npc.h"
//#include "player.h"
using namespace std;


class CEntity;
class CTile;
class CPlayer;

class CWorld : public CRenderable{
public:
    vector<vector<CTile>> tiles;
    float gravity;
    CPlayer* player;
    vector<CNpc*> worldnpcs;
    vector<CEntity*> entities;
    CWorld(int w, int h);
    CWorld(ifstream& is);
    virtual ~CWorld();
    void setplayer(CPlayer* pl);
    void render(CCameraRenderer * renderer) override;
    void update();
    vector2 genSpawnpoint(int h, int w,CPhyiscs* checker);
    //void handleInput(CCameraRenderer * camrenderer);
    /**
     * @brief handles a melee attack
     * 
     * @param item melee used to attack
     * @param owner attacker entity
     * @param worldpoint where the attack was at relative to world
     */
    void handleAttack(CItem* item, CEntity* owner, vector2 worldpoint);
    /**
     * @brief returns whether some entity is on a void block or not 
     * 
     * @param x index of the block on x axis
     * @param y index of the block on y axis
     * @return true 
     * @return false 
     */
    bool isempty(int x, int y);
    /**
     * @brief checks if given x,y is without bounds of the current map
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool iswithinlimitsofmap(int x, int y);
    bool isvalidlocation(int x, int y, int w, int h,CPhyiscs* checker);
    bool placeblock(tileID toplace,vector2 worldpoint);
    



};

