#include "AnimationKit.h"

USING_NS_CC;

CAnimationKit * CAnimationKit::create(std::string const & animPath, cocos2d::Rect const & rect, int countFrames, bool repeat, double delay)
{
	CAnimationKit *pAnimKit = new (std::nothrow) CAnimationKit();
	if (pAnimKit && pAnimKit->init(animPath, rect, countFrames, repeat, delay)) 
	{
		pAnimKit->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pAnimKit);
	}
	return pAnimKit;
}

bool CAnimationKit::init(std::string const & animPath, cocos2d::Rect const & rect, int countFrames, bool repeat, double delay)
{
	Vector<SpriteFrame*> animFrames(countFrames);
	for (unsigned i = 0; i < countFrames; ++i)
	{
		auto frame = SpriteFrame::create(animPath, Rect(i * rect.getMinX(), rect.getMinY(), rect.size.width, rect.size.height));
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, delay);
	m_action = Animate::create(animation);
	if (repeat)
	{
		m_action = RepeatForever::create(m_action);
	}
	return true;
}

cocos2d::ActionInterval * CAnimationKit::getAction() const
{
	return m_action;
}

