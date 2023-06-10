#include "item.h"



class CEatable : public CItem{
public:
    unsigned int eatcooldown;
    uint lastused=0;
    int healthboost;
    CEatable(itemID id, CEntity* owner, int stackcount1, int eatcooldown,int healthboost);
    void use(CWorld* world,vector2 clickpos) override;
};