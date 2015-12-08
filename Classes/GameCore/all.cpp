#include "all.h"

int BoardObject::id_count=1;
float angle_range_0_2pi(float x){
    if(x<0)
        x+=int(x/3.1415/2)*2*3.1415 + 20*3.1415;
    x-=int(x/3.1415/2)*2*3.1415;
    return x;

}
float angle_range_npi_pi(float x){
    x=angle_range_0_2pi(x);
    if(x>3.1415)
        x=x-2*3.1415;
    return x;

}
float find_angle(const Point &p){
    Point f=p;
    f.normalize();
    float angle=acos(f.x);
    if(f.y<0)
        angle=3.1415*2-angle;
    return angle;
}
float find_angle_and_size(const Point a,const Point &b,float &size){
    Point d=b;
    d-=a;
    size=d.length();
    d.normalize();
    return find_angle(d);
}
