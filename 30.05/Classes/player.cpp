#include "Player.h"

CPlayer::~CPlayer()
{
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
	runAction(m_idleAnimation->getAction());
	
	emptySprite = Sprite::create();
	emptySprite->initWithFile("stay.png");
	emptySprite->setColor(Color3B::RED);
	emptySprite->setVisible(false);
	m_pSpriteBody = PhysicsBody::createEdgeBox(Size(50, 86), PhysicsMaterial(300, 0, 0));
	m_pSpriteBody->setRotationEnable(false);
	m_pSpriteBody->setAngularDamping(0);
	m_pSpriteBody->setLinearDamping(0);
	
	m_pSpriteBody->setDynamic(true);
	m_pSpriteBody->setMass(50);
	emptySprite->setPhysicsBody(m_pSpriteBody);

	m_runAnimation = CAnimationKit::create("run_player_4.png", Rect(112, 0, 112, 150), 10, true, 0.09f);
	m_kniveOpAnimation = CAnimationKit::create("knives_operate___.png", Rect(250, 0, 250, 250), 19, false, 0.07f);
	m_attackAnimation = CAnimationKit::create("test_attack_2.png", Rect(250, 0, 250, 164), 11, true, 0.06f);
	m_animFrost = CAnimationKit::create("stay_anim_frost_2.png", Rect(130, 0, 130, 211), 7, false, 0.15f);
	m_animFire = CAnimationKit::create("stay_anim_fire.png", Rect(130, 0, 130, 211), 7, false, 0.15f);
	m_animArcane = CAnimationKit::create("stay_anim_arcan.png", Rect(130, 0, 130, 211), 7, false, 0.15f);
}

void CPlayer::arcaneOperate()
{
	setAnimation(m_animArcane);
}

PlayerState CPlayer::getPlayerState() const
{
	return m_state;
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
	if (m_state != PlayerState::stay)
	{
		if (m_state == PlayerState::moveLeft)
		{
			this->setScaleX(-0.6);
			if (emptySprite->getPhysicsBody()->getVelocity().x > -200)
			{
				emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x - 20, emptySprite->getPhysicsBody()->getVelocity().y));
			}
		}
		else if (m_state == PlayerState::moveRight)
		{
			this->setScaleX(0.6); 
			if (emptySprite->getPhysicsBody()->getVelocity().x < 200)
			{
				emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x + 20, emptySprite->getPhysicsBody()->getVelocity().y));
			}
		}
	}
	else
	{
		emptySprite->getPhysicsBody()->setVelocity(Vec2(0, emptySprite->getPhysicsBody()->getVelocity().y));
	}
	if (m_isJump)
	{
		if (emptySprite->getPhysicsBody()->getVelocity().y == 0 && jumpPos.y == 0)
		{
			jumpPos = emptySprite->getPosition();
			emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x, emptySprite->getPhysicsBody()->getVelocity().y + 200));
		}
		else if (abs(jumpPos.y - emptySprite->getPosition().y) < 83)
		{
			m_isJump = false;
			jumpPos = Vec2(0, 0);
		}
	}
    setPosition(emptySprite->getPosition());
}

int CPlayer::getHealthCount() const
{
	return m_health;
}

int CPlayer::getManaCount() const
{
	return m_mana;
}

void CPlayer::setAnimation(CAnimationKit * kit)
{
	stopAllActions();
	runAction(kit->getAction());
}
