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
	moving = false;

	m_idleAnimation = CAnimationKit::create("knives_operate___.png", Rect(250, 0, 250, 250), 19, true, 0.07f);
	this->runAction(m_idleAnimation->getAction()); //This will be the starting animation
	
	m_runAnimation = CAnimationKit::create("run_player_4.png", Rect(112, 0, 112, 150), 10, true, 0.09f);
}

void CPlayer::move(int directionParam)
{
	setAnimation(m_runAnimation);

	direction = directionParam;
	moving = true;
}

void CPlayer::idle()
{
	moving = false;
	setAnimation(m_idleAnimation);
}

void CPlayer::update()
{
	if (moving) //check if moving
	{
		if (direction == 0) //check if going left
		{
			this->setScaleX(-1); //flip
			this->setPositionX(this->getPositionX() - 5);
		}
		else
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
