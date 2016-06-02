#include "Enemy.h"

USING_NS_CC;

CEnemy * CEnemy::create()
{
	CEnemy * enemy = new (std::nothrow) CEnemy();
	if (enemy)
	{
		enemy->autorelease();
		enemy->initEnemy();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);

	return NULL;
}

bool CEnemy::isAlive() const
{
	return m_isAlive;
}

bool CEnemy::canDeallocate() const
{
	return !m_isAlive;
}

Vec2 CEnemy::getVelocity()const
{
	return m_phantomeSprite->getPhysicsBody()->getVelocity();
}

void CEnemy::setVelocity(Vec2 const & velocity)
{
	m_phantomeSprite->getPhysicsBody()->setVelocity(velocity);
}

void CEnemy::dieTimer(float dt)
{
	if (m_dieTimer < 90)
	{
		m_dieTimer += 1;
	}
	else
	{
		unschedule(schedule_selector(CEnemy::dieTimer));
		m_isAlive = false;
	}
}

void CEnemy::pushAnimations()
{
	m_animations.insert({ EnemyAnimationType::move,
		CAnimationKit::create("easy_enemy_walk.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	m_animations.insert({ EnemyAnimationType::attack,
		CAnimationKit::create("easyFight.png", Rect(150, 0, 150, 106), 2, true, 0.2f) });
	m_animations.insert({ EnemyAnimationType::die,
		CAnimationKit::create("unitDie.png", Rect(111, 0, 111, 118), 14, false, 0.11f) });
}

void CEnemy::initEnemy()
{
	m_enemySprite = Sprite::create();
	m_enemySprite->initWithFile("easy_enemy_walk.png");
	m_enemySprite->setScaleY(0.6);
	addChild(m_enemySprite);

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
	addChild(m_phantomeSprite);

	pushAnimations();
	setAnimation(m_animations.at(EnemyAnimationType::move));
}

void CEnemy::action(EnemyState const & state)
{
	switch (state)
	{
	case EnemyState::moveLeft:
		move(state);
		break;
	case EnemyState::moveRight:
		move(state);
		break;
	case EnemyState::attack:
		attack();
		break;
	}
	m_state = state;
}

void CEnemy::update()
{
	if (m_health > 0)
	{
		if (m_debuffTimer > 500)
		{
			unschedule(schedule_selector(CEnemy::updateDebuffTimer));
			m_debuffTimer = 0;
			m_enemySprite->setColor(Color3B::WHITE);
			m_velocityX = 200;
		}
		if (m_phantomeSprite->getPhysicsBody()->getName() == "toOther!")
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
		m_enemySprite->setPosition(m_phantomeSprite->getPosition());
	}
	else if (m_isAlive && m_dieTimer == 0)
	{
		m_dieTimer = 1;
		die();
	}
}

void CEnemy::setPosition(cocos2d::Vec2 const & pos)
{
	m_phantomeSprite->setPosition(pos);
	m_enemySprite->setPosition(pos);
}

int CEnemy::getHealthCount() const
{
	return m_health;
}

int CEnemy::getManaCount() const
{
	return 0;
}

const cocos2d::Vec2 & CEnemy::getPosition() const
{
	return m_phantomeSprite->getPosition();
}

cocos2d::Rect CEnemy::getBoundingBox() const
{
	return m_enemySprite->getBoundingBox();
}

void CEnemy::attackedByFrost()
{
	if (m_debuffTimer == 0)
	{
		m_health -= 10;
	}
	m_velocityX = 25;
	m_enemySprite->setColor(Color3B::BLUE);
	schedule(schedule_selector(CEnemy::updateDebuffTimer));
}

void CEnemy::hasDamaged(int healthCount)
{
	m_health -= healthCount;
}

EnemyState CEnemy::SwitchMoveDirection(EnemyState const & state)
{
	switch (state)
	{
	case EnemyState::moveLeft:
		return EnemyState::moveRight;
	case EnemyState::moveRight:
		return EnemyState::moveLeft;
	default:
		return state;
	}
}

void CEnemy::move(EnemyState const & state)
{
	int sign = static_cast<int>(state);
	if (((sign > 0) && (getVelocity().x < m_velocityX))
		|| ((sign < 0) && (getVelocity().x > -m_velocityX)))
	{
		m_enemySprite->setScaleX(0.6f * sign);
		setVelocity(Vec2(getVelocity().x + 20 * sign, getVelocity().y));
	}
	if (state != m_state)
	{
		setAnimation(m_animations.at(EnemyAnimationType::move));
	}
}

void CEnemy::jump()
{
	if (getVelocity().y < 10)
	{
		jumpPos = m_phantomeSprite->getPosition();
		setVelocity(Vec2(getVelocity().x, getVelocity().y + 200));
	}
	else if (abs(jumpPos.y - getPosition().y) < 73)
	{
		jumpPos = Vec2(0, 0);
	}
}

void CEnemy::die()
{
	setAnimation(m_animations.at(EnemyAnimationType::die));
	schedule(schedule_selector(CEnemy::dieTimer));
}

void CEnemy::attack()
{
	if (m_state != EnemyState::attack)
	{
		setVelocity(Vec2(0, getVelocity().y));
		m_state = EnemyState::attack;
		setAnimation(m_animations.at(EnemyAnimationType::attack));
	}
}

void CEnemy::idle()
{
	setAnimation(m_animations.at(EnemyAnimationType::move));
}

void CEnemy::setAnimation(CAnimationKit * kit)
{
	m_enemySprite->stopAllActions();
	m_enemySprite->runAction(kit->getAction());
}

void CEnemy::updateDebuffTimer(float /*dt*/)
{
	m_debuffTimer += 1;
}
