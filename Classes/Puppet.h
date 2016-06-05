#pragma once
#include "AnimationKit.h"
#include "ObjectKeeper.h"

enum class PuppetAnimationType
{
	stay,
	move,
	die,
	meleeAttack,

	knivesOperate,
	frostMageSwitch,
	fireMageSwitch,
	arcaneMageSwitch,
	castFrostBalt,
	castFireBalt,
	castArcanBlast,
};

enum class PuppetState
{
	moveLeft = -1,
	moveRight = 1,
	stay,
	jump,
	attack
};

class CPuppet
	: public cocos2d::Node
{
public:
	const cocos2d::Vec2 &getPosition()const final;
	cocos2d::Rect getBoundingBox()const final;
	int getHealthCount()const;
	PuppetState const &getState()const;
	bool isAlive()const;
	void hasDamaged(int healthCount);
	void move(PuppetState const &state);
	virtual void update() = 0;
	virtual void action(PuppetState const &state) = 0;
protected:
	void jump();
	void setAnimation(CAnimationKit *kit);
	cocos2d::Vec2 getVelocity()const;
	void setVelocity(cocos2d::Vec2 const &velocity);
	virtual bool isCanJump()const;
protected:
	cocos2d::Sprite* m_puppetSprite = nullptr;
	cocos2d::Sprite* m_phantomeSprite = nullptr;
	bool m_isJump = false;
	cocos2d::Vec2 jumpPos = { 0, 0 };
	int m_health = 100;
	float m_velocityX = 200;
	bool m_isAlive = true;
	PuppetState m_state;
	std::map<const PuppetAnimationType, ObjectKeeper<CAnimationKit>> m_animations;
};