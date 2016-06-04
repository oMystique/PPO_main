#include "Bonus.h"

USING_NS_CC;

CBonus * CBonus::create(cocos2d::Vec2 const & pos)
{
	CBonus * bonus = new (std::nothrow) CBonus();
	if (bonus && bonus->init(pos))
	{
		bonus->autorelease();
		return bonus;
	}

	CC_SAFE_DELETE(bonus);
	return NULL;
}

void CBonus::setPhysicsBodyForBonus()
{
	auto spriteBody = PhysicsBody::createEdgeBox(Size(50, 50), PhysicsMaterial(300, 0, 0));
	spriteBody->setGravityEnable(false);
	spriteBody->setRotationEnable(false);
	spriteBody->setDynamic(true);
	spriteBody->setMass(500);
	setPhysicsBody(spriteBody);

	scheduleUpdate();
}

void CBonus::update(float dt)
{
	if (abs(getPositionY() - m_soarStartPosY) > 43)
	{
		getPhysicsBody()->setVelocity({ 0, -20 });
	}
	else if (getPositionY() <= m_soarStartPosY)
	{
		getPhysicsBody()->setVelocity({ 0, 20 });
	}
}

bool CBonus::init(cocos2d::Vec2 const & pos)
{
	setPosition(pos);

	m_soarStartPosY = pos.y;

	scheduleUpdate();
	return true;
}
