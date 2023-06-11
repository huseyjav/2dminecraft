#include "melee.h"
#include "world.h"
#include "entity.h"

CMelee::CMelee(itemID id,CEntity* owner,int attackcooldown,int damage) : CItem(id,owner,1),damage(damage),attackcooldown(attackcooldown){

}

meleeread CMelee::getmeleeread(){
    meleeread toret;
    toret.item = getitemread();
    toret.damage = damage;
    toret.attackcooldown = attackcooldown;
    return toret;
}

CMelee::CMelee(meleeread read) : CItem(read.item),damage(read.damage),attackcooldown(read.attackcooldown){

}

void CMelee::use(CWorld* world,vector2 clickpos){
    if(SDL_GetTicks()-lastused<attackcooldown) return;
    world->handleAttack(this,owner,clickpos);
    lastused = SDL_GetTicks();
}


void CMelee::savetofile(ostream & os){
    os.write(reinterpret_cast<char*>(&id),sizeof(itemID));
    meleeread towrite = getmeleeread();
    os.write(reinterpret_cast<char*>(&towrite),sizeof(meleeread));
}