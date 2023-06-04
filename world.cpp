#include "world.h"
#include <iostream>
#include "player.h"


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

CWorld::~CWorld(){
    for(auto i : worldnpcs){
        delete i;
    }
}

void CWorld::render(CCameraRenderer * renderer){
    for(auto i : tiles){
        for(auto j : i){
            j.render(renderer);
        }
    }
    player->render(renderer);
    for(auto i : worldnpcs){
        i->render(renderer);
    }
}


void CWorld::setplayer(CPlayer* pl){
    player = pl;
}

void CWorld::update(){
    player->update();
    // for(auto i : worldnpcs){
    //     if(!i->alive){
    //         worldnpcs.erase(i);
    //     }
    //     i->update();
    // }
    for(auto i = worldnpcs.begin() ; i!=worldnpcs.end();){
        if(!(*i)->alive){
            delete *i;
            worldnpcs.erase(i);

            continue;
        }
        else {
            (*i)->update();
        }
        i++;
    }
    if(worldnpcs.size()==0){
        worldnpcs.push_back(new CNpc(2000,800,90,195,7,this,player));
        //worldnpcs.push_back(new CNpc(0,800,90,195,7,this,player));
    }
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
            //if(tiles.at(vy).at(vx).type==VOID) tiles.at(vy).at(vx).type=GRASS;
            //else tiles.at(vy).at(vx).type=VOID;
        }
        lastclickedtilex=vx;
        lastclickedtiley=vy;
        lastframekleftclick = true;
    }
    else{
        lastframekleftclick = false;
    }
}

void CWorld::handleAttack(CItem* item, CEntity* owner, vector2 worldpoint){
    vector<vector2> a = bresenhamalgo(vector2{owner->x,owner->y},worldpoint);
    for(auto i : a){
        if(tiles.at(i.y/100).at(i.x/100).isCollidable()){
            cout << "mining block" << endl;
            return;
        }
        if(owner!=player){
            //cout << " aushdasudasudhasudha " << endl;
            if(i.x > player->x && i.x < player->x+player->w && i.y > player->y && i.y < player->y + player->h){
                player->hurt(((CMelee*)item)->damage);
                return;
                
            }
        }
        for(auto j : worldnpcs){
            if(owner==j) continue;
            //cout << "asdasda" << endl;
            if(i.x > j->x && i.x < j->x+j->w && i.y > j->y && i.y < j->y + j->h){
                j->hurt(((CMelee*)item)->damage);
                return;
            }
        }
    }
}