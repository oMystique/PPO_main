#include "EnemyPuppeteer.h"
#include "AudioEngine.h" 

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

void CEnemyPuppeteer::updateAttackTimer(float /*dt*/)
{
	++m_attackTimer;
}

void CEnemyPuppeteer::unscheduleAttackTimer()
{
	if (m_attackTimer > m_enemy->getAttackTimerLimit())
	{
		unschedule(schedule_selector(CEnemyPuppeteer::updateAttackTimer));
		if (m_enemy->getTag() == 2)
		{
			m_enemy->castBalt();
		}
		m_attackTimer = 0;
	}
}

void CEnemyPuppeteer::scheduleAttackTimer()
{
	if (m_attackTimer == 0 && m_enemy->getHealthCount() > 0)
	{
		int audio;
		m_enemy->getTag() == 2 ? audio = experimental::AudioEngine::play2d("enemy_cast_sound.mp3") 
			: audio = experimental::AudioEngine::play2d("kickHit.ogg");
		schedule(schedule_selector(CEnemyPuppeteer::updateAttackTimer));
		m_attackTimer = 1;
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
		damagePuppet(15);
	}
	m_enemy->action(PuppetState::attack);
	scheduleAttackTimer();
}

CEnemy *CEnemyPuppeteer::getPuppet() const
{
	return m_enemy;
}

bool CEnemyPuppeteer::isAttack() const
{
	if (m_enemyIsAttack && m_enemy->getTag() == 1)
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
		break;
	case 2:
		m_enemy->attackedByFire();
		break;
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
		if (m_enemy->getBoundingBox().intersectsRect(playerRect)
			|| (m_enemy->getTag() == 2 
				&& abs(m_enemy->getPosition().x - playerPos.x) < 200))
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

	unscheduleAttackTimer();

	m_enemy->update();
}
