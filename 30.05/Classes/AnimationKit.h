#pragma once
#include "cocos2d.h"
#include "ObjectKeeper.h"

class CAnimationKit : public cocos2d::Object
{
public:
	static CAnimationKit* create(cocos2d::String const &animPath, cocos2d::Rect const &rect, int countFrames, bool repeat, double delay);
	bool init(cocos2d::String const &animPath, cocos2d::Rect const &rect, int countFrames, bool repeat, double delay);

	cocos2d::ActionInterval *getAction()const;
private:
	ObjectKeeper<cocos2d::ActionInterval> m_action;
};