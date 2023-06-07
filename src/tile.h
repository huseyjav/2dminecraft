#pragma once


#include "SDL2/SDL.h"
#include "utils.h"
#include "renderer.h"
#include "renderable.h"
#define GRASS 1
#define VOID 0

class CCameraRenderer;

class CTile : public CRenderable{ // placeholder class for testing purposes
public:
    int type;
    int x,y;
    int health=100;
    int maxhealth=100;
    CTile(int type,int x, int y);
    void render(CCameraRenderer * renderer) override;
    bool isCollidable();
};