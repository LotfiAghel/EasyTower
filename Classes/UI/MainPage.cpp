#include "MainPage.h"
Scene* MainPage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainPage::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool MainPage::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    return true;
}
