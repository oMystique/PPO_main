#pragma once
#include "Entities.h"
#include "AnimationKit.h"

USING_NS_CC;

enum class PlayerState
{
	moveLeft,
	moveRight,
	stay,
	fight,
	none
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

class CPlayer : public CEntities {
public:

	static CPlayer * create();
	void move(PlayerState const &state);
	void idle();
	void knivesOperate();
	void attack();
	void frostOperate();
	void fireOperate();

	void update() override;
private:
	void setAnimation(CAnimationKit *kit);
	void initPlayer();
private:
	~CPlayer();
	ObjectKeeper<CAnimationKit> m_idleAnimation;
	ObjectKeeper<CAnimationKit> m_runAnimation;
	ObjectKeeper<CAnimationKit> m_kniveOpAnimation;
	ObjectKeeper<CAnimationKit> m_attackAnimation;
	ObjectKeeper<CAnimationKit> m_animFrost;
	ObjectKeeper<CAnimationKit> m_animFire;

	PlayerState m_state;
	PlayerFightType m_fightType;
	PlayerMagicType m_magicType;
};