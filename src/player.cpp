#include "player.h"
#include "world.h"
#include "entity.h"
#include "itemfactory.h"
#include <iostream>

using namespace std;

CPlayer::CPlayer(int x, int y, int w, int h, int velocityX,CWorld* world): CEntity(x,y,w,h,velocityX,world),hotbar(6,nullptr){
    hotbar.at(0) = makeitem(itemID::emptyhand_id);
    hotbar.at(1) = makeitem(itemID::sword_id);
    hotbar.at(2) = makeitem(itemID::grassblock_id);
    hotbar.at(0)->owner=this;
    hotbar.at(1)->owner=this;
    hotbar.at(2)->owner=this;
}

CPlayer::CPlayer(playerread& oldstate,CWorld* world): CEntity(oldstate.entity,world),CAlive(oldstate.alive) ,respawnx(oldstate.respawnx),respawny(oldstate.respawny),activeitem(oldstate.activeitem) ,hotbar(6,nullptr){

}
playerread CPlayer::getplayerread(){
    playerread toret;
    toret.entity = getentityread();
    toret.alive = getaliveread();
    toret.respawnx = respawnx;
    toret.respawny = respawny;
    toret.activeitem = activeitem;
    return toret;
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
    if(!isValidcoordinate(respawnx,respawny)){
        cout << "generating new location" << endl;
        vector2 randomspot = world->genSpawnpoint(h,w,this);
        respawnx = randomspot.x;
        respawny = randomspot.y;
    }
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
    if(!alive) return;
    if(!hotbar[activeitem]) return;
    hotbar[activeitem]->use(world,worldpos);
    if(hotbar[activeitem]->currentcount<=0){
        delete hotbar[activeitem];
        hotbar[activeitem]=nullptr;
    }
}

CPlayer::~CPlayer(){
    for(auto i : hotbar){
        if(!i) continue;
        delete i;
    }
}


void CPlayer::setactiveitem(int slot){
    if(slot>(int)hotbar.size() || slot<1) return;
    if(!hotbar[slot-1]) return;
    activeitem=slot-1;
}

int CPlayer::stackitem(itemID id,int count){
    for(auto i : hotbar){
        if(!i) continue;
        if(i->id!=id) continue;
        int howmanywecanadd = i->maxcount-i->currentcount;
        if(howmanywecanadd>=count){
            i->currentcount+=count;
            return count;
        }
        else if(howmanywecanadd==0) continue;
        else if(howmanywecanadd<count){
            i->currentcount+=howmanywecanadd;
            return howmanywecanadd;
        }
    }
    for(size_t i = 0 ; i<hotbar.size();i++){
        if(hotbar[i]) continue;
        hotbar[i]=makeitem(id);
        hotbar[i]->owner=this;
        hotbar[i]->currentcount=count;
        return count;
    }
    
    return 0;
}