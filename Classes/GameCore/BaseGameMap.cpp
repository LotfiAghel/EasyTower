







#include "BaseGameMap.h"
#include "Tower/Tower.h"
#include "Unit/Unit.h"
#include "Unit/Helicopter.h"
#include "Tower/Canon.h"
#include "Tower/Gun.h"
#include "Tower/Rocket.h"
#include "Tower/Tesla.h"















void GameMap::init(){
    Path p;
    p.push_back({x0,y3});
    p.push_back({x1,y3});
    p.push_back({x1,y2});
    p.push_back({x2,y2});
    p.push_back({x2,y1});
    p.push_back({x4,y1});
    //p.push_back({x4*2,y1});
    paths.push_back(p);
    {
        Path p;
        p.push_back({x0,y3});
        p.push_back({x0+1000,y3});
        paths.push_back(p);
        Helicopter *h=new Helicopter(*this,paths[paths.size()-1]);
        h->speed=50+50*2;
        h->defult_speed=50+50*2;
        h->set_health(100);
        units.push_back(h);
    }


    Point points[]={{100,y3*1.2},{100,y3*0.8},{350,y2*1.2},{350,y2*0.8},{550,y2*0.8},{700,y2*0.6}};
    for(int i=0; i<3; ++i){
        Tower *t=new Canon(*this,points[i]);

        t->is_focused_on_target=false;
        towers.push_back(t);
    }

    for(int i=3; i<4; ++i){
        Gun *t=new Gun(*this,points[i]);
        t->angle=0;
        t->angle_speed=3.1415;
        t->is_focused_on_target=false;
        towers.push_back(t);
    }
    for(int i=4; i<5; ++i){
        auto *t=new Rocket(*this,points[i]);
        t->angle=0;
        t->angle_speed=3.1415;
        t->is_focused_on_target=false;
        towers.push_back(t);
    }
    for(int i=5; i<6; ++i){
        auto *t=new Tesla(*this,points[i]);
        t->angle=0;
        t->angle_speed=3.1415;
        t->is_focused_on_target=false;
        towers.push_back(t);
    }


}
void GameMap::update(float dt){
    cerr<<"core update <<"<<endl;
    total_time+=dt;
    for(int i=0; i<units.size();++i)
         if(units[i]->alive){
             units[i]->update(dt);
         }else{
             units[i]->g->removeFromParent();
             units[i]=units[units.size()-1];
             units.pop_back();
         }
     if(int(total_time)!=int(total_time+dt)){
             Unit *u=new Unit(*this,paths[0]);
             u->speed=u->defult_speed=50+50*rand()%3;
             u->set_health(100);
             units.push_back(u);

         }

     for(int i=0; i<towers.size();++i){
        if(towers[i]->alive)
            towers[i]->update(dt);
     }
     for(int i=0; i<towers.size();++i)
        if(!towers[i]->alive){
            //towers[i]=towers[towers.size()-1];
            //towers.pop_back();
        }

     for(int i=0; i<misels.size();++i){
         if(misels[i]->alive)
             misels[i]->update(dt);
         else{
             cerr<<"remove misle ";
             misels[i]->update(dt);
             if(misels[i]->g!=nullptr){
                misels[i]->g->removeFromParent();
                cerr<<"."<<endl;
                misels[i]->g=nullptr;
             }
             misels[i]=misels[misels.size()-1];
             misels.pop_back();

         }
     }
    cerr<<"core update >>"<<endl;

}
void GameMap::add_misel(Misle *misle){
    misels.push_back(misle);
}
