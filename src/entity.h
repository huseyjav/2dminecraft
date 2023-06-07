#pragma once
#include "physics.h"
//#include "world.h"
#include "constids.h"

class CWorld;

class CEntity : public CPhyiscs{
public:
    entityID id;
    //CEntity()=default;
    CEntity(int x, int y, int w, int h,int velocityX,CWorld* world);

    
    
    virtual void update();

};

