#include "itemfactory.h"
#include "placeable.h"
#include "eatable.h"

using namespace std;

CItem* makeitem(itemID id){
    switch(id){
        case itemID::emptyhand_id:
            return new CMelee(itemID::emptyhand_id,nullptr,300,10);
        case itemID::grassblock_id:
            return new CPlaceable(itemID::grassblock_id,nullptr,64);
        case itemID::meat_id:
            return new CEatable(itemID::meat_id,nullptr,5,100,10);
        case itemID::pickaxe_id:
            return nullptr;
        case itemID::sword_id:
            return new CMelee(itemID::sword_id,nullptr,300,50);
        default:
            return nullptr;
    }
}


CItem* extractfromfile(ifstream & is){
    itemID id;
    is.read(reinterpret_cast<char*>(&id),sizeof(itemID));
    if(id==itemID::emptyhand_id || id==itemID::pickaxe_id || id==itemID::sword_id){
        meleeread extracted ;
        is.read(reinterpret_cast<char*>(&extracted),sizeof(meleeread));
        return new CMelee(extracted);
        // melee

    }
    else if(id==itemID::grassblock_id){
        //placeable
        placeableread extracted;
        is.read(reinterpret_cast<char*>(&extracted),sizeof(placeableread));
        return new CPlaceable(extracted);
    }
    else if(id==itemID::meat_id){
        //eatable
        eatableread extracted;
        is.read(reinterpret_cast<char*>(&extracted),sizeof(eatableread));
        return new CEatable(extracted);

    }
    cout << "aaaaaaaaaa" << endl;
    return nullptr;
}