
#include "Rocket.h"
#include "../BaseGameMap.h"
#include "../all.h"

#include "../Unit/Unit.h"
void Rocket::update(float dt){
    time_waiting_to_be_ready-=dt;
    if(!is_focused_on_target){
        int t=find_target();
        if(t!=-1){
            target_idx=t;
            is_focused_on_target=true;
        }
    }
   find_angle(dt);



    if(time_waiting_to_be_ready<0 && is_focused_on_target && can_attack()){
        RocketShot *m=new RocketShot(this->game_map,this,target_idx);
        m->target_idx=target_idx;
        m->pos=pos+Point(cos(angle),sin(angle))*20;
        m->speed=500;
        m->max_range=3000;
        m->velocity=Point(cos(angle),sin(angle))*m->speed;
        m->angle=angle;
        time_waiting_to_be_ready =1;
        this->game_map.add_misel(m);
        misle_lunch_ted=1;
        last_time=0;
        shot_signal=true;
    }

}



void RocketShot::update(float dt){
    Point f=game_map.units[target_idx]->pos;
    f-=pos;
    if(f.lengthSquared()<100){
        alive=false;
    }
    angle=find_angle(f);
    f.normalize();
    pos+=f*speed*dt;
    Misle::update(dt);


}

