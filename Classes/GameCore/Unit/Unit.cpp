#include "Unit.h"
#include "../BaseGameMap.h"

Unit::Unit (const GameMap &g_p,const Path &p):game_map(g_p),distance_of_walk(0){
    alive=true;
    last_point_of_path_idx=-1;
    g=nullptr;
    velocity={0,0};
    go_next_from_last=0;
    end_of_part_lenth_swured=0;
    for(int i=0; i<p.size();++i){
        path.push_back(p[i]);
    }
    pos=p[0];
    slow_time=0;
}
void Unit::update(float dt){
    if(health<=0)
        alive=false;
    if(!alive)
        return ;
    slow_time-=dt;
    if(slow_time<0){
        speed=defult_speed;
    }
    go_next_from_last+=dt*speed;
    pos+=velocity*speed*dt;


    if(go_next_from_last>end_of_part_lenth_swured){
        go_next_from_last=0;

        ++last_point_of_path_idx;

        if(last_point_of_path_idx+1>path.size()-1){
            alive=false;
        }

        Point s=path[last_point_of_path_idx];
        Point f=path[last_point_of_path_idx+1];

        end_of_part_lenth_swured=(f-s).length();

        velocity=f;
        velocity-=s;
        velocity.normalize();

        angle=acos(velocity.x);
        if(velocity.y<0)
            angle=3.1415*2-angle;


    }

}




