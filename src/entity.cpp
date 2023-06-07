#include "entity.h"

CEntity::CEntity(int x, int y, int w, int h,int velocityX,CWorld* world) : CPhyiscs(x,y,w,h,velocityX,world){

}

void CEntity::update(){
    setonGround();
    //cout << "a" << endl;
    //if(isValidcoordinate(200,496)) std::cout << " as " << std::endl;
    handleFreefall();
    if(jumping){
        stepajump();
    }

}