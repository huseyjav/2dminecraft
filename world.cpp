#include "world.h"
#include <iostream>



CWorld::CWorld(int w, int h){
    for(int i = 0 ; i < h;i++){
        vector<CTile> topushback;
        for(int j = 0 ; j<w;j++){
            if(i<5) topushback.push_back(CTile(GRASS,j*100,i*100));
            else topushback.push_back(CTile(VOID,j*100,i*100));
        }
        tiles.push_back(topushback);
    }
    tiles.at(5).at(6).type = GRASS;
    tiles.at(6).at(5).type = GRASS;
    tiles.at(7).at(4).type = GRASS;
    tiles.at(5).at(2).type = GRASS;
    tiles.at(6).at(3).type = GRASS;
    //tiles.at(7).at(4).type = GRASS;
}



void CWorld::render(CCameraRenderer * renderer){
    for(auto i : tiles){
        for(auto j : i){
            j.render(renderer);
        }
    }
    player->render(renderer);
}


void CWorld::setplayer(CEntity* pl){
    player = pl;
}

void CWorld::update(){
    player->update();
}

void CWorld::handleInput(CCameraRenderer * camrenderer){
    int mouseX;
    int mouseY;
    Uint32 state = SDL_GetMouseState(&mouseX, &mouseY);
    if(state & SDL_BUTTON(SDL_BUTTON_LEFT)){
        vector2 worldpos = camrenderer->screentoworld(vector2{mouseX,mouseY});
        //worldpos.y = 1000-worldpos.y;
        //cout << worldpos.x << " " << worldpos.y << endl;
        int vx = worldpos.x/100;
        int vy = worldpos.y/100;

        if(!lastframekleftclick || vx!=lastclickedtilex || vy!=lastclickedtiley){
            if(tiles.at(vy).at(vx).type==VOID) tiles.at(vy).at(vx).type=GRASS;
            else tiles.at(vy).at(vx).type=VOID;
        }
        lastclickedtilex=vx;
        lastclickedtiley=vy;
        lastframekleftclick = true;
    }
    else{
        lastframekleftclick = false;
    }
}