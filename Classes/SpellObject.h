#pragma once
#include "cocos2d.h"

class CSpellObject
	: public cocos2d::Node
{
public:
	static CSpellObject * create(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask, std::string const &dieImagePath);
	void update(float dt)override;
private:
	bool init(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask, std::string const &dieImagePath);
	void die();
	void dieTimer(float dt);
private:
	std::string m_dieImagePath;
	float m_dieTimer = 0;
	cocos2d::Sprite * m_sprite;
	cocos2d::Sprite * m_phantomeSprite;
};