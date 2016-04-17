
#pragma once
#include "cocos2d.h" 

using namespace cocos2d;

class Joystick : public CCLayer
{

public:

    virtual bool init();  
    CCPoint getVelocity() {return velocity;}
    CREATE_FUNC(Joystick);

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) override;
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) override;
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) override;

private:

    CCPoint kCenter;
    CCSprite *thumb;
    bool isPressed;

    CCPoint velocity;

    void updateVelocity(CCPoint point);
    void resetJoystick();
    bool handleLastTouch();
};
