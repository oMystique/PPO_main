#pragma once
#include "Entities.h"
#include "AnimationKit.h"
#include "Puppet.h"

class CEnemy
	: public CPuppet
{
public:
	static CEnemy * create(cocos2d::Vec2 const &pos);
	bool m_isPursuitTarget = false;
	void action(PuppetState const &state)override;
	void update()override;
	void attackedByFrost();
	void attackedByFire();
private:
	static PuppetState SwitchMoveDirection(PuppetState const &state);
	void die();
	void attack();
	void dieTimer(float dt);
	void pushAnimations();
	void initEnemy(cocos2d::Vec2 const &pos);
	void updateDebuffTimer(float dt);
	void collisionDetectEvents();
	void unscheduleDebuffTimer();
	bool isCanJump()const override;
private:
	int m_debuffTimer = 0;
	int m_dieTimer = 0;
};

