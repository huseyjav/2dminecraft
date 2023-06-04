#include "aliveent.h"


#include <iostream>
using namespace std;
void CAlive::hurt(int damage){
    
    hurtanim=true;
    health-=damage;
    if(health<=0) {
        alive=false;
        cout << "dead " << endl;
    }
}