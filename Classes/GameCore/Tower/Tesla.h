#ifndef TELSA_H
#define TELSA_H

#include "Tower.h"

struct Tesla:public Tower{
    Tesla(GameCore &g_p,const Point &p):Tower(g_p,p){
        range=200;
        angle_speed=0;
    };
    virtual void update(float dt);

    int find_target();
};




#endif // TELSA_H
