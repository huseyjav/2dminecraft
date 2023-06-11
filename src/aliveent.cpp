#include "aliveent.h"


#include <iostream>
using namespace std;


CAlive::CAlive(aliveread& a) :  health(a.health),
                                armor(a.armor),
                                alive(a.alive),
                                hurtanim(a.hurtanim)
                                {}


aliveread CAlive::getaliveread(){
    aliveread toret;
    toret.health = health;
    toret.armor = armor;
    toret.alive = alive;
    toret.hurtanim = hurtanim;
    return toret;
}

void CAlive::hurt(int damage){
    
    hurtanim=true;
    health-=damage;
    if(health<=0) {
        alive=false;
        cout << "dead " << endl;
    }
}