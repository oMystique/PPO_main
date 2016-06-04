#pragma once
#include "player.h"

class CPlayerPuppeteer
	: public cocos2d::Node
{
public:
	static CPlayerPuppeteer * create(cocos2d::Vec2 const &playerPos);

	CPlayer * getPuppet()const;
	const cocos2d::Vec2 &getPuppetPos()const;
	void update(cocos2d::Vec2 const &controllerPosition);

	bool isAttack() const;

	void damagePuppet(int healthCount);
	void burnPuppetMana(int manaCount);

	bool puppetIsNeedBonus(int bonusTag);
private:
	void init(cocos2d::Vec2 const &playerPos);
private:
	ObjectKeeper<CPlayer> m_player;
};
