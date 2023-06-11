#pragma once

#include "item.h"



class CPlaceable : public CItem{
public:

    //CItem(itemID id, CEntity* owner,int stackcount1)
    CPlaceable(itemID id, CEntity* owner, int stackcount1);
    CPlaceable(placeableread read);
    void use(CWorld* world,vector2 clickpos) override;
    placeableread getplaceableread();
    virtual void savetofile(ostream & os) override;
};