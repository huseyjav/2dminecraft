#include "eatable.h"
#include "player.h"

CEatable::CEatable(itemID id, CEntity* owner, int stackcount1 , int eatcooldown,int healthboost) : CItem(id,owner,stackcount1) , eatcooldown(eatcooldown),healthboost(healthboost){

}
void CEatable::use(CWorld* world,vector2 clickpos){
    if(SDL_GetTicks()-lastused<eatcooldown) return;
    
    CPlayer* player = (CPlayer*)owner;
    
    if(player->health + healthboost >100) player->health=100;
    else player->health+=healthboost;
    currentcount--;
    lastused = SDL_GetTicks();
}

CEatable::CEatable(eatableread read) : CItem(read.item), eatcooldown(read.eatcooldown),healthboost(read.healthboost){

}

eatableread CEatable::geteatableread(){
    eatableread toret;
    toret.item = getitemread();
    toret.healthboost = healthboost;
    toret.eatcooldown = eatcooldown;
    return toret;
}
void CEatable::savetofile(ostream & os){
    os.write(reinterpret_cast<char*>(&id),sizeof(itemID));
    eatableread towrite = geteatableread();
    os.write(reinterpret_cast<char*>(&towrite),sizeof(eatableread));
}