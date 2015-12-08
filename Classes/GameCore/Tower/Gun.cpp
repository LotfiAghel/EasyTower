#include "Gun.h"
#include "../BaseGameMap.h"
#include "../all.h"

#include "../Unit/Unit.h"
void Gun::update(float dt){
    time_waiting_to_be_ready-=dt;
    if(!is_focused_on_target){
        int t=find_target();
        if(t!=-1){
            target_idx=t;
            is_focused_on_target=true;
        }
    }
   find_angle(dt);


    //time_waiting_to_be_ready=10;



    if(time_waiting_to_be_ready<0 && is_focused_on_target && can_attack()){
        shot_signal=true;
        if(level==level1 || level==level3){
            GunShot *m=new GunShot(this->game_map,this,target_idx);
            m->target_idx=target_idx;
            m->pos=pos+Point(cos(angle),sin(angle))*20;
            m->speed=2800;
            m->max_range=2000;
            m->velocity=Point(cos(angle),sin(angle))*m->speed;
            m->angle=angle;
            time_waiting_to_be_ready =0.1;
            this->game_map.add_misel(m);
            misle_lunch_ted=1;
            last_time=0;

        }

        if(level==level3){
            GunShot *m=new GunShot(this->game_map,this,target_idx);
            m->target_idx=target_idx;
            m->pos=pos+Point(cos(angle),sin(angle))*20+Point(sin(angle),-cos(angle))*20;;
            m->speed=2800;
            m->max_range=2000;
            m->velocity=Point(cos(angle),sin(angle))*m->speed;
            m->angle=angle;
            this->game_map.add_misel(m);
            {
                GunShot *m=new GunShot(this->game_map,this,target_idx);
                m->target_idx=target_idx;
                m->pos=pos+Point(cos(angle),sin(angle))*20-Point(sin(angle),-cos(angle))*20;;
                m->speed=2800;
                m->max_range=2000;
                m->velocity=Point(cos(angle),sin(angle))*m->speed;
                m->angle=angle;
                this->game_map.add_misel(m);
            }
        }


        if(level==level2){
            GunShot *m=new GunShot(this->game_map,this,target_idx);
            m->target_idx=target_idx;
            m->state = Misle::in_move;
            m->pos=pos+Point(cos(angle),sin(angle))*20+Point(sin(angle),-cos(angle))*10;;
            m->speed=2800;
            m->max_range=2000;
            m->velocity=Point(cos(angle),sin(angle))*m->speed;
            m->angle=angle;
            this->game_map.add_misel(m);
            {
                GunShot *m=new GunShot(this->game_map,this,target_idx);
                m->target_idx=target_idx;
                m->pos=pos+Point(cos(angle),sin(angle))*20-Point(sin(angle),-cos(angle))*10;
                m->speed=2800;
                m->max_range=2000;
                m->velocity=Point(cos(angle),sin(angle))*m->speed;
                m->angle=angle;
                this->game_map.add_misel(m);
            }
        }
    }

}



void GunShot::update(float dt){


    Point f=((BoardObject*)game_map.units[target_idx])->pos;
    f-=pos;
    for(int i=0; i<10;++i){
        if(f.lengthSquared()<20*20){
            state=in_cross;
        }
        f-=velocity*dt/10;
    }
    if(state==in_move)
        pos+=velocity*dt;
    Misle::update(dt);

}
