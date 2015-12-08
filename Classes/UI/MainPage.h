#ifndef MAINPAGE_H
#define MAINPAGE_H


#include "cocos2d.h"
#include "vector"
#include "cocos2d.h"
#include "iostream"

#include "ui/CocosGUI.h"
#include "GameCore/Tower/Tower.h"
#include "GameCore/Unit/Unit.h"
#include "GameCore/BaseGameMap.h"
using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class MainPage : public cocos2d::Layer
{
public:

    struct UI{
        ui::ScrollView* scrollView ;
        ImageView* map_img;
    };


    static cocos2d::Scene* createScene();


    virtual bool init();
    CREATE_FUNC(MainPage);
};

#endif // MAINPAGE_H
