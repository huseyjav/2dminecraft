#include "tile.h"

#include <iostream>

using namespace std;

CTile::CTile(int type, int x, int y): type(type),x(x),y(y){
    //health = 100;
}

void CTile::render(CCameraRenderer * renderer){
    SDL_Rect rect;

    //vector2 screenpos;
    
    vector2 screenpos = renderer->worldtoscreen(vector2{x,y});

    rect.x = screenpos.x;
    rect.y = 1000-screenpos.y-100;
    rect.w = 100;
    rect.h = 100;
    if(type==VOID){
        //SDL_SetRenderDrawColor(renderer, 0, 177, 224, 255);
        //SDL_RenderFillRect(renderer,&rect);
    }
    if(type==GRASS){
        
        // SDL_SetRenderDrawColor(renderer->renderer, 0, 177, 0, 255);
        // SDL_RenderFillRect(renderer->renderer,&rect);
        // SDL_SetRenderDrawColor(renderer->renderer, 0, 255, 0, 255);
        // SDL_RenderDrawRect(renderer->renderer,&rect);
        SDL_RenderCopy(renderer->renderer,renderer->assets->grassblock,nullptr,&rect);

        SDL_SetRenderDrawBlendMode(renderer->renderer,SDL_BLENDMODE_BLEND);

        //cout << health << endl;
        SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, ((100-health)*255)/100   );
        SDL_RenderFillRect(renderer->renderer,&rect);

        SDL_SetRenderDrawBlendMode(renderer->renderer,SDL_BLENDMODE_NONE);
    }
    
}

bool CTile::isCollidable(){
    return type==GRASS;
}