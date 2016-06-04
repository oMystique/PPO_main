#pragma once
#include "Enemy.h"
#include "Lifebar.h"

class CEnemyPuppeteer
	: public cocos2d::Node
{
public:
	CEnemyPuppeteer() = default;
	static CEnemyPuppeteer * create(cocos2d::Vec2 const &playerPos);

	CEnemy * getPuppet()const;

	bool isAttack()const;
	void puppetHasAttackedByMagic(int magicType);
	void damagePuppet(int healthCount);

	bool hasPuppet()const;

	const cocos2d::Vec2 &getPuppetPos()const;
	void interactWithPlayer(cocos2d::Vec2 const &playerPos, cocos2d::Rect const &playerRect, bool playerIsAttacked);
	void update();
private:
	void init(cocos2d::Vec2 const &puppetPos);
	void updateAttackTimer(float dt);
	void unscheduleAttackTimer();
	void scheduleAttackTimer();
	void pursuitTarget(cocos2d::Vec2 const &playerPos);
	void attackTarget(bool playerIsAttacked);
private:
	int m_attackTimer = 0;
	ObjectKeeper<CEnemy> m_enemy;
	ObjectKeeper<CLifeBar> m_lifebar;
	mutable bool m_enemyIsAttack = false;
};