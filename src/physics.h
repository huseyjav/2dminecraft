#pragma once

#include "SDL2/SDL.h"




#include "renderer.h"
#include "renderable.h"

class CWorld;



class CPhyiscs : public CRenderable{
public:
    // location in world
    int x,y; 
    int oldx=0,oldy=0;
    // collidable widht, height in world
    int w,h;
    int isorientationleft = false;
    int velocityX;
    int velocityY;
    CWorld* world;
    bool onGround;
    bool jumping=false;
    int timeinair; // time in air in milliseconds
    int howmanypixels = 0 ; // how far object fell from sky (used for fall damage)
    CPhyiscs(int x, int y, int w, int h,int velocityX,CWorld* world);
    virtual void render(CCameraRenderer * renderer) override;



    void setonGround();
    /**
     * @brief checks wheter new location overlaps with any collidable
     *
     * @param newx 
     * @param newy 
     * @return true can be there 
     * @return false cant be there
     */

    /**
     * @brief handles free fall
     * 
     * @return int returns how many pixels it fell for
     */
    int handleFreefall();

    bool isValidcoordinate(int newx, int newy);
    /**
     * @brief will move object as much as possible with given offset
     * 
     * @param offsetx 
     * @param offsety 
     */
    void movewOffset(int offsetx, int offsety);

    void moveLeft();
    void moveRight();
    void jump();
    // apply jump (should be called every frame)
    void stepajump();

    // these functions will make object move to whichever direction until there is an obsticle 
    void moveLeftmax();

    void moveRightmax();

    void moveUpmax();

    void moveDownmax();

};

