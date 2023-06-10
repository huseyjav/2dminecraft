#include "pickable.h"
#include "world.h"
#include "player.h"

CPickable::CPickable(entityID id,int x, int y, int w, int h,int velocityX,CWorld* world,int stackcount):CEntity(id,x,y,w,h,velocityX,world),stackcount(stackcount){

}


void CPickable::update(){

    SDL_Rect a;
    a.x=x;
    a.y=y;
    a.h=h;
    a.w=w;

    SDL_Rect b;
    b.x = world->player->x;
    b.y = world->player->y;
    b.w = world->player->w;
    b.h = world->player->h;

    if(SDL_HasIntersection(&a,&b)){
        stackcount-=world->player->stackitem(getitemID(id),stackcount);
        if(stackcount<=0) shouldberemoved=true;
    }
    CEntity::update();    
}


void CPickable::render(CCameraRenderer * renderer){

    vector2 screenpos = renderer->worldtoscreen(vector2{x,y});

    SDL_Rect a;
    a.x=screenpos.x;
    a.y=1000-screenpos.y-h;
    a.h=h;
    a.w=w;



    SDL_RenderCopy(renderer->renderer,getentTexture(this,renderer->assets),nullptr,&a);
}



SDL_Texture* getentTexture(CEntity* ent,CAssets* assets){
    if(!ent) return nullptr;
    switch(ent->id){
        case(entityID::dropped_sword_id):
            return assets->sword;
        case(entityID::dropped_pickaxe_id):
            return nullptr;
        case(entityID::dropped_meat_id):
            return nullptr;
        case(entityID::dropped_grassblock_id):
            return assets->grassblock;
    }
}




/*

enum entityID{
    localplayer_id,
    zombiewithsword_id,
    dropped_sword_id,
    dropped_pickaxe_id,
    dropped_meat_id,
    dropped_grassblock_id
};

*/