#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

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


class GameMap;
class Path;
class Unit;
class Tower;

class CC_DLL EaseOutIn : public EaseRateAction
{
public:
    /** Creates the action with the inner action and the rate parameter */
    static EaseOutIn* create(ActionInterval* action, float rate);

    // Overrides
    virtual void update(float time) override;
    virtual EaseOutIn* clone() const  override;
    virtual EaseOutIn* reverse() const  override;

CC_CONSTRUCTOR_ACCESS:
    EaseOutIn() {}
    virtual ~EaseOutIn() {}

private:
    CC_DISALLOW_COPY_AND_ASSIGN(EaseOutIn);
};

class RoadSprite : public cocos2d::Sprite{
public:
     cocos2d::CustomCommand _drawCommand;
    void drawSkeleton (const Mat4 &transform, uint32_t transformFlags) {
        getGLProgramState()->apply(transform);
        cerr<<"ca"<<endl;
        auto center1_tex= Director::getInstance()->getTextureCache()->addImage("tail_tex.png");

        GL::bindTexture2D(center1_tex->getName());
        GL::bindVAO(0);
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
        glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORDS);


        cocos2d::V2F_C4B_T2F _vertices[]={{{0,0},{255,255,255,255},{0,0}},
                                         {{0,720},{255,255,0,255},{0,0.9}},
                                         {{720,0},{0,0,255,255},{0.9,0}},
                                         {{720,720},{0,0,0,0},{0.9,0.9}}
                                        };

        //Point vertices[]={{0,0},{0,400.0f},{400.0f,0},{400,400}};
        //Color4B colors[]={{255,255,255,120},{255,0,0,120},{255,255,0,120},{255,255,0,120}};
        //Point texCoords[]={{0,0},{0,0.9},{0.9,0},{0.9,0.9}};
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), &_vertices[0].vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), &_vertices[0].colors);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), &_vertices[0].texCoords);


        GLushort _triangles[]={0,1,2,1,2,3};
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_SHORT, _triangles);

        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 4);



        CHECK_GL_ERROR_DEBUG();/**/

        return ;






    }
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t transformFlags)
    {

        //_glProgram->use();
        // Tell Cocos2D to pass the CCNode's position/scale/rotation matrix to the shader (well, that's what Ray says!)
        //_glProgram->setUniformsForBuiltins();
        //getGLProgramState()->apply(transform);
        //game_core.draw(Point(0,0));


        /*_drawCommand.init(100);
        _drawCommand.func = CC_CALLBACK_0(RoadSprite::drawSkeleton,this,transform, transformFlags);
        _drawCommand.setType(RenderCommand::Type::CUSTOM_COMMAND );
        cerr<<(int)_drawCommand.getType()<<"  "<<(int)RenderCommand::Type::CUSTOM_COMMAND<<endl;
        renderer->addCommand(&_drawCommand);
        cerr<<(int)_drawCommand.getType()<<"  "<<(int)RenderCommand::Type::CUSTOM_COMMAND<<endl;/**/
        /**/



    }
    bool init () {


        _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
        setOpacityModifyRGB(true);

        setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
        scheduleUpdate();
        return true;
    }

    CREATE_FUNC(RoadSprite);
};

class HelloWorld : public cocos2d::Layer
{
public:
    ui::ScrollView* scrollView ;
    ImageView* map_img;
    ParticleSystemQuad* par;
    float angle;
    GameMap game_map;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    vector< Animate* > annn;
    Animate *tesla_shot_anim;
    Animate *canon_cross=nullptr;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void createTower(Tower *tower);
    void updateTower(Tower *tower);
    void createMilse(Misle *misle);
    void tesla_anim(Sprite *imageView);
    void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    Button *b;
    void paresh(Ref* pSender);
    void pop_up(Ref* pSender,Tower *t){
       // Button *b= (Button*)(((Sprite*)pSender)->getChildByTag(1));
        //b->runAction(ScaleTo::create(1,10));

    }
    void close_all_upgrade_pop_up(){
        //getChildByTag(2)
        for(int i=0; i<game_map.towers.size(); ++i)
        if(game_map.towers[i]->back!=nullptr){
            Tower *tower=game_map.towers[i];
            Sequence *s=Sequence::create(
                        Spawn::create(MoveTo::create(0.1,tower->back->getContentSize()/2),
                                      RotateTo::create(0.1,-180),nullptr),
                        Hide::create(),
                        nullptr);
            tower->back->getChildByTag(2)->runAction(s);
            tower->back->getChildByTag(3)->runAction(s->clone());
        }
    }
    void removeTower(Tower *tower);


};

#endif // __HELLOWORLD_SCENE_H__
