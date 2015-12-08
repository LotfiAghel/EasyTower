#ifndef TOWER_ALL_H
#define TOWER_ALL_H

#include "cocos2d.h"
#include "vector"
#include "cocos2d.h"
#include "iostream"

#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;


struct BoardObject{
    static int id_count;
    int id;
    Point pos;
    bool alive;
    BoardObject(){
        id=id_count++;
    }
};

class GameCore;
class Path;
class Unit;
class Tower;
class Misle;
float angle_range_0_2pi(float x);
float angle_range_npi_pi(float x);
float find_angle(const Point &p);
float find_angle_and_size(const Point a,const Point &b,float &size);


class Path : public vector<Point> {};


#endif
