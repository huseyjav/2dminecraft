#include "player.h"
#include "world.h"
#include "entity.h"

#include <iostream>

using namespace std;

CPlayer::CPlayer(int x, int y, int w, int h, CWorld* world): CEntity(x,y,w,h,world){

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
        health-=10;
    }
    if(health<=0) alive=false;
}


void CPlayer::respawn(){
    x=respawnx;
    y=respawny;
    health=100;
    alive=true;
}

void CPlayer::render(CCameraRenderer* camrenderer){
    if(alive){
        CEntity::render(camrenderer);
    }
}