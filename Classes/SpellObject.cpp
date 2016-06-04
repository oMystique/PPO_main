#include "SpellObject.h"
#include "AnimationKit.h"

USING_NS_CC;

CSpellObject * CSpellObject::create(float velocityX, cocos2d::Vec2 const &spawnPos)
{
	CSpellObject * spellObject = new (std::nothrow) CSpellObject();
	if (spellObject && spellObject->init(velocityX, spawnPos))
	{
		spellObject->autorelease();
		return spellObject;
	}

	CC_SAFE_DELETE(spellObject);
	return NULL;
}

void CSpellObject::update(float dt)
{
	auto velocityX = m_phantomeSprite->getPhysicsBody()->getVelocity().x;
	if (abs(velocityX) < 600)
	{
		m_phantomeSprite->getPhysicsBody()->setVelocity({ velocityX * 1.1f, 0 });
	}
	m_sprite->setPosition(m_phantomeSprite->getPosition());
	if (m_phantomeSprite->getPhysicsBody()->getName() == "collideBalt")
	{
		removeFromParentAndCleanup(true);
	}
}

bool CSpellObject::init(float velocityX, cocos2d::Vec2 const &spawnPos)
{
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
	spriteBody->setCollisionBitmask(3);
	spriteBody->setMass(1);
	spriteBody->setVelocity({ velocityX, 0 });

	m_phantomeSprite->setPhysicsBody(spriteBody);
	addChild(m_phantomeSprite);

	auto anim = CAnimationKit::create("ice_balts_4.png", Rect(500, 0, 500, 88), 7, false, 0.12f);
	m_sprite->runAction(anim->getAction());

	scheduleUpdate();

	return true;
}
