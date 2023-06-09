#include "item.h"
//#include "world.h"
//#include "entity.h"
#include <iostream>

using namespace std;
CItem::CItem(itemID id, CEntity* owner,int stackcount=1) : id(id),owner(owner),stackcount(stackcount){

}



SDL_Texture* getTexture(itemID id,CAssets* assets){
    switch(id){
        case itemID::emptyhand_id:
            return assets->fist;
        case itemID::grassblock_id:
            return nullptr;
        case itemID::meat_id:
            return nullptr;
        case itemID::pickaxe_id:
            return nullptr;
        case itemID::sword_id:
            return assets->sword;
        default:
            return nullptr;
    }
}