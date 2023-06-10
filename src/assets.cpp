#include "assets.h"
#include <iostream>
#include "renderer.h"
using namespace std;

CAssets::CAssets(CCameraRenderer* renderer){
    grassblock = IMG_LoadTexture(renderer->renderer,"src/resources/Green_Brick.png");
    player_sprite = IMG_LoadTexture(renderer->renderer,"src/resources/anim-sheet.png");
    fist = IMG_LoadTexture(renderer->renderer,"src/resources/fist1.png");
    sword = IMG_LoadTexture(renderer->renderer,"src/resources/sword.png");
    cout << fist << endl;
}