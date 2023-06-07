#include "assets.h"
#include <iostream>
using namespace std;

CAssets::CAssets(CCameraRenderer* renderer){
    grassblock = IMG_LoadTexture(renderer->renderer,"src/resources/Green_Brick.png");
    player_sprite = IMG_LoadTexture(renderer->renderer,"src/resources/anim-sheet.png");
    cout << grassblock << endl;
}