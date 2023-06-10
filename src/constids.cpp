#include "constids.h"



entityID getentityIDtile(tileID tile){
    switch (tile)
    {
    case(tileID::grass_id):
        return entityID::dropped_grassblock_id;
    
    default:
        break;
    }
}