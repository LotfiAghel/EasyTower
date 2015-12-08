#include "Canon.h"
#include "../BaseGameMap.h"
#include "../all.h"

#include "../Unit/Unit.h"
void Canon::update(float dt){
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
        CanonShot *m=new CanonShot(this->game_map,this,target_idx);
        m->target_pos=game_map.units[target_idx]->pos;
        m->state = Misle::in_move;
        m->pos=pos+Point(cos(angle),sin(angle))*20;
        m->speed=600;
        m->max_range=range;
        m->velocity=Point(cos(angle),sin(angle))*m->speed;
        m->angle=angle;
        time_waiting_to_be_ready =1;
        this->game_map.add_misel(m);
        misle_lunch_ted=1;
        last_time=0;
        shot_signal=true;
    }

}



void CanonShot::update(float dt){


    Point f=target_pos;
    f-=pos;
    if(state==in_move)
        for(int i=0; i<10;++i){
            if(f.lengthSquared()<10*10){
                cerr<<"cross "<<id<<endl;
                state=in_cross;
                cross_signal=true;
                cross_time=game_map.total_time;
                break;
            }
            f-=velocity*dt/10;
        }
    if(state==Misle::in_cross && cross_time+2<game_map.total_time){
        state=ded;
        alive=false;
        cerr<<"ded "<<id<<endl;
    }
    if(state==Misle::in_miss && miss_time+2<game_map.total_time){
        state=ded;
        alive=false;
        cerr<<"ded mised"<<id<<endl;
    }
    if(state==in_move)
        pos+=velocity*dt;
    Misle::update(dt);
}

