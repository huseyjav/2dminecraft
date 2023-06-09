#include "itemfactory.h"



CItem* makeitem(itemID id){
    switch(id){
        case itemID::emptyhand_id:
            return new CMelee(itemID::emptyhand_id,nullptr,300,10);
        case itemID::grassblock_id:
            return nullptr;
        case itemID::meat_id:
            return nullptr;
        case itemID::pickaxe_id:
            return nullptr;
        case itemID::sword_id:
            return new CMelee(itemID::sword_id,nullptr,300,50);
        default:
            return nullptr;
    }
}