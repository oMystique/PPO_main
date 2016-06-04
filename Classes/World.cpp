#include "World.h"
#include "UILayer.h"

USING_NS_CC;

CWorld * CWorld::create()
{
	CWorld * world = new (std::nothrow) CWorld();
	if (world && world->init())
	{
		world->autorelease();
		return world;
	}
	CC_SAFE_DELETE(world);

	return nullptr;
}

void CWorld::update()
{
	m_cameraTarget->setPosition(getPlayerPos().x, getPlayerPos().y);

	updateEnemyPuppeteers();

	m_playerPuppeteer->update(m_uiLayer->getJoystickPosition());

	updateBonuses();

	if (m_action->getNumberOfRunningActions() == 0)
	{
		m_action->setTag(0);
	}
}

void CWorld::setPtrToUiLayer(CUILayer * uiLayer)
{
	m_uiLayer = uiLayer;
}

cocos2d::Vec2 CWorld::getPlayerPos() const
{
	return m_playerPuppeteer->getPuppetPos();
}

int CWorld::getPlayerHealthCount() const
{
	return m_playerPuppeteer->getPuppet()->getHealthCount();
}

int CWorld::getPlayerManaCount() const
{
	return m_playerPuppeteer->getPuppet()->getManaCount();
}

void CWorld::createFireCircle()
{
	if (getPlayerManaCount() >= 30)
	{
		auto m_actionAnim = CAnimationKit::create("cast_fire_circle.png", Rect(540, 0, 540, 198), 6, false, 0.15f);
		m_actionAnim->autorelease();
		m_action->stopAllActions();
		m_action->setTag(2);
		m_action->setPosition(Vec2(getPlayerPos().x, getPlayerPos().y + 50));
		m_action->runAction(m_actionAnim->getAction());
		m_playerPuppeteer->burnPuppetMana(40);
	}
}

CPlayer * CWorld::getPlayer()
{
	return m_playerPuppeteer->getPuppet();
}

bool CWorld::init()
{
	m_level = new CLevel();
	m_level->loadMap("TileGameResources/map1.tmx");
	addChild(m_level->getMap());

	m_cameraTarget = Sprite::create();
	addChild(m_cameraTarget);
	auto camera = Follow::create(m_cameraTarget, Rect::ZERO);
	runAction(camera);

	m_playerPuppeteer = CPlayerPuppeteer::create(m_level->getPlayerPos("player"));
	addChild(m_playerPuppeteer);

	m_enemyPuppeteers = m_level->getObjects<CEnemyPuppeteer>("Enemies");
	for_each(m_enemyPuppeteers.begin(), m_enemyPuppeteers.end(), [this](CEnemyPuppeteer * puppeteer) {
		addChild(puppeteer);
	});

	createBonuses();

	m_action = Sprite::create();
	addChild(m_action);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

	return true;
}


void CWorld::createFrostCircle()
{
	if (getPlayerManaCount() >= 5)
	{
		auto m_actionAnim = CAnimationKit::create("frost_circle.png", Rect(540, 0, 540, 198), 6, false, 0.13f);
		m_actionAnim->autorelease();
		m_action->stopAllActions();
		m_action->setTag(1);
		m_action->setPosition(Vec2(getPlayerPos().x, getPlayerPos().y + 50));
		m_action->runAction(m_actionAnim->getAction());
		m_playerPuppeteer->burnPuppetMana(5);
	}
}

bool CWorld::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("toOther!");
		b->setName("toOther!");
	}
	else if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask())
		|| (3 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("collideWithFrostBalt");
		b->setName("collideWithFrostBalt");
	}
	else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
		|| (4 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("collideWithFireBalt");
		b->setName("collideWithFireBalt");
	}

	return true;
}

void CWorld::fightEnemyPuppeteerEvents(CEnemyPuppeteer * enemyPuppeteer)
{
	if (enemyPuppeteer->getPuppet()->getBoundingBox()
		.intersectsRect(m_action->getBoundingBox()))
	{
		enemyPuppeteer->puppetHasAttackedByMagic(m_action->getTag());
	}
	if (enemyPuppeteer->isAttack())
	{
		m_playerPuppeteer->damagePuppet(2);
	}
}

void CWorld::createBonuses()
{
	auto healthBonuses = m_level->getObjects<CBonus>("healthBonuses");
	for_each(healthBonuses.begin(), healthBonuses.end(), [this](CBonus * bonus) {
		bonus->initWithFile("health_bonus.png");
		bonus->setPhysicsBodyForBonus();
		bonus->setTag(1);
		addChild(bonus);
	});

	auto manaBonuses = m_level->getObjects<CBonus>("manaBonuses");
	for_each(manaBonuses.begin(), manaBonuses.end(), [this](CBonus * bonus) {
		bonus->initWithFile("mana_bonus.png");
		bonus->setPhysicsBodyForBonus();
		bonus->setTag(2);
		addChild(bonus);
	});
	std::merge(healthBonuses.begin(), healthBonuses.end(), manaBonuses.begin(), manaBonuses.end(), std::back_inserter(m_bonuses));
}

void CWorld::updateBonuses()
{
	for (auto it = m_bonuses.begin(); it != m_bonuses.end();)
	{
		auto bonus = *it;
		if (bonus->getBoundingBox().intersectsRect(m_playerPuppeteer->getPuppet()->getBoundingBox()) 
			&& m_playerPuppeteer->puppetIsNeedBonus(bonus->getTag()))
		{
			bonus->removeFromParentAndCleanup(true);
			m_bonuses.erase(it);
			break;
		}
		++it;
	}
}

void CWorld::updateEnemyPuppeteers()
{
	auto playerIsAttack = m_playerPuppeteer->isAttack();
	for (auto it = m_enemyPuppeteers.begin(); it != m_enemyPuppeteers.end();)
	{
		auto enemyPuppeteer = *it;
		if (!enemyPuppeteer->hasPuppet())
		{
			enemyPuppeteer->interactWithPlayer(m_playerPuppeteer->getPuppetPos(),
				m_playerPuppeteer->getPuppet()->getBoundingBox(),
				playerIsAttack);
			fightEnemyPuppeteerEvents(enemyPuppeteer);
			enemyPuppeteer->update();
			++it;
		}
		else
		{
			m_enemyPuppeteers.erase(it);
			enemyPuppeteer->removeFromParent();
			break;
		}
	}
}
