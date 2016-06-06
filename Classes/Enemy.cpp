#include "Enemy.h"
#include "SpellObject.h"

USING_NS_CC;

CEnemy * CEnemy::create(cocos2d::Vec2 const &pos)
{
	CEnemy * enemy = new (std::nothrow) CEnemy();
	if (enemy)
	{
		enemy->autorelease();
		enemy->initEnemy(pos);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);

	return NULL;
}


void CEnemy::dieTimer(float dt)
{
	if (m_dieTimer < 90)
	{
		++m_dieTimer;
	}
	else
	{
		unschedule(schedule_selector(CEnemy::dieTimer));
		m_isAlive = false;
	}
}

void CEnemy::pushMeleeEnemyAnimations()
{
	m_animations.insert({ PuppetAnimationType::move,
		CAnimationKit::create("easy_enemy_walk.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	m_animations.insert({ PuppetAnimationType::meleeAttack,
		CAnimationKit::create("easyFight.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	setTag(1);
	setAnimation(m_animations.at(PuppetAnimationType::move));
}

void CEnemy::initEnemy(cocos2d::Vec2 const &pos)
{
	m_puppetSprite = Sprite::create();
	m_puppetSprite->initWithFile("easy_enemy_walk.png");
	m_puppetSprite->setScaleY(0.6);
	addChild(m_puppetSprite);

	m_phantomeSprite = Sprite::create();
	m_phantomeSprite->initWithFile("stay.png");
	m_phantomeSprite->setVisible(false);
	auto spriteBody = PhysicsBody::createEdgeBox(Size(70, 50), PhysicsMaterial(300, 0, 0), 4);
	spriteBody->setRotationEnable(false);
	spriteBody->setCollisionBitmask(1);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setDynamic(true);
	spriteBody->setMass(50);

	m_phantomeSprite->setPhysicsBody(spriteBody);
	m_phantomeSprite->setPosition(pos);
	addChild(m_phantomeSprite);

	m_animations.insert({ PuppetAnimationType::die,
		CAnimationKit::create("unitDie.png", Rect(111, 0, 111, 118), 14, false, 0.11f) });

	m_state = PuppetState::moveLeft;
}

void CEnemy::action(PuppetState const & state)
{
	switch (state)
	{
	case PuppetState::moveLeft:
		move(state);
		break;
	case PuppetState::moveRight:
		move(state);
		break;
	case PuppetState::attack:
		attack();
		break;
	}
	m_state = state;
}

void CEnemy::update()
{
	if (m_health > 0)
	{
		unscheduleDebuffTimer();
		if (physicsBodyNameIsEqual("toOther!"))
		{
			collisionDetectEvents();
		}
		else if (physicsBodyNameIsEqual("collideWithFrostBalt"))
		{
			collideByFrostBalt();
		}
		else if (physicsBodyNameIsEqual("collideWithFireBalt"))
		{
			hasDamaged(60);
		}
		else if (physicsBodyNameIsEqual("collideWithArcanBlast"))
		{
			hasDamaged(12);
		}
		m_phantomeSprite->getPhysicsBody()->setName("");
		m_puppetSprite->setPosition(m_phantomeSprite->getPosition());
	}
	else if (m_isAlive && m_dieTimer == 0)
	{
		m_dieTimer = 1;
		m_puppetSprite->setColor(Color3B::WHITE);
		die();
	}
}

void CEnemy::attackedByFrost()
{
	if (m_puppetSprite->getColor() != Color3B::BLUE)
	{
		m_health -= 10;
	}
	m_velocityX = 25;
	m_puppetSprite->setColor(Color3B::BLUE);
	schedule(schedule_selector(CEnemy::updateDebuffTimer));
}

void CEnemy::attackedByFire()
{
	if (m_puppetSprite->getColor() != Color3B::RED)
	{
		m_velocityX += 100;
		m_health -= 65;
		m_debuffTimer = 1;
	}
	m_puppetSprite->setColor(Color3B::RED);
	schedule(schedule_selector(CEnemy::updateDebuffTimer));
}

int CEnemy::getAttackTimerLimit()
{
	return getTag() == 1 ? 19 : 90;
}

void CEnemy::castBalt()
{
	auto spell = CSpellObject::create(200 * m_puppetSprite->getScaleX(), getPosition()
		+ Vec2((getBoundingBox().size.width) * (m_puppetSprite->getScaleX()), 0), "range_enemy_balts.png", 5, "enemy_cast_die.png");
	addChild(spell);
}

void CEnemy::pushRangeEnemyAnimations()
{
	m_animations.insert({ PuppetAnimationType::move,
		CAnimationKit::create("enemy_range_move.png", Rect(150, 0, 150, 106), 6, true, 0.16f) });
	m_animations.insert({ PuppetAnimationType::meleeAttack,
		CAnimationKit::create("enemy_range_cast_anim.png", Rect(150, 0, 150, 106), 2, true, 0.16f) });
	setTag(2);
	setAnimation(m_animations.at(PuppetAnimationType::move));
}

PuppetState CEnemy::SwitchMoveDirection(PuppetState const & state)
{
	switch (state)
	{
	case PuppetState::moveLeft:
		return PuppetState::moveRight;
	case PuppetState::moveRight:
		return PuppetState::moveLeft;
	default:
		return state;
	}
}

void CEnemy::die()
{
	setAnimation(m_animations.at(PuppetAnimationType::die));
	schedule(schedule_selector(CEnemy::dieTimer));
}

void CEnemy::attack()
{
	if (m_state != PuppetState::attack && m_health > 0)
	{
		setVelocity(Vec2(0, getVelocity().y));
		m_state = PuppetState::attack;
		setAnimation(m_animations.at(PuppetAnimationType::meleeAttack));
	}
}

void CEnemy::updateDebuffTimer(float /*dt*/)
{
	++m_debuffTimer;
}

void CEnemy::collisionDetectEvents()
{
	if (m_isPursuitTarget)
	{
		jump();
	}
	else
	{
		action(SwitchMoveDirection(m_state));
	}
}

void CEnemy::unscheduleDebuffTimer()
{
	if (m_debuffTimer > 500)
	{
		unschedule(schedule_selector(CEnemy::updateDebuffTimer));
		m_debuffTimer = 0;
		m_puppetSprite->setColor(Color3B::WHITE);
		m_velocityX = 200;
	}
}

void CEnemy::collideByFrostBalt()
{
	if (m_puppetSprite->getColor() != Color3B::BLUE)
	{
		hasDamaged(15);
	}
	else
	{
		hasDamaged(30);
	}
	attackedByFrost();
}

bool CEnemy::isCanJump() const
{
	return getVelocity().y < 10;
}
