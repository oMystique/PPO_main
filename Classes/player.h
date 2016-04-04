#pragma once
#include "Entities.h"
#include "AnimationKit.h"
USING_NS_CC;

enum class PlayerState
{
	stay,
	moveLeft,
	moveRight,
	fight
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
	void move(int directionParam);
	void idle();

	void update() override;
private:
	void setAnimation(CAnimationKit *kit);
private:
	~CPlayer();
	ObjectKeeper<CAnimationKit> m_idleAnimation;
	ObjectKeeper<CAnimationKit> m_runAnimation;

	bool moving;
	int direction;

	void initPlayer();
};