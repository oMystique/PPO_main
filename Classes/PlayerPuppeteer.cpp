#include "PlayerPuppeteer.h"

USING_NS_CC;

CPlayerPuppeteer *CPlayerPuppeteer::create(Vec2 const & playerPos)
{
	CPlayerPuppeteer *playerPuppeteer = new (std::nothrow) CPlayerPuppeteer();
	if (playerPuppeteer)
	{
		playerPuppeteer->autorelease();
		playerPuppeteer->init(playerPos);
		return playerPuppeteer;
	}
	CC_SAFE_DELETE(playerPuppeteer);

	return NULL;
}

bool CPlayerPuppeteer::isAttack() const
{
	return m_player->isAttack();
}

void CPlayerPuppeteer::init(Vec2 const & playerPos)
{
	m_player = CPlayer::create(playerPos);
	addChild(m_player);
}

CPlayer *CPlayerPuppeteer::getPuppet()const
{
	return m_player;
}

const Vec2 &CPlayerPuppeteer::getPuppetPos()const
{
	return m_player->getPosition();
}

void CPlayerPuppeteer::update(cocos2d::Vec2 const & controllerPosition)
{
	if (controllerPosition.x < 0)
	{
		m_player->action(PuppetState::moveLeft);
	}
	else if (controllerPosition.x > 0)
	{
		m_player->action(PuppetState::moveRight);
	}
	else if (controllerPosition.x == 0)
	{
		m_player->action(PuppetState::stay);
	};
	if (controllerPosition.y > 50)
	{
		m_player->action(PuppetState::jump);
	}
	m_player->update();
}

void CPlayerPuppeteer::damagePuppet(int healthCount)
{
	m_player->hasDamaged(healthCount);
}

void CPlayerPuppeteer::burnPuppetMana(int manaCount)
{
	m_player->hasBurnedMana(manaCount);
}

bool CPlayerPuppeteer::puppetIsNeedBonus(int bonusTag)
{
	switch (bonusTag)
	{
	case 1:
		if (m_player->getHealthCount() <= 90)
		{
			m_player->useBonus(bonusTag);
			return true;
		}
	case 2:
		if (m_player->getManaCount() <= 80)
		{
			m_player->useBonus(bonusTag);
			return true;
		}
	}
	return false;
}

