#pragma once

#include "item.h"



class CPlaceable : public CItem{
public:

    //CItem(itemID id, CEntity* owner,int stackcount1)
    CPlaceable(itemID id, CEntity* owner, int stackcount1);
    CPlaceable(placeableread read);
    virtual ~CPlaceable()=default;
    void use(CWorld* world,vector2 clickpos) override;
    /**
     * @brief returns struct used for saving game state and load for constructor
     * 
     * @return placeableread 
     */
    placeableread getplaceableread();
    /**
     * @brief saves information needed to reconstruct class from file
     * 
     * @param os 
     */
    virtual void savetofile(ostream & os) override;
};