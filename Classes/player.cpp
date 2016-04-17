#include "Player.h"

CPlayer::~CPlayer()
{
	CC_SAFE_RELEASE(m_idleAnimation);
	CC_SAFE_RELEASE(m_runAnimation);
}

CPlayer * CPlayer::create()
{
	CPlayer * player = new (std::nothrow) CPlayer();
	if (player && player->initWithFile("stay.png"))
	{
		player->autorelease();
		player->initPlayer();
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void CPlayer::initPlayer()
{
	m_state = PlayerState::stay;
	m_idleAnimation = CAnimationKit::create("stay_anim_1.png", Rect(130, 0, 130, 211), 7, true, 0.13f);
	this->runAction(m_idleAnimation->getAction()); //This will be the starting animation
	
	m_runAnimation = CAnimationKit::create("run_player_4.png", Rect(112, 0, 112, 150), 10, true, 0.09f);
	m_kniveOpAnimation = CAnimationKit::create("knives_operate___.png", Rect(250, 0, 250, 250), 19, false, 0.07f);
	m_attackAnimation = CAnimationKit::create("test_attack_2.png", Rect(250, 0, 250, 164), 11, true, 0.06f);
	m_animFrost = CAnimationKit::create("stay_anim_frost_2.png", Rect(130, 0, 130, 211), 7, false, 0.15f);
	m_animFire = CAnimationKit::create("stay_anim_fire.png", Rect(130, 0, 130, 211), 7, false, 0.15f);
}

void CPlayer::move(PlayerState const &state)
{
	if (state != m_state)
	{
		setAnimation(m_runAnimation);

		m_state = state;
	}
}

void CPlayer::knivesOperate()
{
	setAnimation(m_kniveOpAnimation);
}

void CPlayer::idle()
{
	if (m_state != PlayerState::stay)
	{
		m_state = PlayerState::stay;
		setAnimation(m_idleAnimation);
	}
}

void CPlayer::attack()
{
	m_fightType = PlayerFightType::melee;
	setAnimation(m_attackAnimation);
}

void CPlayer::fireOperate()
{
	m_fightType = PlayerFightType::magic;
	setAnimation(m_animFire);
}

void CPlayer::frostOperate()
{
	m_fightType = PlayerFightType::magic;
	setAnimation(m_animFrost);
}

void CPlayer::update()
{
	if (m_state != PlayerState::stay) //check if moving
	{
		if (m_state == PlayerState::moveLeft) //check if going left
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() - 5);
		}
		else if (m_state == PlayerState::moveRight)
		{
			this->setScaleX(1); //flip
			this->setPositionX(this->getPositionX() + 5);
		}
	}
}

void CPlayer::setAnimation(CAnimationKit * kit)
{
	stopAllActions();
	runAction(kit->getAction());
}
