#include "physics.h"
#include "world.h"
#include <iostream>

using namespace std;
CPhyiscs::CPhyiscs(int x, int y, int w, int h,int velocityX,CWorld* world) : x(x),y(y),w(w),h(h),velocityX(velocityX),world(world){

}

CPhyiscs::CPhyiscs(physicsread physics, CWorld* world) : x(physics.x),y(physics.y),oldx(physics.oldx),oldy(physics.oldy),w(physics.w),h(physics.h),isorientationleft(physics.isorientationleft),velocityX(physics.velocityx),velocityY(physics.velocityy),world(world),onGround(physics.onGround),jumping(physics.jumping),timeinair(physics.timeinair),howmanypixels(physics.howmanypixels){

}

physicsread CPhyiscs::getphysicsread(){
    physicsread toret;
    toret.x = x;
    toret.y = y;
    toret.oldx = oldx;
    toret.oldy = oldy;
    toret.w = w;
    toret.h = h;
    toret.isorientationleft = isorientationleft;
    toret.velocityx = velocityX;
    toret.velocityy = velocityY;
    toret.onGround = onGround;
    toret.jumping = jumping;
    toret.timeinair = timeinair;
    toret.howmanypixels = howmanypixels;
    return toret;
}

void CPhyiscs::render(CCameraRenderer* renderer){
    //cout << x << " " << y << "\n";
    //

    vector2 screenpos = renderer->worldtoscreen(vector2{x,y});

    //cout << screenpos.x << " " << screenpos.y << "\n";
    //cout << renderer->centerX << " " << renderer->centerY << "\n";
    SDL_Rect rect;
    rect.x = screenpos.x;
    rect.y = 1000-screenpos.y;
    //rect.y =screenpos.y;
    rect.w = w;
    rect.h = -h;

    SDL_SetRenderDrawColor(renderer->renderer, 255, 177, 50, 0);
    SDL_RenderFillRect(renderer->renderer,&rect);

}




void CPhyiscs::setonGround(){
    onGround=true;
    if(isValidcoordinate(x,y-1)) onGround=false;
    // onGround=false;
    // if(y%100!=0){
    //     onGround = false;
    //     return;
    // }
    // int heightidx = y/100 - 1;
    // for(int i = (x+1)/100;i<=(x+w-1)/100;i++){
    //     //cout << i << endl;
    //     if(heightidx>=world->tiles.size()) return;
    //     if(i>=world->tiles.at(heightidx).size()) return;   
    //     if(world->tiles.at(heightidx).at(i).isCollidable()) {
    //         onGround = true;
    //         return;    
    //     }
    // }
    

}


bool CPhyiscs::isValidcoordinate(int newx, int newy){
    return world->isvalidlocation(newx,newy,w,h,this);
    
    if(newx<0 || newy<0) return false;
    //cout << y << " "<< x << endl;
    if(uint(newy+h-1)/100 >= world->tiles.size()) return false;
    if(uint(newx+w-1)/100 >= world->tiles.at(0).size()) return false;
    //cout << (newy+h-1)/100  << endl;
    for(int i = (newy)/100 ; i <=(newy+h-1)/100 ; i ++) {
        for(int j = (newx)/100 ; j<=(newx+w-1)/100;j++){
            if(world->tiles.at(i).at(j).isCollidable()){
                return false;
            }
            
        }
    }
    return true;
}

void CPhyiscs::movewOffset(int offsetx, int offsety){
    if(isValidcoordinate(x+offsetx,y+offsety)){
        x+=offsetx;
        y+=offsety;
    }
    else{
        if(offsety<0){
            moveDownmax();
        }
        if(offsety>0){
            moveUpmax();
        }
        if(offsetx<0){
            moveLeftmax();
        }
        if(offsetx>0){
            moveRightmax();
        }
    }
}

void CPhyiscs::moveLeft(){
    movewOffset(-velocityX,0);
    //x-=10;
    //if(isValidcoordinate(x-10,y)) x-=10;
    //velocityX-=5;
}
void CPhyiscs::moveRight(){
    movewOffset(velocityX,0);
    //if(isValidcoordinate(x+10,y)) x+=10;
    //velocityX+=5;
}

void CPhyiscs::jump(){
    
    if(onGround){
        jumping = true;
        timeinair=160;
    }
}

void CPhyiscs::stepajump(){
    //int maxjump = 150; // hardcoded value of how far object will jump
    if(timeinair>0){
        timeinair-=16;
        movewOffset(0,15);
    }
    else{
        jumping = false;
    }
}

void CPhyiscs::moveLeftmax(){
    int xoffset=0;
    while(isValidcoordinate(x+xoffset-1,y)){
        xoffset--;
    }
    movewOffset(xoffset,0);
}   

void CPhyiscs::moveRightmax(){
    int xoffset=0;
    while(isValidcoordinate(x+xoffset+1,y)){
        xoffset++;
    }
    movewOffset(xoffset,0);
}

void CPhyiscs::moveUpmax(){
    int yoffset=0;
    while(isValidcoordinate(x,y+yoffset+1)){
        yoffset++;
    }
    movewOffset(0,yoffset);
}

void CPhyiscs::moveDownmax(){
    int yoffset=0;
    while(isValidcoordinate(x,y+yoffset-1)){
        yoffset--;
    }
    movewOffset(0,yoffset);
    // for(int i = (y/100)-1 ; i>=0 ; i++){
    //     for(int j =(x+1)/100 ; j<=(x+w-1)/100 ; j++){
    //         if(world->tiles.at(i).at(j).isCollidable()){
    //             cout << i << endl;
    //             y = (i+1)*100;
    //             return;
    //         }
    //     }
    // }
}

int CPhyiscs::handleFreefall(){
    if(!onGround && !jumping){
        int oldy=y;
        movewOffset(0,-12);
        howmanypixels+=(oldy-y);
    }
    else{
        int temp = howmanypixels;
        howmanypixels=0;
        return temp;
    }
    return 0;
}
