#pragma once
#include "Entities.h"
#include "AnimationKit.h"

enum class EnemyState
{
	moveLeft = -1,
	moveRight = 1,
	jump,
	attack
};

enum class EnemyAnimationType
{
	stay,
	move,
	attack,
	die
};

class CEnemy
	: public cocos2d::Node
{
public:
	static CEnemy * create();

	bool isAlive()const;

	bool canDeallocate()const;

	void attack();
	void idle();

	EnemyState m_state;
	bool m_isPursuitTarget = false;

	void action(EnemyState const &state);
	void update();

	void setPosition(cocos2d::Vec2 const &pos);
	int getHealthCount()const;
	int getManaCount()const;
	const cocos2d::Vec2 &getPosition()const override;
	cocos2d::Rect getBoundingBox()const override;

	void attackedByFrost();
	void hasDamaged(int healthCount);
private:
	static EnemyState SwitchMoveDirection(EnemyState const &state);

	void move(EnemyState const &state);
	void jump();

	void die();

	cocos2d::Vec2 getVelocity()const;
	void setVelocity(cocos2d::Vec2 const &velocity);

	void dieTimer(float dt);

	void pushAnimations();
	void initEnemy();
	void setAnimation(CAnimationKit *kit);
	void updateDebuffTimer(float dt);
private:
	cocos2d::Sprite* m_enemySprite = nullptr;
	cocos2d::Sprite* m_phantomeSprite = nullptr;

	ObjectKeeper<CAnimationKit> m_runAnimation = nullptr;
	ObjectKeeper<CAnimationKit> m_attackAnimation = nullptr;
	bool m_isJump = false;
	cocos2d::Vec2 jumpPos = { 0, 0 };
	std::map<const EnemyAnimationType, ObjectKeeper<CAnimationKit>> m_animations;
	int m_health = 100;
	int m_debuffTimer = 0;
	float m_velocityX = 200;
	bool m_isAlive = true;
	float m_dieTimer = 0;
};

