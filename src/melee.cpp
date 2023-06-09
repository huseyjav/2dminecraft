#include "melee.h"
#include "world.h"
#include "entity.h"

CMelee::CMelee(itemID id,CEntity* owner,int attackcooldown,int damage) : CItem(id,owner),damage(damage),attackcooldown(attackcooldown){

}

void CMelee::use(CWorld* world,vector2 clickpos){
    if(SDL_GetTicks()-lastused<attackcooldown) return;
    world->handleAttack(this,owner,clickpos);
    lastused = SDL_GetTicks();
}