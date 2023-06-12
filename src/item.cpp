#include "item.h"
//#include "world.h"
//#include "entity.h"
#include <iostream>

using namespace std;
CItem::CItem(itemID id, CEntity* owner,int stackcount1=1) : id(id),owner(owner),maxcount(stackcount1){

}

CItem::CItem(itemread read) :  id(read.id),currentcount(read.currentcount),maxcount(read.maxcount){

}

itemread CItem::getitemread(){
    itemread toret;
    toret.currentcount = currentcount;
    toret.id = id;
    toret.maxcount = maxcount;
    return toret;
}

SDL_Texture* getTexture(itemID id,CAssets* assets){
    switch(id){
        case itemID::emptyhand_id:
            return assets->fist;
        case itemID::grassblock_id:
            return assets->grassblock;
        case itemID::meat_id:
            return assets->meat;
        case itemID::pickaxe_id:
            return nullptr;
        case itemID::sword_id:
            return assets->sword;
        default:
            return nullptr;
    }
}

void CItem::savetofile(ostream & os){
    os.write(reinterpret_cast<char*>(&id),sizeof(itemID));
    itemread towrite = getitemread();
    os.write(reinterpret_cast<char*>(&towrite),sizeof(itemread));
}