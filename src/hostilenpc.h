#include "npc.h"
#include "melee.h"

class CZombie : public CNpc{
public:
    CItem* sword=nullptr;
    CZombie(int x, int y, int w, int h, int velocityX,CWorld* world, CEntity* target);
    virtual void update() override;
    virtual ~CZombie();
};