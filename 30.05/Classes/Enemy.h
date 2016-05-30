#pragma once
#include "Entities.h"
#include "AnimationKit.h"

enum class EnemyAction
{
	moveLeft,
	moveRight,
	jump,
	attack
};

class CEnemy
	: public CEntities
{
public:
	static CEnemy * create();

	void initEnemy();
	void update() override;
	~CEnemy() = default;

	void attack();
	void idle();

	EnemyAction m_state;
	bool m_isPursuitTarget = false;
	cocos2d::PhysicsBody *m_pSpriteBody;
	ObjectKeeper<Sprite> emptySprite;
private:
	void setAnimation(CAnimationKit *kit);
	ObjectKeeper<CAnimationKit> m_runAnimation;
	ObjectKeeper<CAnimationKit> m_attackAnimation;
	bool m_isJump;
	cocos2d::Vec2 jumpPos;
};

