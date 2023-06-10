#pragma once

#include "item.h"



class CPlaceable : public CItem{
public:

    //CItem(itemID id, CEntity* owner,int stackcount1)
    CPlaceable(itemID id, CEntity* owner, int stackcount1);
    void use(CWorld* world,vector2 clickpos) override;
};