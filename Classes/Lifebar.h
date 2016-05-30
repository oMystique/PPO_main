#pragma once
#include <cocos2d.h>

class CLifeBar
	: public cocos2d::Layer
{
public:
	CLifeBar() = default;
	static CLifeBar * create(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, cocos2d::Vec2 const &manaPos);
	void update(int health, int mana);
	~CLifeBar() = default;
private:
	void initLifeBar(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, cocos2d::Vec2 const &manaPos);
private:
	cocos2d::Sprite *m_background;
	cocos2d::Sprite *m_health;
	cocos2d::Sprite *m_mana;
};