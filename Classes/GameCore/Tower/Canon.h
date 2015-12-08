#ifndef CANON_H
#define CANON_H


#include "Tower.h"


struct Canon:public Tower{
    Canon(GameCore &g_p,const Point &p):Tower(g_p,p){
        range=200;
        angle=0;
        angle_speed=3.1415;
    };
    virtual void update(float dt);

};
struct CanonShot:public Misle{
    CanonShot(const GameCore &g_p,Tower *tower,int idx):Misle(g_p,tower,idx){};
    void update(float dt);
};




#endif // CANON_H
