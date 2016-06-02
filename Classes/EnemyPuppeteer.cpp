#include "EnemyPuppeteer.h"

USING_NS_CC;

CEnemyPuppeteer * CEnemyPuppeteer::create(Vec2 const & playerPos)
{
	CEnemyPuppeteer *enemyPuppeteer = new (std::nothrow) CEnemyPuppeteer();
	if (enemyPuppeteer)
	{
		enemyPuppeteer->autorelease();
		enemyPuppeteer->init(playerPos);
		return enemyPuppeteer;
	}
	CC_SAFE_DELETE(enemyPuppeteer);

	return nullptr;
}

void CEnemyPuppeteer::init(Vec2 const & puppetPos)
{
	m_enemy = CEnemy::create(puppetPos);
	addChild(m_enemy);

	m_lifebar = CLifeBar::create(Vec2(), Vec2(),
		"enemy_lifebar_background.png", "enemy_lifebar_hp.png");
	addChild(m_lifebar);
}

void CEnemyPuppeteer::updateTimer(float /*dt*/)
{
	m_timer += 1;
}

void CEnemyPuppeteer::unscheduleTimer()
{
	if (m_timer > 19)
	{
		unschedule(schedule_selector(CEnemyPuppeteer::updateTimer));
		m_timer = 0;
	}
}

void CEnemyPuppeteer::scheduleTimer()
{
	if (m_timer == 0)
	{
		schedule(schedule_selector(CEnemyPuppeteer::updateTimer));
		m_timer = 1;
		m_enemyIsAttack = true;
	}
}

void CEnemyPuppeteer::pursuitTarget(Vec2 const &playerPos)
{
	m_enemy->m_isPursuitTarget = true;
	if (m_enemy->getPosition().x < playerPos.x)
	{
		m_enemy->action(PuppetState::moveRight);
	}
	else
	{
		m_enemy->action(PuppetState::moveLeft);
	}
}

void CEnemyPuppeteer::attackTarget(bool playerIsAttacked)
{
	if (playerIsAttacked)
	{
		damagePuppet(20);
	}
	m_enemy->action(PuppetState::attack);
	scheduleTimer();
}

CEnemy *CEnemyPuppeteer::getPuppet() const
{
	return m_enemy;
}

bool CEnemyPuppeteer::isAttack() const
{
	if (m_enemyIsAttack)
	{
		m_enemyIsAttack = false;
		return true;
	}

	return false;
}

void CEnemyPuppeteer::puppetHasAttackedByMagic(int magicType)
{
	switch (magicType)
	{
	case 1:
		m_enemy->attackedByFrost();
	}
}

void CEnemyPuppeteer::damagePuppet(int healthCount)
{
	m_enemy->hasDamaged(healthCount);
}

bool CEnemyPuppeteer::hasPuppet()const
{
	return !m_enemy->isAlive();
}

void CEnemyPuppeteer::interactWithPlayer(cocos2d::Vec2 const & playerPos, cocos2d::Rect const & playerRect, bool playerIsAttacked)
{
	if (abs(m_enemy->getPosition().x - playerPos.x) < 500)
	{
		if (m_enemy->getBoundingBox().intersectsRect(playerRect))
		{
			attackTarget(playerIsAttacked);
		}
		else
		{
			pursuitTarget(playerPos);
		}
	}
	else
	{
		m_enemy->move(m_enemy->getState());
		m_enemy->m_isPursuitTarget = false;
	}
}

void CEnemyPuppeteer::update()
{
	m_lifebar->updateHealthBarPosition(m_enemy->getPosition() + Vec2(0.f, 60.f)
		, m_enemy->getPosition() + Vec2(-56.f, 55.6f));
	m_lifebar->update(m_enemy->getHealthCount());

	unscheduleTimer();

	m_enemy->update();
}
