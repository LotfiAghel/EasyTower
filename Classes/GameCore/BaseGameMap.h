#ifndef TOWER_BASEGAMEMAP_H
#define TOWER_BASEGAMEMAP_H



#include "all.h"







// xxx
#define x0 0
#define x1 259
#define x2 450
#define x3 690
#define x4 1024


///y
#define y0 0
#define y1 88
#define y2 298
#define y3 600



class GameMap{
public:
    float total_time=0;
   vector<Path> paths;
   vector<Unit* > units;
   vector<Tower* > towers;
   vector<Misle* > misels;

   void init();
   void update(float dt);
   void add_misel(Misle *misle);
};




#endif
