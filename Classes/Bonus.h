#pragma once
#include <cocos2d.h>

class CBonus :
	public cocos2d::Sprite
{
public:
	enum BonusType
	{
		health,
		mana,
	};

	static CBonus * create(cocos2d::Vec2 const &pos);
	void update(float dt)override;
	void setPhysicsBodyForBonus();
private:
	bool init(cocos2d::Vec2 const &pos);
private:
	float m_soarStartPosY = 0;
	bool m_isAlive = true;
};