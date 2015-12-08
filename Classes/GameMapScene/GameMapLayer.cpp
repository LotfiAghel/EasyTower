#include "GameMapLayer.h"
#include <typeinfo>
#include <typeindex>
#include "GameCore/Tower/Canon.h"
#include "GameCore/Tower/Gun.h"
#include "GameCore/Tower/Rocket.h"
#include "GameCore/Tower/Tesla.h"
#include "Widget/easeoutin.h"
USING_NS_CC;





Scene* GameMapLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameMapLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}




// on "init" you need to initialize your instance
bool GameMapLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    scheduleUpdate();





/////////////////////

    Size backgroundSize = getContentSize();

    scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
    scrollView->setTouchEnabled(true);
    //scrollView->setBounceEnabled(true);
    //scrollView->setBackGroundImageScale9Enabled(true);
    //scrollView->setBackGroundImage("CloseNormal.png");
    scrollView->setContentSize(backgroundSize);

    scrollView->setPosition(Vec2(0,0));


    map_img = ImageView::create("level/ground1.jpg");
    Size s=map_img->getContentSize();

    float t=1.2;
    Size iner=Size(backgroundSize.width*t , t*float(s.height)/s.width* backgroundSize.width);
    scrollView->setInnerContainerSize(iner);








    scrollView->addChild(map_img);





    b=Button::create("CloseNormal.png",
                          "CloseSelected.png"
                           );


    b->setPosition(Point(100,100));
    b->setZOrder(100);
    scrollView->addChild(b);
    b->addClickEventListener(CC_CALLBACK_1(GameMapLayer::paresh, this));


    /*b->runAction(RepeatForever::create(
                     Sequence::create(
                         ScaleTo::create(0.2,1.5),
                         ScaleTo::create(0.2,1),
                         nullptr)
                     ));/**/


    map_img->setScale(t*backgroundSize.width/s.width);

    map_img->setPosition(Vec2(iner.width/2, iner.height/2 ));


    game_map.init();

    addChild(scrollView);


    ////


    par=ParticleSystemQuad::create("BoilingFoam.plist");
    par->setScale(0.5);
    //par->setTotalParticles(100);
    par->setStartColor(Color4F(1,1,0.5,1) );
    par->setEndColor(Color4F(0.2,0.2,0,1) );
    par->setStartColorVar(Color4F(0,0,0,0));
    par->setEndColorVar(Color4F(0,0,0,0));
    par->setPositionType(ParticleSystem::PositionType::RELATIVE);
    par->setPosition(Point(map_img->getContentSize().width/2,map_img->getContentSize().height*4/5));
        //map_img->addChild(par, 10);
    angle=0;
        //par->setTexture( Director::getInstance()->getTextureCache()->addImage("fire.png") );

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label



    char str[100] = {0};
   for(int i = 1; i < 4; i++)
   {






       Vector<SpriteFrame*> animFrames(2);

       sprintf(str, "tower4/impact%i.png",i);
       auto frame = SpriteFrame::create(str,Rect(0,0,128,128)); //we assume that the sprites' dimentions are 40*40 rectangles.
       animFrames.pushBack(frame);


       sprintf(str, "tower4/muzzle%d.png",i);
       frame = SpriteFrame::create(str,Rect(0,0,128,128)); //we assume that the sprites' dimentions are 40*40 rectangles.
       animFrames.pushBack(frame);
       auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
       auto animate = Animate::create(animation);
       animate->retain();
       annn.push_back( animate);
   }

   Vector<SpriteFrame*> animFrames(3);
   for(int i = 1; i < 4; i++)
   {


       sprintf(str, "tower4/t_s%d.png",i);
       auto frame = SpriteFrame::create(str,Rect(0,0,112,51));
       animFrames.pushBack(frame);




   }
   auto animation = Animation::createWithSpriteFrames(animFrames, 0.03f);
   auto animate = Animate::create(animation);
   animate->retain();
   tesla_shot_anim=animate;

    {
       Vector<SpriteFrame*> animFrames(25);
       char str[100] = {0};
       sprintf(str, "tower3/cross.png");
       for(int i = 0; i < 5; i++)for(int j=0; j<5; ++j)
       {

           auto frame = SpriteFrame::create(str,Rect(64*i,64*i,64,64)); //we assume that the sprites' dimentions are 40*40 rectangles.
           animFrames.pushBack(frame);
       }

       auto animation = Animation::createWithSpriteFrames(animFrames, 0.3/25);
       canon_cross = Animate::create(animation);
       canon_cross->retain();
   }



    return true;
}
int t=0;
void GameMapLayer::tesla_anim(Sprite *imageView){
    t++;
    imageView->runAction(Sequence::create(Show::create(),
                                          annn[t%3],
                                            Hide::create(),
                                            DelayTime::create(0.7),
                                            CallFunc::create(std::bind(&GameMapLayer::tesla_anim,this,imageView)),nullptr));
}

