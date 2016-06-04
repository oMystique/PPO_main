#pragma once
#include "cocos2d.h"

class CSpellObject
	: public cocos2d::Node
{
public:
	static CSpellObject * create(float velocityX, cocos2d::Vec2 const &spawnPos);
	void update(float dt)override;
private:
	bool init(float velocityX, cocos2d::Vec2 const &spawnPos);
private:
	cocos2d::Sprite * m_sprite;
	cocos2d::Sprite * m_phantomeSprite;
};