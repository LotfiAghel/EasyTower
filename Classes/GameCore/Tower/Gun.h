#ifndef GUN_H
#define GUN_H
#include "Tower.h"


struct Gun:public Tower{
    Gun(GameCore &g_p,const Point &p):Tower(g_p,p){
        range=2000;
    };
    virtual void update(float dt);

};
struct GunShot:public Misle{
    GunShot(const GameCore &g_p,Tower *tower,int idx):Misle(g_p,tower,idx){};
    void update(float dt);
};



#endif // GUN_H
