
#ifndef  _TOWER_TOWER_H_
#define  _TOWER_TOWER_H_


#include "../all.h"


class Misle:public BoardObject{
public:
    const GameMap &game_map;
    float angle;
    float max_angle_speed;
    float max_range;
    int target_idx;
    Point target_pos;
    enum{
        in_lunch=1,
        in_move=2,
        in_cross=3,
        in_miss=4,
        ded=5,
    }state;
    float speed;
    bool cross_signal;
    float cross_time;
    bool miss_signal;
    float miss_time;
    float lunch_time=0;
    float lunch_start_time=0;

    Point velocity;
    bool alive;
    Sprite *g;
    Tower *tower;
    ParticleSystem *dud;
    Misle(const GameMap &g_p,Tower *tower,int idx);
    virtual void update(float dt);
};



class Tower:public BoardObject{
public:
    GameMap &game_map;

    float angle;
    float angle_speed;

    float time_waiting_to_be_ready;

    int misle_lunch_ted;
    float last_time;
    float range=300;
    enum{
        level1=1,
        level2=2,
        level3=3
    } level;

    bool is_focused_on_target;
    int target_idx;
    Tower(GameMap &g_p,const Point &p):BoardObject(),game_map(g_p),time_waiting_to_be_ready(0){
        pos=p;
        luncher=nullptr;
        misle_lunch_ted=0;
        target_idx=-1;
        level=level1;
        upgrade_signal=true;
        alive=true;
    }
    bool shot_signal;
    bool upgrade_signal;
    Sprite *luncher;
    ImageView *back;
    Sprite *shot_efect;
    virtual int find_target();
    virtual void update(float dt);
    virtual bool can_attack();
     virtual void  find_angle(float dt);
};



#endif
