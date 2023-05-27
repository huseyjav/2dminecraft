#include "hud.h"

CHud::CHud(CPlayer* localplayer) : localplayer(localplayer){
    
}


void CHud::render(CCameraRenderer* camrenderer){
    SDL_Rect rect;
    rect.x=10;
    rect.y=10;

    rect.h =20;
    rect.w = localplayer->health;

    SDL_SetRenderDrawColor(camrenderer->renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(camrenderer->renderer,&rect);
}