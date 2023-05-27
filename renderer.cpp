#include "renderer.h"
#include "world.h"


CCameraRenderer::CCameraRenderer(SDL_Window* window,SDL_Renderer* renderer,CWorld* world): window(window),renderer(renderer),world(world){

}

void CCameraRenderer::centerTo(int x, int y){
    centerX = x;
    centerY = y;
}

vector2 CCameraRenderer::worldtoscreen(vector2 worldpos){
    vector2 toret;
    int screendimx;
    int screendimy;
    SDL_GetWindowSize(window,&screendimx,&screendimy);
    toret.x = worldpos.x - (centerX-screendimx/2);
    toret.y = worldpos.y - (centerY-screendimy/2);
    return toret;
}


vector2 CCameraRenderer::screentoworld(vector2 screenpos){
    vector2 toret;
    int screendimx;
    int screendimy;
    SDL_GetWindowSize(window,&screendimx,&screendimy);
    screenpos.y = 1000-screenpos.y;
    toret.x = screenpos.x + (centerX-screendimx/2);
    toret.y = screenpos.y + (centerY-screendimy/2);
    return toret;
}