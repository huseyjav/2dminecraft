#pragma once

#include <vector>
#include "SDL2/SDL.h"

#include "utils.h"

#include "tile.h"
#include "renderable.h"
#include "entity.h"
//#include "player.h"
using namespace std;


class CEntity;
class CTile;


class CWorld : public CRenderable{
public:
    vector<vector<CTile>> tiles;
    float gravity;
    CEntity* player;

    CWorld(int w, int h);
    void setplayer(CEntity* pl);
    void render(CCameraRenderer * renderer) override;
    void update();
    vector2 genSpawnpoint();
    void handleInput(CCameraRenderer * camrenderer);

    bool lastframekleftclick = false;
    int tickoflastclick = 0;
    int lastclickedtilex=0;
    int lastclickedtiley=0;



};

