#include "item.h"



class CEatable : public CItem{
public:
    unsigned int eatcooldown;
    uint lastused=0;
    int healthboost;
    CEatable(itemID id, CEntity* owner, int stackcount1, int eatcooldown,int healthboost);
    CEatable(eatableread read);
    /**
     * @brief returns struct used for saving game state and load for constructor
     * 
     * @return eatableread 
     */
    eatableread geteatableread();
    /**
     * @brief saves information needed to reconstruct class from file
     * 
     * @param os 
     */
    virtual void savetofile(ostream & os) override;
    void use(CWorld* world,vector2 clickpos) override;
    virtual ~CEatable()=default;
};