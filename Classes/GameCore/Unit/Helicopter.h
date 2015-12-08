#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "Unit.h"

struct Helicopter:public Unit{
    Helicopter(const GameMap &g_p,const Path &p):Unit(g_p,p){};
};

#endif // HELICOPTER_H
