#include "Puppet.h"

USING_NS_CC;

const cocos2d::Vec2 & CPuppet::getPosition() const
{
	return m_puppetSprite->getPosition();
}

cocos2d::Rect CPuppet::getBoundingBox() const
{
	return m_puppetSprite->getBoundingBox();
}

int CPuppet::getHealthCount() const
{
	return m_health;
}

PuppetState const & CPuppet::getState() const
{
	return m_state;
}

bool CPuppet::isAlive() const
{
	return m_isAlive;
}

void CPuppet::hasDamaged(int healthCount)
{
	m_health -= healthCount;
}

void CPuppet::move(PuppetState const & state)
{
	if (m_health < 0)
	{
		return;
	}
	int sign = static_cast<int>(state);
	if (((sign > 0) && (getVelocity().x < m_velocityX))
		|| ((sign < 0) && (getVelocity().x > -m_velocityX)))
	{
		m_puppetSprite->setScaleX(0.6f * sign);
		setVelocity(Vec2(getVelocity().x + 20 * sign, getVelocity().y));
	}
	if (state != m_state && isCanJump())
	{
		setAnimation(m_animations.at(PuppetAnimationType::move));
	}
}

void CPuppet::jump()
{
	if (isCanJump())
	{
		jumpPos = m_phantomeSprite->getPosition();
		setVelocity(Vec2(getVelocity().x, getVelocity().y + 200));
	}
	else if (abs(jumpPos.y - getPosition().y) < 73)
	{
		jumpPos = Vec2(0, 0);
	}
}

void CPuppet::setAnimation(CAnimationKit * kit)
{
	m_puppetSprite->stopAllActions();
	m_puppetSprite->runAction(kit->getAction());
}

cocos2d::Vec2 CPuppet::getVelocity() const
{
	return m_phantomeSprite->getPhysicsBody()->getVelocity();
}

void CPuppet::setVelocity(cocos2d::Vec2 const & velocity)
{
	m_phantomeSprite->getPhysicsBody()->setVelocity(velocity);
}

bool CPuppet::isCanJump() const
{
	return getVelocity().y == 0 && jumpPos.y == 0;
}
