#pragma once
#include "physics.h"
//#include "world.h"
#include "constids.h"
#include "helperstructs.h"
class CWorld;

class CEntity : public CPhyiscs{
public:
    bool shouldberemoved=false;
    entityID id;
    //CEntity()=default;
    CEntity(int x, int y, int w, int h,int velocityX,CWorld* world);
    CEntity(entityID,int, int, int , int ,int ,CWorld*);
    CEntity(entityread entity,CWorld* world);
    
    entityread getentityread();

    virtual void update();

};

