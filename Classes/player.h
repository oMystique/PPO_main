#pragma once
#include "Entities.h"
#include "AnimationKit.h"
#include <map>

enum class PlayerState
{
	moveLeft = -1,
	stay = 0,
	moveRight = 1,
	fight,
	jump,
	none
};

enum class PlayerAnimationType
{
	run,
	stay,
	knivesOperate,
	knivesAttack,
	frostMageSwitch,
	fireMageSwitch,
	arcaneMageSwitch,
};

enum class PlayerFightType
{
	melee,
	magic
};

enum class PlayerMagicType
{
	arcan,
	fire,	
	frost
};

class CPlayer 
	: public cocos2d::Node 
{
public:
	static CPlayer * create();

	void idle();
	void knivesOperate();
	void attack();
	void frostOperate();
	void fireOperate();
	void arcaneOperate();

	void setPosition(cocos2d::Vec2 const &pos);
	int getHealthCount()const;
	int getManaCount()const;
	const cocos2d::Vec2 &getPosition()const override;
	cocos2d::Rect getBoundingBox()const override;

	void action(PlayerState const &state);
	void update();

	bool isAttack()const;

	void hasDamaged(int healthCount);
	void hasBurnedMana(int manaCount);
private:
	void move(PlayerState const &state);
	void jump();

	cocos2d::Vec2 getVelocity()const;
	void setVelocity(cocos2d::Vec2 const &velocity);

	void pushAnimations();
	void setAnimation(CAnimationKit *kit);
	void initPlayer();

private:
	CPlayer* operator=(CPlayer && player) = delete;

	ObjectKeeper<cocos2d::Sprite> m_playerSprite = nullptr;
	ObjectKeeper<cocos2d::Sprite> m_phantomeSprite = nullptr;

	PlayerState m_state = PlayerState::stay;
	cocos2d::Vec2 m_jumpPos = { 0, 0 };

	mutable bool m_isMeleeAttack = false;

	int m_health = 100;
	int m_mana = 100;

	std::map<const PlayerAnimationType, ObjectKeeper<CAnimationKit>> m_animations;
};