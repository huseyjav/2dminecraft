#include "hostilenpc.h"
#include "itemfactory.h"
#include "player.h"
CZombie::CZombie(int x, int y, int w, int h, int velocityX,CWorld* world, CEntity* target): CNpc(x, y, w, h, velocityX, world,target,entityID::zombiewithsword_id){
    sword = makeitem(itemID::emptyhand_id);
    sword->owner = this;
}


void CZombie::update(){
    if (targetwithinproximinity() && ((CPlayer*)target)->alive )
    {
        if(abs(x - target->x) < 200){
            sword->use(world,vector2{target->x+target->w/2, target->y + target->h/2});
        }
        if (target->x < x)
        {
            if (oldx == x && oldy == y)
                jump();
            oldx = x;
            oldy = y;
            moveLeft();
        }
        else if (target->x > x)
        {
            if (oldx == x && oldy == y)
                jump();
            oldx = x;
            oldy = y;
            moveRight();
        }

    }

    CEntity::update();
} 

CZombie::~CZombie(){
    delete sword;
}