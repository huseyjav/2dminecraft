#pragma once
#include "physics.h"
//#include "world.h"


class CWorld;

class CEntity : public CPhyiscs{
public:
    
    //CEntity()=default;
    CEntity(int x, int y, int w, int h,int velocityX,CWorld* world);

    
    
    virtual void update();

};

