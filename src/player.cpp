#include "player.h"
#include "world.h"
#include "entity.h"

#include <iostream>

using namespace std;

CPlayer::CPlayer(int x, int y, int w, int h, int velocityX,CWorld* world): CEntity(x,y,w,h,velocityX,world),activeitem (new CMelee(1,this,200,20)){
    
    
}




void CPlayer::update(){
    setonGround();
    //cout << "a" << endl;
    //if(isValidcoordinate(200,496)) std::cout << " as " << std::endl;
    int temp = handleFreefall();
    if(jumping){
        stepajump();
    }
    if(temp>300){
        //health-=10;
        hurt(20);
    }
    if(oldx > x){
        isorientationleft=true;
    }
    else if(oldx < x) isorientationleft=false;
    oldx = x;
    oldy = y;
    //if(health<=0) alive=false;
    
}


void CPlayer::respawn(){
    x=respawnx;
    y=respawny;
    health=100;
    alive=true;
}

void CPlayer::render(CCameraRenderer* camrenderer){
    if(alive){
        //CEntity::render(camrenderer);
        vector2 screenpos = camrenderer->worldtoscreen(vector2{x,y});


        SDL_Rect rect;
        rect.x = screenpos.x;
        rect.y = 1000-screenpos.y-h;
        rect.w = w;
        rect.h = h;
        SDL_Rect spritesheet;
        spritesheet.x = 24;
        spritesheet.y = 0;
        spritesheet.w = 16;
        spritesheet.h = 64;
        //SDL_RenderCopy(camrenderer->renderer,camrenderer->assets->player_sprite,&spritesheet,&rect);
        SDL_RenderCopyEx(camrenderer->renderer,camrenderer->assets->player_sprite,&spritesheet,&rect,0,nullptr,isorientationleft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);


    if(hurtanim){
        vector2 screenpos = camrenderer->worldtoscreen(vector2{x,y});

        SDL_Rect rect;
        rect.x = screenpos.x;
        rect.y = 1000-screenpos.y;
        rect.w = w;
        rect.h = -h;

        SDL_SetRenderDrawColor(camrenderer->renderer, 255, 0, 0, 0);
        SDL_RenderFillRect(camrenderer->renderer,&rect);
        hurtanim=false;
    }
    }
    //cout <<"as" << endl;

}

void CPlayer::useactiveitem(vector2 worldpos){
    if(!activeitem) return;
    activeitem->use(world,worldpos);
}

CPlayer::~CPlayer(){
    delete activeitem;
}