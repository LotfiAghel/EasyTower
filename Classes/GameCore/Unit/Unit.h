#ifndef TOWER_UNIT_H
#define TOWER_UNIT_H
#include "../all.h"
class Unit:public BoardObject{
    float health;
public:
    const GameCore &game_map;
    Path path;
    float distance_of_walk;

    int last_point_of_path_idx;

    float defult_speed;
    float slow_time;


    float speed;


    Point velocity;
    float angle;

    float end_of_part_lenth_swured;
    float go_next_from_last;
    //Path path;
    int id;

    Sprite *g;

    Unit(const GameCore &g_p,const Path &p);
    virtual void  update(float dt);
    virtual void take_damage(float damage){
        health-=damage;

    }
    void set_health(float h){
        health=h;
    }

};



#endif
