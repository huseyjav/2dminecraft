#include "constids.h"



entityID getentityIDtile(tileID tile){
    switch (tile)
    {
    case(tileID::grass_id):
        return entityID::dropped_grassblock_id;
    
    default:
        break;
    }
    return entityID::dropped_grassblock_id;
}

tileID gettileID(itemID item){
    switch(item){
        case (itemID::grassblock_id):
            return tileID::grass_id;
        default:
            return tileID::void_id;
    }
}


itemID getitemID(entityID entity){
    switch(entity){
        case(entityID::dropped_sword_id):
            return itemID::sword_id;
        case(entityID::dropped_pickaxe_id):
            return itemID::pickaxe_id;
        case(entityID::dropped_meat_id):
            return itemID::meat_id;
        case(entityID::dropped_grassblock_id):
            return itemID::grassblock_id;
        default:
            return itemID::emptyhand_id;
    }
}


/*

enum entityID{
    localplayer_id,
    zombiewithsword_id,
    dropped_sword_id,
    dropped_pickaxe_id,
    dropped_meat_id,
    dropped_grassblock_id
};

*/