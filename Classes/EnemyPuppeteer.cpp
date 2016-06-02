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
	m_enemy = CEnemy::create();
	m_enemy->setPosition(puppetPos);
	addChild(m_enemy);

	m_lifebar = CLifeBar::create(Vec2(), Vec2(),
		"enemy_lifebar_background.png", "enemy_lifebar_hp.png");
	addChild(m_lifebar);
}

void CEnemyPuppeteer::updateTimer(float /*dt*/)
{
	m_timer += 1;
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

bool CEnemyPuppeteer::hasPuppet() const
{
	return m_enemy->canDeallocate();
}

void CEnemyPuppeteer::update(Vec2 const & playerPos, Rect const & playerRect, bool playerIsAttacked)
{
	if (!hasPuppet())
	{
		m_lifebar->updateHealthBarPosition(m_enemy->getPosition() + Vec2(0.f, 60.f), m_enemy->getPosition() + Vec2(-56.f, 55.6f));
		m_lifebar->update(m_enemy->getHealthCount());
		if (m_timer > 19)
		{
			unschedule(schedule_selector(CEnemyPuppeteer::updateTimer));
			m_timer = 0;
		}
		if (abs(m_enemy->getPosition().x - playerPos.x) < 250)
		{
			if (m_enemy->getBoundingBox().intersectsRect(playerRect))
			{
				if (playerIsAttacked)
				{
					damagePuppet(20);
				}
				m_enemy->action(EnemyState::attack);
				if (m_timer == 0)
				{
					schedule(schedule_selector(CEnemyPuppeteer::updateTimer));
					m_timer = 1;
					m_enemyIsAttack = true;
				}
			}
			else
			{
				m_enemy->m_isPursuitTarget = true;
				if (m_enemy->m_state == EnemyState::attack)
				{
					m_enemy->idle();
				}
				if (m_enemy->getPosition().x < playerPos.x)
				{
					m_enemy->action(EnemyState::moveRight);
				}
				else
				{
					m_enemy->action(EnemyState::moveLeft);
				}
			}
		}
		else
		{
			m_enemy->m_isPursuitTarget = false;
		}
		m_enemy->update();
	}
}
