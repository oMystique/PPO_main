#include "Enemy.h"

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

void CEnemy::pushAnimations()
{
	m_animations.insert({ PuppetAnimationType::move,
		CAnimationKit::create("easy_enemy_walk.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	m_animations.insert({ PuppetAnimationType::meleeAttack,
		CAnimationKit::create("easyFight.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	m_animations.insert({ PuppetAnimationType::die,
		CAnimationKit::create("unitDie.png", Rect(111, 0, 111, 118), 14, false, 0.11f) });
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
	auto spriteBody = PhysicsBody::createEdgeBox(Size(70, 50), PhysicsMaterial(300, 0, 0));
	spriteBody->setRotationEnable(false);
	spriteBody->setCollisionBitmask(1);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setDynamic(true);
	spriteBody->setMass(50);

	m_phantomeSprite->setPhysicsBody(spriteBody);
	m_phantomeSprite->setPosition(pos);
	addChild(m_phantomeSprite);

	pushAnimations();
	setAnimation(m_animations.at(PuppetAnimationType::move));
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
		if (m_phantomeSprite->getPhysicsBody()->getName() == "toOther!")
		{
			collisionDetectEvents();
		}
		m_puppetSprite->setPosition(m_phantomeSprite->getPosition());
	}
	else if (m_isAlive && m_dieTimer == 0)
	{
		m_dieTimer = 1;
		die();
	}
}

void CEnemy::attackedByFrost()
{
	if (m_debuffTimer == 0)
	{
		m_health -= 10;
	}
	m_velocityX = 25;
	m_puppetSprite->setColor(Color3B::BLUE);
	schedule(schedule_selector(CEnemy::updateDebuffTimer));
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
	if (m_state != PuppetState::attack)
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
	m_phantomeSprite->getPhysicsBody()->setName("");
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

bool CEnemy::isCanJump() const
{
	return getVelocity().y < 10;
}
