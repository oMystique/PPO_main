#pragma once
#include <cocos2d.h>

class CLifeBar
	: public cocos2d::Layer
{
public:
	static CLifeBar * create(cocos2d::Point const &backgroundPos, cocos2d::Point const &hpPos, cocos2d::Point const &manaPos);
	void update(int health, int mana);
private:
	void initLifeBar(cocos2d::Point const &backgroundPos, cocos2d::Point const &hpPos, cocos2d::Point const &manaPos);
private:
	cocos2d::Sprite *m_background;
	cocos2d::Sprite *m_health;
	cocos2d::Sprite *m_mana;
};