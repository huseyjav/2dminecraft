#pragma once


#include "SDL2/SDL.h"
#include "utils.h"
#include "renderable.h"
#include "assets.h"
#include "constids.h"
// #define GRASS 1
// #define VOID 0

class CCameraRenderer;
class CWorld;


class CTile : public CRenderable{ // placeholder class for testing purposes
public:
    //CAssets* assets;
    //int type;
    tileID type;
    int x,y;
    int health=100;
    int maxhealth=100;
    CWorld* world;
    void setblocktype(tileID type);
    CTile(tileID type,int x, int y,CWorld* world);
    void render(CCameraRenderer * renderer) override;
    bool isCollidable();
};