#ifndef ROCKET_H
#define ROCKET_H

#include "Tower.h"
struct Rocket:public Tower{
    Rocket(GameCore &g_p,const Point &p):Tower(g_p,p){
        range=2000;
    };
    virtual void update(float dt);

};
struct RocketShot:public Misle{
    RocketShot(const GameCore &g_p,Tower *tower,int idx):Misle(g_p,tower,idx){};
    void update(float dt);
};

#endif // ROCKET_H
