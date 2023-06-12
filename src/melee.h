#pragma once
#include "item.h"
#include "SDL2/SDL.h"


class CMelee : public CItem{
public:
    int damage;
    unsigned int attackcooldown;
    uint lastused=0;
    CMelee(itemID id,CEntity* owner,int attackcooldown,int damage);
    CMelee(meleeread read);
    void use(CWorld* world,vector2 clickpos) override;
    /**
     * @brief returns struct used for saving game state and load for constructor
     * 
     * @return meleeread 
     */
    meleeread getmeleeread();
    /**
     * @brief saves information needed to reconstruct class from file
     * 
     * @param os 
     */
    virtual void savetofile(ostream & os) override;
    virtual ~CMelee() = default;
};