#include "Player.h"
#include "SpellObject.h"

USING_NS_CC;

CPlayer * CPlayer::create(cocos2d::Vec2 const &pos)
{
	CPlayer * player = new (std::nothrow) CPlayer();
	if (player)
	{
		player->autorelease();
		player->initPlayer(pos);
		return player;
	}

	CC_SAFE_DELETE(player);
	return NULL;
}

void CPlayer::initPlayer(cocos2d::Vec2 const &pos)
{	
	m_puppetSprite = Sprite::create();
	m_puppetSprite->initWithFile("stay.png");
	m_puppetSprite->setScale(0.6f);
	m_puppetSprite->setPosition(pos);
	addChild(m_puppetSprite);

	m_phantomeSprite = Sprite::create();
	m_phantomeSprite->initWithFile("stay.png");
	m_phantomeSprite->setVisible(false);
	m_phantomeSprite->setPosition(pos);

	auto spriteBody = PhysicsBody::createEdgeBox(Size(50, 86), PhysicsMaterial(300, 0, 0));
	spriteBody->setRotationEnable(false);
	spriteBody->setDynamic(true);
	spriteBody->setMass(50);

	m_phantomeSprite->setPhysicsBody(spriteBody);
	addChild(m_phantomeSprite);

	pushAnimations();
	setAnimation(m_animations.at(PuppetAnimationType::stay));
}

void CPlayer::arcaneOperate()
{
	setAnimation(m_animations.at(PuppetAnimationType::arcaneMageSwitch));
}

void CPlayer::castFrostBalt()
{
	if (m_mana >= 10 && m_state == PuppetState::stay)
	{
		m_castTimer = 0;
		schedule(schedule_selector(CPlayer::castTimer));
		setAnimation(m_animations.at(PuppetAnimationType::castFrostBalt));
	}
}

void CPlayer::action(PuppetState const & state)
{
	switch (state)
	{
	case PuppetState::moveLeft:
		move(state);
		break;
	case PuppetState::moveRight:
		move(state);
		break;
	case PuppetState::jump:
		jump();
		break;
	case PuppetState::stay:
		idle();
		break;
	}
	m_state = state;
}

void CPlayer::knivesOperate()
{
	setAnimation(m_animations.at(PuppetAnimationType::knivesOperate));
}

void CPlayer::idle()
{
	setVelocity(Vec2(0, getVelocity().y));
	if (m_state != PuppetState::stay)
	{
		m_state = PuppetState::stay;
		setAnimation(m_animations.at(PuppetAnimationType::stay));
	}
}

void CPlayer::attack()
{
	auto anim = m_animations.at(PuppetAnimationType::meleeAttack);
	if (anim->getAction()->isDone() || m_puppetSprite->getNumberOfRunningActions() == 0)
	{
		m_isMeleeAttack = true;
		setAnimation(m_animations.at(PuppetAnimationType::meleeAttack));
	}
}

void CPlayer::fireOperate()
{
	setAnimation(m_animations.at(PuppetAnimationType::fireMageSwitch));
}

void CPlayer::frostOperate()
{
	setAnimation(m_animations.at(PuppetAnimationType::frostMageSwitch));
}

void CPlayer::update()
{
	m_puppetSprite->setPosition(m_phantomeSprite->getPosition());
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

void CPlayer::hasBurnedMana(int manaCount)
{
	m_mana -= manaCount;
}

int CPlayer::getManaCount() const
{
	return m_mana;
}

void CPlayer::castTimer(float /*dt*/)
{
	if (!m_puppetSprite->getActionByTag(1) || m_state != PuppetState::stay)
	{
		m_castTimer = 0;
		unschedule(schedule_selector(CPlayer::castTimer));
		stopAllActions();
	}
	if (m_castTimer < 60)
	{
		++m_castTimer;
	}
	else
	{
		auto spell = CSpellObject::create(200 * m_puppetSprite->getScaleX(), getPosition()
			+ Vec2(getBoundingBox().size.width * m_puppetSprite->getScaleX(), -20));
		addChild(spell);
		unschedule(schedule_selector(CPlayer::castTimer));
		m_castTimer = 0;
		hasBurnedMana(10);
		setAnimation(m_animations.at(PuppetAnimationType::stay));
	}
}

void CPlayer::pushAnimations()
{
	m_animations.insert({ PuppetAnimationType::stay,
		CAnimationKit::create("stay_anim_1.png", Rect(130, 0, 130, 211), 7, true, 0.13f) });
	m_animations.insert({ PuppetAnimationType::move,
		CAnimationKit::create("run_player_4.png", Rect(112, 0, 112, 150), 10, true, 0.09f) });
	m_animations.insert({ PuppetAnimationType::knivesOperate,
		CAnimationKit::create("9.png", Rect(250, 0, 250, 250), 15, false, 0.07f) });
	m_animations.insert({ PuppetAnimationType::meleeAttack,
		CAnimationKit::create("test_attack_2.png", Rect(250, 0, 250, 164), 11, false, 0.06f) });
	m_animations.insert({ PuppetAnimationType::frostMageSwitch,
		CAnimationKit::create("stay_anim_frost_2.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::fireMageSwitch,
		CAnimationKit::create("stay_anim_fire.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::arcaneMageSwitch,
		CAnimationKit::create("stay_anim_arcan.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::castFrostBalt,
		CAnimationKit::create("frost_balt_cast.png", Rect(113, 0, 113, 155), 3, true, 0.23f) });
	m_animations.at(PuppetAnimationType::castFrostBalt)->getAction()->setTag(1);
}
