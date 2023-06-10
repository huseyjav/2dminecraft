#include "placeable.h"
#include "world.h"
#include "constids.h"
CPlaceable::CPlaceable(itemID id, CEntity* owner, int stackcount1) : CItem(id,owner,stackcount1){

}



void CPlaceable::use(CWorld* world,vector2 clickpos){
    if(world->placeblock(gettileID(id),clickpos))
        currentcount--;
}