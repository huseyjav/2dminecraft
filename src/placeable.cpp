#include "placeable.h"
#include "world.h"
#include "constids.h"
CPlaceable::CPlaceable(itemID id, CEntity* owner, int stackcount1) : CItem(id,owner,stackcount1){

}

CPlaceable::CPlaceable(placeableread read) : CItem(read.item){

}

void CPlaceable::use(CWorld* world,vector2 clickpos){
    if(world->placeblock(gettileID(id),clickpos))
        currentcount--;
}



placeableread CPlaceable::getplaceableread(){
    placeableread toret;
    toret.item = getitemread();
    return toret;
}
void CPlaceable::savetofile(ostream & os){
    os.write(reinterpret_cast<char*>(&id),sizeof(itemID));
    placeableread towrite = getplaceableread();
    os.write(reinterpret_cast<char*>(&towrite),sizeof(placeableread));
}