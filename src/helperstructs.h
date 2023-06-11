#pragma once
#include "constids.h"

struct physicsread{
    int x;
    int y;
    int oldx;
    int oldy;
    int w;
    int h;
    bool isorientationleft;
    int velocityx;
    int velocityy;
    bool onGround;
    bool jumping;
    int timeinair;
    int howmanypixels;
};

struct entityread{
    physicsread a;
    bool shouldberemoved;
    entityID id;
};

struct aliveread{
    int health;
    int armor;
    bool alive;
    bool hurtanim;
};


struct playerread{
    entityread entity;
    aliveread alive;
    int respawnx; 
    int respawny;
    int activeitem;  
};