#include "SpellObject.h"
#include "AnimationKit.h"

#include "AudioEngine.h" 
USING_NS_CC;

CSpellObject * CSpellObject::create(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask, std::string const &dieImagePath)
{
	CSpellObject * spellObject = new (std::nothrow) CSpellObject();
	if (spellObject && spellObject->init(velocityX, spawnPos, imagePath, collisionBitmask, dieImagePath))
	{
		spellObject->autorelease();
		return spellObject;
	}

	CC_SAFE_DELETE(spellObject);
	return NULL;
}

void CSpellObject::update(float dt)
{
	if (m_dieTimer == 0)
	{
		auto velocityX = m_phantomeSprite->getPhysicsBody()->getVelocity().x;
		if (abs(velocityX) < 600)
		{
			m_phantomeSprite->getPhysicsBody()->setVelocity({ velocityX * 1.1f, 0 });
		}
		m_sprite->setPosition(m_phantomeSprite->getPosition());
		auto name = m_phantomeSprite->getPhysicsBody()->getName();
		if (name == "collideWithFrostBalt" ||
			name == "collideWithFireBalt" ||
			name == "collideWithArcanBlast" ||
			name == "collideWithEnemyBalt")
		{
			die();
		}
	}
}

bool CSpellObject::init(float velocityX, cocos2d::Vec2 const &spawnPos, std::string const &imagePath, int collisionBitmask, std::string const &dieImagePath)
{
	m_dieImagePath = dieImagePath;

	m_sprite = Sprite::create();
	velocityX > 0 ? m_sprite->setScale(0.6f) : m_sprite->setScale(-0.6f);
	m_sprite->setPosition(spawnPos);
	addChild(m_sprite);

	m_phantomeSprite = Sprite::create();
	m_phantomeSprite->initWithFile("stay.png");
	m_phantomeSprite->setVisible(false);
	m_phantomeSprite->setPosition(spawnPos);

	auto spriteBody = PhysicsBody::createCircle(7, PhysicsMaterial(1000, 0, 0));
	spriteBody->setDynamic(true);
	spriteBody->setGravityEnable(false);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setCollisionBitmask(collisionBitmask);
	spriteBody->setMass(1);
	spriteBody->setVelocity({ velocityX, 0 });

	m_phantomeSprite->setPhysicsBody(spriteBody);
	addChild(m_phantomeSprite);

	auto anim = CAnimationKit::create(imagePath, Rect(500, 0, 500, 88), 7, false, 0.12f);
	m_sprite->runAction(anim->getAction());

	scheduleUpdate();

	return true;
}

void CSpellObject::dieTimer(float dt)
{
	if (m_dieTimer < 40)
	{
		++m_dieTimer;
	}
	else
	{
		//unschedule(schedule_selector(CSpellObject::dieTimer));
		removeFromParentAndCleanup(true);
	}
}

void CSpellObject::die()
{
	m_dieTimer = 1;
	m_sprite->stopAllActions();
	m_sprite->runAction(CAnimationKit::create(m_dieImagePath, Rect(150, 0, 150, 106), 6, false, 0.07f)->getAction());
	m_phantomeSprite->setPosition(Vec2(0, 0));
	schedule(schedule_selector(CSpellObject::dieTimer));
}