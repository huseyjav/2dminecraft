#include "item.h"



class CEatable : public CItem{
public:
    unsigned int eatcooldown;
    uint lastused=0;
    int healthboost;
    CEatable(itemID id, CEntity* owner, int stackcount1, int eatcooldown,int healthboost);
    CEatable(eatableread read);
    eatableread geteatableread();
    virtual void savetofile(ostream & os) override;
    void use(CWorld* world,vector2 clickpos) override;
    virtual ~CEatable()=default;
};