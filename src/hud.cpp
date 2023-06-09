#include "hud.h"

CHud::CHud(CPlayer* localplayer) : localplayer(localplayer){
    
}


void CHud::render(CCameraRenderer* camrenderer){
    renderhealth(camrenderer);
    renderhotbar(camrenderer);
}

void CHud::renderhealth(CCameraRenderer* camrenderer){
    SDL_Rect rect;
    rect.x=10;
    rect.y=10;

    rect.h =20;
    rect.w = localplayer->health;

    SDL_SetRenderDrawColor(camrenderer->renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(camrenderer->renderer,&rect);
}


void CHud::renderhotbar(CCameraRenderer* camrenderer){
    int screendimx;
    int screendimy;
    SDL_GetWindowSize(camrenderer->window,&screendimx,&screendimy);
    for(size_t i = 0 ; i<localplayer->hotbar.size();i++){
        SDL_Rect rect;
        rect.w = 75;
        rect.h = 75;
        rect.y = int(screendimy*0.9);
        rect.x = int((screendimx-localplayer->hotbar.size()*75)/2+i*75);
        SDL_SetRenderDrawColor(camrenderer->renderer, 255, 255, 255, 0);
        if(localplayer->activeitem==i){
            SDL_SetRenderDrawColor(camrenderer->renderer, 255, 0, 0, 0);
        }
        SDL_RenderDrawRect(camrenderer->renderer,&rect);

        rect.w = 70;
        rect.h = 70;

        rect.y+=2;
        rect.x+=2;
        
        SDL_RenderCopy(camrenderer->renderer,localplayer->hotbar[i] ? getTexture(localplayer->hotbar[i]->id,camrenderer->assets) : nullptr,nullptr,&rect);

    }
}

CHud::~CHud(){
    
}