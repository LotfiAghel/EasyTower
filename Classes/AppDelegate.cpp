#include "AppDelegate.h"
#include "GameMapScene/GameMapLayer.h"
#include "UI/MainPage.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        glview->setFrameSize(1280,720);
        director->setOpenGLView(glview);
    }


    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameMapLayer::createScene();

    // run
    director->runWithScene(scene);

    if(false){
        Director *director = new (std::nothrow) DisplayLinkDirector();
        CCASSERT(director, "FATAL: Not enough memory");
        director->init();


        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::create("ui des");
            director->setOpenGLView(glview);
        }

        // turn on display FPS
        director->setDisplayStats(true);

        // set FPS. the default value is 1.0/60 if you don't call this
        director->setAnimationInterval(1.0 / 60);

        // create a scene. it's an autorelease object
        auto scene = GameMapLayer::createScene();

        // run
        director->runWithScene(scene);
    }


    return true;
}
bool AppDelegate::applicationDidFinishLaunching2() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
    //glview->setDesignResolutionSize(1200,720,ResolutionPolicy::NO_BORDER);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainPage::createScene();

    // run
    director->runWithScene(scene);

    return true;
}
// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
