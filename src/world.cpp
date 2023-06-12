#include "world.h"
#include <iostream>
#include "player.h"
#include "game.h"
#include "pickable.h"
#include "hostilenpc.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
vector<vector<CTile>> LoadTilesFromFile(ifstream& is) {
    int numRows, numCols;
    is.read(reinterpret_cast<char*>(&numRows), sizeof(int));
    is.read(reinterpret_cast<char*>(&numCols), sizeof(int));

    vector<vector<CTile>> loadedTiles(numRows, vector<CTile>(numCols));

    for (auto& row : loadedTiles) {
        for (auto& tile : row) {
            is.read(reinterpret_cast<char*>(&tile), sizeof(CTile));
        }
    }

    return loadedTiles;
}
CWorld::CWorld(int w, int h){
    //tiles = LoadTilesFromFile("tiles.sav"); 
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

CWorld::CWorld(ifstream& is){
    tiles = LoadTilesFromFile(is);
    for(auto i : tiles){
        for(auto j : i){
            j.world=this;
        }
    }
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
            entityID id = (*i)->getitemdrop();
            int tempx=(*i)->x;
            int tempy=(*i)->y;
            //int temph=(*i)->h;
            //int tempw=(*i)->w;
            delete *i;
            worldnpcs.erase(i);
            entities.push_back ( new CPickable(id,tempx,tempy,50,50,10,this,1));
            continue;
        }
        else {
            (*i)->update();
        }
        i++;
    }
    while(worldnpcs.size()<10){
        vector2 vec = genSpawnpoint(195,90,nullptr);
        worldnpcs.push_back(new CZombie(vec.x,vec.y,90,195,7,this,player));
        //worldnpcs.push_back(new CNpc(0,800,90,195,7,this,player));
    }

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

void CWorld::handleAttack(CItem* item, CEntity* owner, vector2 worldpoint){
    //extra calculation is to set eyepos 
    vector<vector2> a = bresenhamalgo(vector2{owner->x+owner->w/2,owner->y+(int)((double)owner->h*0.9)},worldpoint);
    for(auto i : a){
        if(!iswithinlimitsofmap(i.x,i.y)) continue;
        if(tiles.at(i.y/100).at(i.x/100).isCollidable()){
            if(owner == player) tiles.at(i.y/100).at(i.x/100).health-=((CMelee*)item)->damage;
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
    if(iswithinlimitsofmap(worldpoint.x,worldpoint.y) && isempty(worldpoint.x/100,worldpoint.y/100)  && tiles.at(worldpoint.y/100).at(worldpoint.x/100).type==tileID::void_id) {
        tiles.at(worldpoint.y/100).at(worldpoint.x/100).setblocktype(toplace);
        return true;
    }
    return false;
}


bool CWorld::iswithinlimitsofmap(int x, int y){
    if(x<0 || y<0) return false;
    if((size_t)y/100 >= tiles.size()) return false;
    if((size_t)x/100 >= tiles.at(0).size()) return false;
    // if((size_t)y > 100 * tiles.size()) return false;
    // if((size_t)x > 100 * tiles.at(0).size()) return false;
    return true;
}


bool CWorld::isvalidlocation(int x, int y, int w, int h, CPhyiscs* checker){
    if(!iswithinlimitsofmap(x,y)) return false;
    if(!iswithinlimitsofmap(x+w,y+h)) return false;
    for(size_t i = (size_t)((y)/100) ; i <=(size_t)((y+h-1)/100) ; i ++) {
        for(size_t j = (size_t)((x)/100 ); j<=(size_t)((x+w-1)/100);j++){
            if(tiles.at(i).at(j).isCollidable()){
                return false;
            }
            
        }
    }

    for(size_t i = 0 ; i<worldnpcs.size();i++){
        if(checker && worldnpcs[i]==checker) continue;
        SDL_Rect a;
        SDL_Rect b;
        a.h = h;
        a.w = w;
        a.x = x;
        a.y = y;

        b.h = worldnpcs[i]->h;
        b.w = worldnpcs[i]->w;
        b.x = worldnpcs[i]->x;
        b.y = worldnpcs[i]->y;

        if(SDL_HasIntersection(&a,&b)) return false;
    }
    if(checker && checker!=player){
        SDL_Rect a;
        SDL_Rect b;
        a.h = h;
        a.w = w;
        a.x = x;
        a.y = y;

        b.h = player->h;
        b.w = player->w;
        b.x = player->x;
        b.y = player->y;

        if(SDL_HasIntersection(&a,&b)) return false;
    }
    return true;
}

vector2 CWorld::genSpawnpoint(int h, int w,CPhyiscs* checker){
    // int randomy = rand()%(100*tiles.size()-h);
    // int randomx = 100*tiles.at(0).size() - w;
    
    int randomx = rand()%(100*tiles.at(0).size()-w);
    int randomy = 100*(tiles.size()-1) - h;
    //cout << randomy << " " << randomx << endl;
    while(!isvalidlocation(randomx,randomy,w,h,checker)){
        randomx = rand()%(100*tiles.at(0).size()-w);
    }

    while(isvalidlocation(randomx,randomy-1,w,h,checker)){
        randomy--;
    }
    return vector2{randomx,randomy};
}