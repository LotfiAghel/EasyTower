
#include "Tesla.h"
#include "../BaseGameMap.h"
#include "../all.h"

#include "../Unit/Unit.h"
void Tesla::update(float dt){
    time_waiting_to_be_ready-=dt;
    if(time_waiting_to_be_ready<0)
        target_idx=find_target();



    if(time_waiting_to_be_ready<0 && target_idx!=-1 ){
        game_map.units[target_idx]->speed=game_map.units[target_idx]->defult_speed/10;
        game_map.units[target_idx]->slow_time=1;
        game_map.units[target_idx]->take_damage(40);
        shot_signal=true;
        time_waiting_to_be_ready=0.5;
    }


    //find_angle(dt);


}


int Tesla::find_target(){
    float rang2=range*range;
    float mind_sq=range*range;

    int mini=-1;
    for(int i=0; i<game_map.units.size();++i){
        float tmp=(game_map.units[i]->pos-pos).lengthSquared();
        if(tmp<rang2 && (mini==-1 || game_map.units[mini]->slow_time>game_map.units[i]->slow_time)){
            mind_sq=tmp;
            mini=i;

        }
    }
    target_idx=mini;
    return mini;

}

