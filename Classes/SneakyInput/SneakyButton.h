#ifndef __SNEAKY_BUTTON_H__
#define __SNEAKY_BUTTON_H__

#include "cocos2d.h"
#include "boost/signals2.hpp"

class CPlayer;

USING_NS_CC;

class SneakyButton : public Node
{
	typedef boost::signals2::signal<void()> OnClick;
	typedef boost::signals2::connection Connection;
public:
	OnClick m_onClick;
protected:
	Point center;
	Rect bounds;

	CC_SYNTHESIZE(bool, status, Status);
	CC_SYNTHESIZE(bool, active, IsActive);
	CC_SYNTHESIZE(bool, value, Value);
	CC_SYNTHESIZE(bool, isHoldable, IsHoldable);
	CC_SYNTHESIZE(bool, isToggleable, IsToggleable);
	CC_SYNTHESIZE(float, rateLimit, RateLimit);
	CC_SYNTHESIZE(float, radiusSq, RadiusSq);

	CC_SYNTHESIZE_READONLY(float, radius, Radius);

	//Public methods
	bool initWithRect(Rect rect);
	void limiter(float delta);
	void setRadius(float r);
	static bool onTouchBegan(Touch *touch, Event *event);
	static void onTouchMoved(Touch *touch, Event *event);
	static void onTouchEnded(Touch *touch, Event *event);
	static void onTouchCancelled(Touch *touch, Event *event);

	void touchDelegateRelease();
	void touchDelegateRetain();

};

#endif