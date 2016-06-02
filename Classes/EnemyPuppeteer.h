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

	void update(cocos2d::Vec2 const &playerPos, cocos2d::Rect const &playerRect, bool playerIsAttacked);
private:
	void init(cocos2d::Vec2 const &puppetPos);
	void updateTimer(float dt);
private:
	int m_timer = 0;
	ObjectKeeper<CEnemy> m_enemy;
	ObjectKeeper<CLifeBar> m_lifebar;
	mutable bool m_enemyIsAttack = false;
};