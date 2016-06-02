#include "Player.h"

USING_NS_CC;

CPlayer * CPlayer::create()
{
	CPlayer * player = new (std::nothrow) CPlayer();
	if (player)
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
	m_playerSprite = Sprite::create();
	m_playerSprite->initWithFile("stay.png");
	m_playerSprite->setScale(0.6f);
	addChild(m_playerSprite);

	m_phantomeSprite = Sprite::create();
	m_phantomeSprite->initWithFile("stay.png");
	m_phantomeSprite->setVisible(false);

	auto spriteBody = PhysicsBody::createEdgeBox(Size(50, 86), PhysicsMaterial(300, 0, 0));
	spriteBody->setRotationEnable(false);
	spriteBody->setDynamic(true);
	spriteBody->setMass(50);

	m_phantomeSprite->setPhysicsBody(spriteBody);
	addChild(m_phantomeSprite);

	pushAnimations();
	setAnimation(m_animations.at(PlayerAnimationType::stay));
}

void CPlayer::arcaneOperate()
{
	setAnimation(m_animations.at(PlayerAnimationType::arcaneMageSwitch));
}

const Vec2 & CPlayer::getPosition()const
{
	return m_phantomeSprite->getPosition();
}

Rect CPlayer::getBoundingBox() const
{
	return m_playerSprite->getBoundingBox();
}

void CPlayer::action(PlayerState const & state)
{
	switch (state)
	{
	case PlayerState::moveLeft:
		move(state);
		break;
	case PlayerState::moveRight:
		move(state);
		break;
	case PlayerState::jump:
		jump();
		break;
	case PlayerState::stay:
		idle();
		break;
	}
	m_state = state;
}

void CPlayer::move(PlayerState const &state)
{
	int sign = static_cast<int>(state);
	if (((sign > 0) && (getVelocity().x < 200.f)) 
		|| ((sign < 0) && (getVelocity().x > -200.f)))
	{
		m_playerSprite->setScaleX(0.6f * sign);
		setVelocity(Vec2(getVelocity().x + 20 * sign, getVelocity().y));
	}
	if (state != m_state)
	{
		setAnimation(m_animations.at(PlayerAnimationType::run));
	}
}

void CPlayer::setPosition(Vec2 const & pos)
{
	m_playerSprite->setPosition(pos);
	m_phantomeSprite->setPosition(pos);
}

void CPlayer::knivesOperate()
{
	setAnimation(m_animations.at(PlayerAnimationType::knivesOperate));
}

void CPlayer::idle()
{
	setVelocity(Vec2(0, getVelocity().y));
	if (m_state != PlayerState::stay)
	{
		m_state = PlayerState::stay;
		setAnimation(m_animations.at(PlayerAnimationType::stay));
	}
}

void CPlayer::attack()
{
	auto anim = m_animations.at(PlayerAnimationType::knivesAttack);
	if (anim->getAction()->isDone() || m_playerSprite->getNumberOfRunningActions() == 0)
	{
		m_isMeleeAttack = true;
		setAnimation(m_animations.at(PlayerAnimationType::knivesAttack));
	}
}

void CPlayer::fireOperate()
{
	setAnimation(m_animations.at(PlayerAnimationType::fireMageSwitch));
}

void CPlayer::frostOperate()
{
	setAnimation(m_animations.at(PlayerAnimationType::frostMageSwitch));
}

void CPlayer::update()
{
	m_playerSprite->setPosition(m_phantomeSprite->getPosition());
}

bool CPlayer::isAttack() const
{
	if (m_isMeleeAttack)
	{
		m_isMeleeAttack = false;
		return true;
	}

	return false;
}

void CPlayer::hasDamaged(int healthCount)
{
	m_health -= healthCount;
}

void CPlayer::hasBurnedMana(int manaCount)
{
	m_mana -= manaCount;
}

void CPlayer::jump()
{
	if (getVelocity().y == 0 && m_jumpPos.y == 0)
	{
		m_jumpPos = m_phantomeSprite->getPosition();
		setVelocity(Vec2(getVelocity().x, getVelocity().y + 200.f));
	}
	else if (abs(m_jumpPos.y - getPosition().y) < 83.f)
	{
		m_jumpPos = { 0, 0 };
	}
}

Vec2 CPlayer::getVelocity()const
{
	return m_phantomeSprite->getPhysicsBody()->getVelocity();
}

void CPlayer::setVelocity(Vec2 const &velocity)
{
	m_phantomeSprite->getPhysicsBody()->setVelocity(velocity);
}

int CPlayer::getHealthCount() const
{
	return m_health;
}

int CPlayer::getManaCount() const
{
	return m_mana;
}

void CPlayer::pushAnimations()
{
	m_animations.insert({ PlayerAnimationType::stay,
		CAnimationKit::create("stay_anim_1.png", Rect(130, 0, 130, 211), 7, true, 0.13f) });
	m_animations.insert({ PlayerAnimationType::run,
		CAnimationKit::create("run_player_4.png", Rect(112, 0, 112, 150), 10, true, 0.09f) });
	m_animations.insert({ PlayerAnimationType::knivesOperate,
		CAnimationKit::create("9.png", Rect(250, 0, 250, 250), 15, false, 0.07f) });
	m_animations.insert({ PlayerAnimationType::knivesAttack,
		CAnimationKit::create("test_attack_2.png", Rect(250, 0, 250, 164), 11, false, 0.06f) });
	m_animations.insert({ PlayerAnimationType::frostMageSwitch,
		CAnimationKit::create("stay_anim_frost_2.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PlayerAnimationType::fireMageSwitch,
		CAnimationKit::create("stay_anim_fire.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PlayerAnimationType::arcaneMageSwitch,
		CAnimationKit::create("stay_anim_arcan.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
}

void CPlayer::setAnimation(CAnimationKit * kit)
{
	m_playerSprite->stopAllActions();
	m_playerSprite->runAction(kit->getAction());
}
