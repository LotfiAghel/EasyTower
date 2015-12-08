#ifndef EASEOUTIN_H
#define EASEOUTIN_H

#include "cocos2d.h"
#include "vector"
#include "cocos2d.h"
#include "iostream"

#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;


class GameCore;
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


#endif // EASEOUTIN_H

