#include "Enemy.h"

USING_NS_CC;

CEnemy * CEnemy::create()
{
	CEnemy * enemy = new (std::nothrow) CEnemy();
	if (enemy && enemy->initWithFile("easy_enemy_walk.png"))
	{
		enemy->autorelease();
		enemy->initEnemy();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);

	return NULL;
}

void CEnemy::initEnemy()
{
	m_runAnimation = CAnimationKit::create("easy_enemy_walk.png", Rect(150, 0, 150, 106), 2, true, 0.2f);
	m_attackAnimation = CAnimationKit::create("easyFight.png", Rect(150, 0, 150, 106), 2, true, 0.2f);
	runAction(m_runAnimation->getAction()); 

	m_state = EnemyAction::moveLeft;

	setScaleY(0.6);

	emptySprite = Sprite::create();
	emptySprite->initWithFile("stay.png");
	emptySprite->setColor(Color3B::RED);
	emptySprite->setVisible(false);
	m_pSpriteBody = PhysicsBody::createEdgeBox(Size(70, 50), PhysicsMaterial(300, 0, 0));
	m_pSpriteBody->setRotationEnable(false);
	m_pSpriteBody->setCollisionBitmask(1);
	m_pSpriteBody->setContactTestBitmask(true);

	m_pSpriteBody->setDynamic(true);
	m_pSpriteBody->setMass(50);
	emptySprite->setPhysicsBody(m_pSpriteBody);
}

void CEnemy::update()
{
	if (m_state == EnemyAction::moveLeft)
	{
		this->setScaleX(-0.6);
		if (emptySprite->getPhysicsBody()->getVelocity().x > -200)
		{
			emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x - 20, emptySprite->getPhysicsBody()->getVelocity().y));
		}

	}
	else if (m_state == EnemyAction::moveRight)
	{
		this->setScaleX(0.6);
		if (emptySprite->getPhysicsBody()->getVelocity().x < 200)
		{
			emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x + 20, emptySprite->getPhysicsBody()->getVelocity().y));
		}
	}
	if (emptySprite->getPhysicsBody()->getName() == "toOther!") 
	{
		if (m_isPursuitTarget)
		{
			if (emptySprite->getPhysicsBody()->getVelocity().y < 10)
			{
				jumpPos = emptySprite->getPosition();
				emptySprite->getPhysicsBody()->setVelocity(Vec2(emptySprite->getPhysicsBody()->getVelocity().x, emptySprite->getPhysicsBody()->getVelocity().y + 200));
			}
			else if (abs(jumpPos.y - emptySprite->getPosition().y) < 73)
			{
				jumpPos = Vec2(0, 0);
			}
		}
		else
		{
			if (m_state == EnemyAction::moveLeft)
			{
				m_state = EnemyAction::moveRight;
			}
			else if (m_state == EnemyAction::moveRight)
			{
				m_state = EnemyAction::moveLeft;
			}
		}
		emptySprite->getPhysicsBody()->setName("");
	}
	setPosition(emptySprite->getPosition());
}

void CEnemy::attack()
{
	m_pSpriteBody->setVelocity(Vec2(0, m_pSpriteBody->getVelocity().y));
	m_state = EnemyAction::attack;
	setAnimation(m_attackAnimation);
}

void CEnemy::idle()
{
	setAnimation(m_runAnimation);
}

void CEnemy::setAnimation(CAnimationKit * kit)
{
	stopAllActions();
	runAction(kit->getAction());
}
