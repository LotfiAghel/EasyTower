#include "Tower.h"
#include "../BaseGameMap.h"
#include "../Unit/Unit.h"

bool Tower::can_attack(){
    Point f=game_map.units[target_idx]->pos;
    f-=pos;
    if(f.lengthSquared()>range*range){
        is_focused_on_target=false;
        target_idx=-1;
        return false;
    }
    f.normalize();
    float angle=acos(f.x);
    if(f.y<0)
        angle=3.1415*2-angle;
    angle=angle_range_0_2pi(angle);
    this->angle=angle_range_0_2pi(this->angle);
    float dt_a=angle-this->angle;
    //return false;
    return(abs(dt_a)<3.1415/20);
}
void  Tower::find_angle(float dt){
   if(is_focused_on_target){
       Point f=game_map.units[target_idx]->pos;
       f-=pos;
       f.normalize();
       float angle=::find_angle(f);
       angle=angle_range_0_2pi(angle);
       this->angle=angle_range_0_2pi(this->angle);
       float dt_a=angle-this->angle;
       dt_a=angle_range_npi_pi(dt_a);

       float range=dt*angle_speed;
       //range=0;
       if(dt_a>range)
           this->angle+=dt*angle_speed;
       else if (dt_a<-range)
           this->angle-=dt*angle_speed;






   }
}
void Tower::update(float dt){
    if(!is_focused_on_target){
        int t=find_target();
        if(t!=-1){
            target_idx=t;
            is_focused_on_target=true;
        }
    }

    find_angle(dt);


    if(time_waiting_to_be_ready<0 && is_focused_on_target && can_attack()){
        Misle *m=new Misle(this->game_map,this,target_idx);
        m->target_idx=target_idx;
        m->pos=pos+Point(sin(angle),-cos(angle))*(0-1)*20;;
        m->speed=200;
        time_waiting_to_be_ready =1;
        this->game_map.add_misel(m);
        misle_lunch_ted=1;
        last_time=0;
        shot_signal=true;
    }
    if(misle_lunch_ted<3 && last_time>0.1 && is_focused_on_target && can_attack()){
        Misle *m=new Misle(this->game_map,this,target_idx);
        m->target_idx=target_idx;
        m->pos=pos+Point(sin(angle),-cos(angle))*(misle_lunch_ted-1)*20;
        m->speed=200;
        this->game_map.add_misel(m);

        misle_lunch_ted++;
        last_time=0;
        shot_signal=true;
    }else
        last_time+=dt;

}

int Tower::find_target(){
    float mind_sq=range*range;
    int mini=-1;
    for(int i=0; i<game_map.units.size();++i){
        float tmp=(game_map.units[i]->pos-pos).lengthSquared();
        if(tmp<mind_sq){
            mind_sq=tmp;
            mini=i;
            cerr<<"find target "<<time_waiting_to_be_ready<<" "<<i<<endl;
        }
    }
    target_idx=mini;
    return mini;

}


void Misle::update(float dt){
    Point f=pos;
    f-=tower->pos;

    if(state==in_move && f.lengthSquared()>max_range*max_range){
        //alive=false;
        state=Misle::in_miss;
        miss_signal=true;
        miss_time=game_map.total_time;

    }
    if(state==in_lunch && lunch_time+lunch_start_time<game_map.total_time){
        state=in_move;
    }

}

Misle::Misle(const GameMap &g_p,Tower *t,int idx):game_map(g_p),tower(t),target_idx(idx){
    g=nullptr;
    alive=true;
    speed=200;
    state=in_lunch;
}
/*void Misle::operator =(const Misle &m){
    memcpy((void*)this,(void*)&m,sizeof(Misle));
}/**/


