#include "npc.h"

void CNpc::update()
{

    if (targetwithinproximinity())
    {
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

CNpc::CNpc(int x, int y, int w, int h, int velocityX, CWorld *world, CEntity *target) : CEntity(x, y, w, h, velocityX, world), target(target)
{
}

void CNpc::render(CCameraRenderer *camrenderer)
{
    if (alive)
    {
        CEntity::render(camrenderer);
        if (hurtanim)
        {
            vector2 screenpos = camrenderer->worldtoscreen(vector2{x, y});

            SDL_Rect rect;
            rect.x = screenpos.x;
            rect.y = 1000 - screenpos.y;
            rect.w = w;
            rect.h = -h;

            SDL_SetRenderDrawColor(camrenderer->renderer, 255, 0, 0, 0);
            SDL_RenderFillRect(camrenderer->renderer, &rect);
            hurtanim = false;
        }
    }
}

bool CNpc::targetwithinproximinity()
{
    if (abs(x - target->x) < 400)
        return true;
    return false;
}


entityID CNpc::getitemdrop(){
    return entityID::dropped_meat_id;
}
