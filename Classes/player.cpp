#include "Player.h"
#include "SpellObject.h"
#include "AudioEngine.h" 

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

	auto spriteBody = PhysicsBody::createEdgeBox(Size(50, 86), PhysicsMaterial(300, 0, 0), 4);
	spriteBody->setRotationEnable(false);
	spriteBody->setDynamic(true);
	spriteBody->setMass(50);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setCollisionBitmask(10);

	m_phantomeSprite->setPhysicsBody(spriteBody);
	addChild(m_phantomeSprite);

	pushAnimations();
	setAnimation(m_animations.at(PuppetAnimationType::stay));
}

void CPlayer::arcaneOperate()
{
	auto audio = experimental::AudioEngine::play2d("arcan_operate_.mp3");
	setAnimation(m_animations.at(PuppetAnimationType::arcaneMageSwitch));
}

void CPlayer::castFrostBalt()
{
	if (m_mana >= 10 && m_state == PuppetState::stay)
	{
		auto audio = experimental::AudioEngine::play2d("cast_fb_sound.mp3");
		m_interruptionCastTime = 60;
		m_castTimer = 0;
		schedule(schedule_selector(CPlayer::castTimer));
		setAnimation(m_animations.at(PuppetAnimationType::castFrostBalt));
	}
}

void CPlayer::castFireBalt()
{
	if (m_mana >= 20 && m_state == PuppetState::stay)
	{
		auto audio = experimental::AudioEngine::play2d("fire_cast_sound.mp3");
		m_interruptionCastTime = 100;
		m_castTimer = 0;
		schedule(schedule_selector(CPlayer::castTimer));
		setAnimation(m_animations.at(PuppetAnimationType::castFireBalt));
	}
}

void CPlayer::castArcanBlast()
{
	if (m_mana >= 3)
	{
		auto audio = experimental::AudioEngine::play2d("arcan_cast.ogg");
		m_interruptionCastTime = 20;
		m_castTimer = 0;
		schedule(schedule_selector(CPlayer::castTimer));
		setAnimation(m_animations.at(PuppetAnimationType::castArcanBlast));
	}
}

void CPlayer::useBonus(int bonusTag)
{
	switch (bonusTag)
	{
	case 1:
		m_health += 10;
		break;
	case 2:
		m_mana += 20;
		break;
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
	auto audio = experimental::AudioEngine::play2d("knives_operate.mp3");
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
	if (!m_puppetSprite->getActionByTag(30))
	{
		auto audio = experimental::AudioEngine::play2d("dagger_fight.mp3");
		m_isMeleeAttack = true;
		setAnimation(m_animations.at(PuppetAnimationType::meleeAttack));
	}
}

void CPlayer::fireOperate()
{
	auto audio = experimental::AudioEngine::play2d("fire_operate_.mp3");
	setAnimation(m_animations.at(PuppetAnimationType::fireMageSwitch));
}

void CPlayer::frostOperate()
{
	auto audio = experimental::AudioEngine::play2d("frost_operate_.mp3");
	setAnimation(m_animations.at(PuppetAnimationType::frostMageSwitch));
}

void CPlayer::update()
{
	if (m_phantomeSprite->getPhysicsBody()->getName() == "collideWithEnemyBalt")
	{
		m_health -= 10;
		m_phantomeSprite->getPhysicsBody()->setName("");
	}
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

void CPlayer::castSpell()
{
	CSpellObject * spell;
	if (m_puppetSprite->getActionByTag(1))
	{
		spell = CSpellObject::create(200 * m_puppetSprite->getScaleX(), getPosition()
			+ Vec2(getBoundingBox().size.width * m_puppetSprite->getScaleX(), -20), "ice_balts_4.png", 3, "frost_cast_die.png");
		hasBurnedMana(10);
	}
	else if (m_puppetSprite->getActionByTag(2))
	{
		spell = CSpellObject::create(200 * m_puppetSprite->getScaleX(), getPosition()
			+ Vec2(getBoundingBox().size.width * m_puppetSprite->getScaleX(), -20), "fire_balts.png", 4, "fire_cast_die.png");
		hasBurnedMana(10);
	}
	else if (m_puppetSprite->getActionByTag(3))
	{
		spell = CSpellObject::create(200 * m_puppetSprite->getScaleX(), getPosition()
			+ Vec2(getBoundingBox().size.width * m_puppetSprite->getScaleX(), -20), "arcan_balts.png", 7, "arcan_cast_die.png");
		hasBurnedMana(3);
	}
	addChild(spell);
}

void CPlayer::castTimer(float /*dt*/)
{
	if (m_state != PuppetState::stay)
	{
		m_castTimer = 0;
		unschedule(schedule_selector(CPlayer::castTimer));
		stopAllActions();
	}
	if (m_castTimer < m_interruptionCastTime)
	{
		++m_castTimer;
	}
	else
	{
		castSpell();
		unschedule(schedule_selector(CPlayer::castTimer));
		m_castTimer = 0;
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
	m_animations.at(PuppetAnimationType::meleeAttack)->getAction()->setTag(30);
	m_animations.insert({ PuppetAnimationType::frostMageSwitch,
		CAnimationKit::create("stay_anim_frost_2.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::fireMageSwitch,
		CAnimationKit::create("stay_anim_fire.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::arcaneMageSwitch,
		CAnimationKit::create("stay_anim_arcan.png", Rect(130, 0, 130, 211), 7, false, 0.15f) });
	m_animations.insert({ PuppetAnimationType::castFrostBalt,
		CAnimationKit::create("frost_balt_cast.png", Rect(113, 0, 113, 155), 3, true, 0.23f) });
	m_animations.at(PuppetAnimationType::castFrostBalt)->getAction()->setTag(1);
	m_animations.insert({ PuppetAnimationType::castFireBalt,
		CAnimationKit::create("fire_balt_cast.png", Rect(113, 0, 113, 155), 3, true, 0.23f) });
	m_animations.at(PuppetAnimationType::castFireBalt)->getAction()->setTag(2);
	m_animations.insert({ PuppetAnimationType::castArcanBlast,
		CAnimationKit::create("fire_balt_cast.png", Rect(113, 0, 113, 155), 2, true, 0.23f) });
	m_animations.at(PuppetAnimationType::castArcanBlast)->getAction()->setTag(3);
}