void GameMapLayer::createTower(Tower *tower){
    char luncher_name[100] = {0};
    char stand_name[100] = {0};
    if(typeid(*tower) == typeid(Canon) ){
        sprintf(luncher_name, "tower3/canon1.png");
        sprintf(stand_name, "tower3/stand.png");
    }
    if(typeid(*tower) == typeid(Gun) ){
        sprintf(luncher_name, "tower1/canon1.png");
        sprintf(stand_name, "tower1/stand.png");
    }
    if(typeid(*tower) == typeid(Rocket) ){
        sprintf(luncher_name, "tower6/canon1.png");
        sprintf(stand_name, "tower6/stand.png");
    }

    ImageView* stand_img = ImageView::create(stand_name);
    stand_img->setPosition(tower->pos);
    stand_img->setZOrder(1);

    tower->back=stand_img;

    ImageView* luncher_img = ImageView::create(luncher_name);
    luncher_img->setPosition(tower->back->getContentSize()/2);
    luncher_img->setZOrder(2);
    //luncher_img->setScale(0.7);
    stand_img->addChild(luncher_img);
    tower->luncher=(Sprite*)luncher_img;




    //Point c=tower->pos;
    //auto t=EaseOutIn::create( Sequence::create(MoveTo::create(0.5,c+Point(50.0,0)),MoveTo::create(0.5,c),nullptr),2);
     map_img->addChild(stand_img);
    //ee->runAction(RepeatForever::create(t));
     if(typeid(*tower) == typeid(Rocket) ){
         auto s=Sprite::create("tower6/glow1.png");
         s->setPosition(Point(165,65));
         s->setZOrder(1);
         tower->luncher->addChild(s);
         s->runAction(Hide::create());
         tower->shot_efect=s;

     }

    if(typeid(*tower) == typeid(Tesla) ){



        tower->luncher=(Sprite*)luncher_img;
        ImageView* ee = ImageView::create("tower4/canon3.png");
        ee->setPosition(tower->pos);
        ee->setZOrder(1);

        tower->back=ee;
         map_img->addChild(ee);


        Sprite* imageView = Sprite::create("tower4/canon3.png");
        map_img->addChild(imageView);
        imageView->setZOrder(2);
        tower->luncher=imageView;
        imageView->setPosition(tower->pos);


        Sprite* bul = Sprite::create("tower4/bullet1_1.png");

        map_img->addChild(bul);
        bul->setZOrder(3);

        bul->runAction(RepeatForever::create(Sequence::create(Show::create(),
                                                              Spawn::create(ScaleTo::create(0.01,0.5),FadeTo::create(0.01,255),nullptr),
                                                              Spawn::create(ScaleTo::create(0.5,1),FadeTo::create(0.5,255.0/4),nullptr),
                                                              Hide::create(),DelayTime::create(2),nullptr)));
        bul->setPosition(tower->pos);
        imageView->runAction(Sequence::create(
                                 DelayTime::create(0.7),
                                 CallFunc::create(std::bind(&GameMapLayer::tesla_anim,this,imageView)),
                                 nullptr));



        auto s=Sprite::create("tower4/t_s1.png");
        s->setPosition(Point(100+s->getContentSize().width/2,65));
        s->setZOrder(1);
        tower->back->addChild(s);
        //s->runAction(Hide::create() );
        //s->runAction(RepeatForever::create(tesla_shot_anim));
        tower->shot_efect=s;


     }
    auto b=Button::create("empty.png" );

    auto upgrade = Button::create("CloseNormal.png",
                           "CloseSelected.png"
                            );

    auto sell = Button::create("CloseNormal.png",
                           "CloseSelected.png"
                            );


    b->setPosition(tower->back->getContentSize()/2);
    tower->back->addChild(b,10,1);
    tower->back->addChild(upgrade,10,2);
    tower->back->addChild(sell,10,3);
    upgrade->setScale(2);
    sell->setScale(2);
    b->setScale(2);
    upgrade->addClickEventListener([this,tower](Ref* pSender) {
        cerr<<"upgrade "<<tower->level<<endl;
        Point p=map_img->convertToNodeSpace(Point(100,100));
        Canon *c=new Canon(game_map,p);
        c->alive=true;
        game_map.towers.push_back(c);
        if(tower->level==Tower::level2){
            tower->level=Tower::level3;
            tower->upgrade_signal=true;
        }
        if(tower->level==Tower::level1){
            tower->level=Tower::level2;
            tower->upgrade_signal=true;
        }

    } );
    sell->addClickEventListener([tower](Ref* pSender) {
        tower->alive=false;

    } );


    b->addClickEventListener([this,stand_img,b,upgrade,sell](Ref* pSender) {
        close_all_upgrade_pop_up();
        upgrade->stopAllActions();
        sell->stopAllActions();
        upgrade->setRotation(-180);
        sell->setRotation(-180);
        upgrade->setPosition(b->getPosition());
        sell->setPosition(b->getPosition());


        upgrade->runAction(RotateTo::create(0.3,0));
        sell->runAction(RotateTo::create(0.3,0));
        upgrade->runAction(Sequence::create( Show::create(),MoveTo::create(0.3,Point(b->getPosition().x,b->getPosition().y+100)),nullptr));
        sell->runAction(Sequence::create(Show::create(),MoveTo::create(0.3,Point(b->getPosition().x+100,b->getPosition().y)),nullptr));


    } );

}
void GameMapLayer::removeTower(Tower *tower){
    if(tower->back!=nullptr)
    tower->back->removeFromParent();
    tower->luncher=nullptr;
    tower->back=nullptr;


}
void GameMapLayer::updateTower(Tower *tower){
    //tower->back->setPosition(tower->pos);
    if(! tower->alive)
        return ;

    tower->luncher->setRotation(-tower->angle*180/3.14);

    float shock_time=0.05;
    float shock_dist=10;
    if(typeid(*tower) == typeid(Canon) ){
        shock_time=0.05;

    }
    if(typeid(*tower) == typeid(Gun) ){
        shock_time=0.01;
        shock_dist=4;
        if(tower->upgrade_signal &&  tower->level==Tower::level2){
            //tower->luncher->setTexture("tower1/canon2.png");
            cerr<<"load2"<<endl;
            tower->luncher->removeFromParent();

            ImageView* imageView = ImageView::create("tower1/canon2.png");
            imageView->setPosition(tower->back->getContentSize()/2);
            imageView->setZOrder(2);
            tower->back->addChild(imageView);
            tower->luncher=(Sprite*)imageView;

            tower->upgrade_signal=false;
        }
        if(tower->upgrade_signal && tower->level==Tower::level3){
            cerr<<"load3"<<endl;
            tower->luncher->removeFromParent();

            ImageView* imageView = ImageView::create("tower1/canon3.png");
            imageView->setPosition(tower->back->getContentSize()/2);
            imageView->setZOrder(2);
            tower->back->addChild(imageView);
            tower->luncher=(Sprite*)imageView;

            cerr<<"load3"<<endl;
            tower->upgrade_signal=false;
        }


    }
    if(typeid(*tower) == typeid(Rocket) ){
        shock_time=0.05;
    }

    if(tower->shot_signal && typeid(*tower) != typeid(Tesla) ){
        tower->shot_signal=false;
        Point c=tower->back->getContentSize()/2;
        float angle=tower->angle;
        Point v=Point(cos(angle),sin(angle))*(-shock_dist);
        auto t=EaseOutIn::create(Sequence::create(MoveTo::create(shock_time,c+v),MoveTo::create(shock_time,c),nullptr),2);
        tower->luncher->runAction(t);
        if(typeid(*tower) == typeid(Rocket) )
            tower->shot_efect->runAction(Sequence::create(Show::create(),DelayTime::create(0.12),Hide::create(),nullptr));

    }
    if(tower->shot_signal && typeid(*tower) == typeid(Tesla) && tower->target_idx>-1){
        tower->shot_efect->runAction(Sequence::create(Show::create(),tesla_shot_anim,Hide::create(),nullptr));
        tower->shot_signal=false;
        float size;
        float angle=find_angle_and_size(tower->pos,game_map.units[tower->target_idx]->pos,size);
        tower->back->setRotation(-angle*180/3.14);
        tower->shot_efect->setScaleX(size/280);

        //tower->shot_efect->setPosition((game_map.units[tower->target_idx]->pos-tower->pos)/2);
        cerr<<"tesla shot"<<endl;
    }

}

