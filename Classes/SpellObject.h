#pragma once
#include "cocos2d.h"

class CSpellObject
	: public cocos2d::Node
{
public:
	static CSpellObject * create(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask);
	void update(float dt)override;
private:
	bool init(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask);
private:
	cocos2d::Sprite * m_sprite;
	cocos2d::Sprite * m_phantomeSprite;
};