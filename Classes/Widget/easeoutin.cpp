#include "easeoutin.h"
EaseOutIn* EaseOutIn::create(ActionInterval *action, float rate)
{
    EaseOutIn *easeInOut = new (std::nothrow) EaseOutIn();
    if (easeInOut)
    {
        if (easeInOut->initWithAction(action, rate))
        {
            easeInOut->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(easeInOut);
        }
    }

    return easeInOut;
}

EaseOutIn* EaseOutIn::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) EaseOutIn();
    a->initWithAction(_inner->clone(), _rate);
    a->autorelease();
    return a;
}
float easeOutIn(float time, float rate)
{
    time *= 2;
    if (time < 1)
    {
        return 0.5f * (1-powf(1-time, rate));
    }
    else
    {
        return (0.5f + 0.5f * powf(time-1, rate));
    }
}
void EaseOutIn::update(float time)
{
    _inner->update(easeOutIn(time, _rate));
}

// InOut and OutIn are symmetrical
EaseOutIn* EaseOutIn::reverse() const
{
    return EaseOutIn::create(_inner->reverse(), _rate);
}



