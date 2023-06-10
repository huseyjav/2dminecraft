#include "world.h"
#include <iostream>
#include "player.h"
#include "game.h"
#include "pickable.h"
CWorld::CWorld(int w, int h){
    for(int i = 0 ; i < h;i++){
        vector<CTile> topushback;
        for(int j = 0 ; j<w;j++){
            if(i<5) topushback.push_back(CTile(tileID::grass_id,j*100,i*100,this));
            else topushback.push_back(CTile(tileID::void_id,j*100,i*100,this));
        }
        tiles.push_back(topushback);
    }
    tiles.at(5).at(6).type = tileID::grass_id;
    tiles.at(6).at(5).type = tileID::grass_id;
    tiles.at(7).at(4).type = tileID::grass_id;
    tiles.at(5).at(2).type = tileID::grass_id;
    tiles.at(6).at(3).type = tileID::grass_id;
    //tiles.at(7).at(4).type = GRASS;
}

CWorld::~CWorld(){
    for(auto i : worldnpcs){
        delete i;
    }
    for(auto i : entities){
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
    for(auto i : entities){
        i->render(renderer);
    }

}


void CWorld::setplayer(CPlayer* pl){
    player = pl;
}

void CWorld::update(){
    player->update();
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
    // for(auto i : entities){
    //     i->update();
    // }

    for(auto i = entities.begin() ; i!=entities.end();){
        if((*i)->shouldberemoved){
            delete *i;
            entities.erase(i);

            continue;
        }
        else {
            (*i)->update();
        }
        i++;
    }

    //resetTilehealth();
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
    //extra calculation is to set eyepos 
    vector<vector2> a = bresenhamalgo(vector2{owner->x+owner->w/2,owner->y+(int)((double)owner->h*0.9)},worldpoint);
    for(auto i : a){
        if(tiles.at(i.y/100).at(i.x/100).isCollidable()){
            lastminedx=i.x/100;
            lastminedy=i.y/100;
            lastminetick = CGame::tick;
            tiles.at(i.y/100).at(i.x/100).health-=((CMelee*)item)->damage;
            if(tiles.at(i.y/100).at(i.x/100).health<=0){
                tileID temp = tiles.at(i.y/100).at(i.x/100).type;
                tiles.at(i.y/100).at(i.x/100).type=tileID::void_id;
                entities.push_back(new CPickable(getentityIDtile(temp),(i.x/100)*100+10 ,(i.y/100)*100+50,50,50,10,this,1));
            }
            return;
        }
        if(owner!=player){
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


void CWorld::resetTilehealth(){
    if(CGame::tick!=lastminetick && lastminedx>=0 && lastminedy>=0){
        //tiles.at(lastminedy).at(lastminedx).health = tiles.at(lastminedy).at(lastminedx).maxhealth;
    }
}

bool CWorld::isempty(int x, int y){
    SDL_Rect a;
    SDL_Rect b;

    a.x = x*100;
    a.y = y*100;
    a.h = 100;
    a.w = 100;

    b.x = player->x;
    b.y = player->y;
    b.h = player->h;
    b.w = player->w;

    if(SDL_HasIntersection(&a,&b)) return false;

    for(auto i : worldnpcs){
        b.x = i->x;
        b.y = i->y;
        b.h = i->h;
        b.w = i->w;
        if(SDL_HasIntersection(&a,&b)) return false;
    }
    for(auto i : entities){
        b.x = i->x;
        b.y = i->y;
        b.h = i->h;
        b.w = i->w;
        if(SDL_HasIntersection(&a,&b)) return false;
    }
    return true;
}

bool CWorld::placeblock(tileID toplace,vector2 worldpoint){
    if(isempty(worldpoint.x/100,worldpoint.y/100)  && tiles.at(worldpoint.y/100).at(worldpoint.x/100).type==tileID::void_id) {
        tiles.at(worldpoint.y/100).at(worldpoint.x/100).setblocktype(toplace);
        return true;
    }
    return false;
}
