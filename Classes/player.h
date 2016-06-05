#pragma once
#include "Entities.h"
#include "AnimationKit.h"
#include <map>
#include "Puppet.h"

class CPlayer 
	: public CPuppet 
{
public:
	static CPlayer * create(cocos2d::Vec2 const &pos);

	void idle();
	void knivesOperate();
	void attack();
	void frostOperate();
	void fireOperate();
	void arcaneOperate();
	void castFrostBalt();
	void castFireBalt();
	void castArcanBlast();

	void useBonus(int bonusTag);

	int getManaCount()const;

	void action(PuppetState const &state)override;
	void update()override;

	bool isAttack()const;

	void hasBurnedMana(int manaCount);
private:

	void castTimer(float dt);
	void pushAnimations();
	void initPlayer(cocos2d::Vec2 const &pos);

private:
	CPlayer* operator=(CPlayer && player) = delete;
	mutable bool m_isMeleeAttack = false;
	int m_mana = 100;
	int m_castTimer = 0;
	int m_interruptionCastTime = 0;
};