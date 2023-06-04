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
    CWorld(int w, int h);
    ~CWorld();
    void setplayer(CPlayer* pl);
    void render(CCameraRenderer * renderer) override;
    void update();
    vector2 genSpawnpoint();
    void handleInput(CCameraRenderer * camrenderer);

    /**
     * @brief handles a melee attack
     * 
     * @param item melee used to attack
     * @param owner attacker entity
     * @param worldpoint where the attack was at relative to world
     */
    void handleAttack(CItem* item, CEntity* owner, vector2 worldpoint);
    bool lastframekleftclick = false;
    int tickoflastclick = 0;
    int lastclickedtilex=0;
    int lastclickedtiley=0;



};