void GameMapLayer::createMilse(Misle *misle){
    if(typeid(*misle) == typeid(CanonShot) ){
        Vector<SpriteFrame*> animFrames(4);
        char str[100] = {0};
        for(int i = 1; i < 4; i++)
        {
            sprintf(str, "tower3/bullet1_%d.png",i);
            auto frame = SpriteFrame::create(str,Rect(0,0,108,59)); //we assume that the sprites' dimentions are 40*40 rectangles.
            animFrames.pushBack(frame);
        }

        auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        auto animate = Animate::create(animation);
        Sprite* imageView = Sprite::create("tower3/bullet1_1.png");
        imageView->runAction(RepeatForever::create(animate));
        map_img->addChild(imageView);
        misle->g=imageView;


    }
    if(typeid(*misle) == typeid(GunShot) ){
        Sprite* imageView = Sprite::create("tower1/bullet1_1.png");
        imageView->setZOrder(1);
        map_img->addChild(imageView);
        misle->g=imageView;
    }
    if(typeid(*misle) == typeid(RocketShot) ){
        Sprite* imageView = Sprite::create("tower6/bullet1_1.png");
        imageView->setZOrder(1);
        map_img->addChild(imageView);
        misle->g=imageView;
    }




}

void GameMapLayer::update(float dt){
    cerr<<"lllllllll"<<endl;
    angle+=dt*360;

    //par->setRotation(angle);
   // par->setAngle(angle);
   // par->setPosition(Point(500,sin(angle/360)*180+360));

    game_map.update(dt);

    for(int i=0; i<game_map.units.size();++i)
        if(game_map.units[i]->g!=nullptr){
            game_map.units[i]->g->setPosition(game_map.units[i]->pos);
            game_map.units[i]->g->setRotation(-game_map.units[i]->angle*180/3.14);
        }else
        {
            char str[100] = {0};
            sprintf(str, "enemy1/1.png",game_map.units[i]->id);
            Sprite* imageView = Sprite::create(str);
            Vector<SpriteFrame*> animFrames(5);

            for(int j = 1; j < 5; j++)
            {

                sprintf(str, "enemy%d/%d.png",1,j);
                auto frame = SpriteFrame::create(str,Rect(0,0,imageView->getTexture()->getPixelsWide(),imageView->getTexture()->getPixelsHigh())); //we assume that the sprites' dimentions are 40*40 rectangles.
                animFrames.pushBack(frame);
            }

            auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
            auto animate = Animate::create(animation);/**/
            //animate->







            imageView->runAction(RepeatForever::create(animate));

            //imageView->setScale(0.5);
            map_img->addChild(imageView);
            imageView->setPosition(game_map.units[i]->pos);
            game_map.units[i]->g=imageView;


        }

    for(int i=0; i<game_map.towers.size();++i){
        if(game_map.towers[i]->alive){
            if (game_map.towers[i]->luncher==nullptr)
                createTower(game_map.towers[i]);
            updateTower(game_map.towers[i]);
        }else{
            removeTower(game_map.towers[i]);
        }


    }


    cerr<<"update graphic misle<<"<<endl;
    for(int i=0; i<game_map.misels.size();++i){
        Misle *misle=game_map.misels[i];
        if(misle->state==Misle::in_move && misle->alive)
        {
            if(misle->g==nullptr)
                createMilse(misle);
            misle->g->setPosition(misle->pos);
            misle->g->setRotation(-misle->angle*180/3.14);
            Point p=Point(-misle->g->getContentSize().width*0.1/2,0);
            Point p2=Point(cos(-misle->angle),sin(misle->angle));
            Point p3;
            p3.x=p.x*p2.x-p.y*p2.y;
            p3.y=p.x*p2.y+p.y*p2.x;

         }else if(misle->state==Misle::ded){
                //misle->g->removeFromParent();
                //misle->g=nullptr;
            }else{
                if(misle->cross_signal && misle->g!=nullptr){
                    auto g=Sprite::create();

                    map_img->addChild(g);
                    g->setPosition(misle->pos);
                    g->runAction(canon_cross);
                    g->runAction(FadeOut::create(0.3));
                    misle->cross_signal=false;
                }
        }

    }
    cerr<<"update graphic misle>>"<<endl;
}

void GameMapLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void GameMapLayer::paresh(Ref* pSender){
    cerr<<"paresh"<<endl;
    b->runAction(MoveBy::create(3,Point(0,100)));
}
