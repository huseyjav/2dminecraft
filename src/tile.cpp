#include "tile.h"
#include "constids.h"
#include "renderer.h"
#include "world.h"
#include "pickable.h"
using namespace std;


CTile::CTile(tileID type,int x, int y,CWorld* world):type(type),x(x),y(y),world(world){

}
void CTile::render(CCameraRenderer * renderer){
    SDL_Rect rect;

    //vector2 screenpos;
    
    vector2 screenpos = renderer->worldtoscreen(vector2{x,y});

    rect.x = screenpos.x;
    rect.y = 1000-screenpos.y-100;
    rect.w = 100;
    rect.h = 100;
    // if(type==VOID){
    //     //SDL_SetRenderDrawColor(renderer, 0, 177, 224, 255);
    //     //SDL_RenderFillRect(renderer,&rect);
    // }
    if(type==tileID::grass_id){
        
        SDL_RenderCopy(renderer->renderer,renderer->assets->grassblock,nullptr,&rect);

        SDL_SetRenderDrawBlendMode(renderer->renderer,SDL_BLENDMODE_BLEND);

        //cout << health << endl;
        SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, ((100-health)*255)/100);
        SDL_RenderFillRect(renderer->renderer,&rect);

        SDL_SetRenderDrawBlendMode(renderer->renderer,SDL_BLENDMODE_NONE);
    }
    
}

bool CTile::isCollidable(){
    return type!=tileID::void_id;
}


void CTile::setblocktype(tileID type){
    this->type=type;
    switch(type){
        case tileID::grass_id:
            maxhealth=100;
            health=100;
            break;
    }
}