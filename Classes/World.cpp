#include "World.h"
#include "UILayer.h"
#include "AudioEngine.h" 
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include <string>

USING_NS_CC;

CWorld * CWorld::create(int levelNumber)
{
	CWorld * world = new (std::nothrow) CWorld();
	if (world && world->init(levelNumber))
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

	if (m_flag->getBoundingBox().intersectsRect(m_finish->getBoundingBox()))
	{
		m_flag->setPosition(m_finish->getPosition() + Vec2(0, 60));
		m_flag->setScale(1);
		m_isFinished = true;
	}
	else if (m_flag->getBoundingBox().intersectsRect(m_playerPuppeteer->getPuppet()->getBoundingBox()))
	{
		m_flag->setPosition(m_playerPuppeteer->getPuppetPos() + Vec2(10, 40));
		m_flag->setScale(0.4);
	}

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
	if (getPlayerManaCount() >= 40)
	{
		auto audio = experimental::AudioEngine::play2d("fire_nova_sound_.mp3");
		auto m_actionAnim = CAnimationKit::create("cast_fire_circle.png", Rect(540, 0, 540, 198), 6, false, 0.15f);
		m_actionAnim->autorelease();
		m_action->stopAllActions();
		m_action->setTag(2);
		m_action->setPosition(Vec2(getPlayerPos().x, getPlayerPos().y + 50));
		m_action->runAction(m_actionAnim->getAction());
		m_playerPuppeteer->burnPuppetMana(40);
	}
}

CPlayer * CWorld::getPlayer()const
{
	return m_playerPuppeteer->getPuppet();
}

bool CWorld::isFinished()const
{
	return m_isFinished;
}

bool CWorld::init(int levelNumber)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"Instrumental_Core_Other Worlds.mp3", true);
	m_level = new CLevel();
	m_level->loadMap("TileGameResources/map" + std::to_string(levelNumber) + ".tmx");
	addChild(m_level->getMap());

	m_flag = Sprite::create();
	m_flag->initWithFile("flag.png");
	m_flag->setPosition(m_level->getObjectPos("flag"));
	addChild(m_flag);

	m_finish = Sprite::create();
	m_finish->initWithFile("finish.png");
	m_finish->setPosition(m_level->getObjectPos("finish"));
	m_finish->setScale(0.3);
	addChild(m_finish);

	m_cameraTarget = Sprite::create();
	addChild(m_cameraTarget);
	auto camera = Follow::create(m_cameraTarget, Rect::ZERO);
	runAction(camera);

	createBonuses();

	m_playerPuppeteer = CPlayerPuppeteer::create(m_level->getObjectPos("player"));
	addChild(m_playerPuppeteer);

	createEnemyPuppeteers();

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
		auto audio = experimental::AudioEngine::play2d("frost_nove_sound.ogg");
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
	else if ((1 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask())
		|| (7 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (7 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("collideWithArcanBlast");
		b->setName("collideWithArcanBlast");
	}
	else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
		|| (4 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("collideWithFireBalt");
		b->setName("collideWithFireBalt");
	}
	else if ((5 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
		|| (10 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
		|| (5 == a->getCollisionBitmask() && 10 == b->getCollisionBitmask())
		|| (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())
		|| (1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
		|| (5 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask())
		|| (4 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
		|| (5 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask())
		|| (3 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask())
		|| (5 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask())
		|| (7 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask()))
	{
		a->setName("collideWithEnemyBalt");
		b->setName("collideWithEnemyBalt");
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
	m_bonuses = m_level->getObjects<CBonus>("healthBonuses");
	for_each(m_bonuses.begin(), m_bonuses.end(), [this](CBonus * bonus) {
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
		m_bonuses.push_back(bonus);
	});
	//std::merge(healthBonuses.begin(), healthBonuses.end(),
	//	manaBonuses.begin(), manaBonuses.end(),
	//	std::back_inserter(m_bonuses));
}

void CWorld::createEnemyPuppeteers()
{
	m_enemyPuppeteers = m_level->getObjects<CEnemyPuppeteer>("meleeEnemies");
	for_each(m_enemyPuppeteers.begin(), m_enemyPuppeteers.end(), [this](CEnemyPuppeteer * puppeteer) {
		puppeteer->getPuppet()->pushMeleeEnemyAnimations();
		addChild(puppeteer);
	});

	auto rangeEnemyPuppeteers = m_level->getObjects<CEnemyPuppeteer>("rangeEnemies");
	for_each(rangeEnemyPuppeteers.begin(), rangeEnemyPuppeteers.end(), [this](CEnemyPuppeteer * puppeteer) {
		puppeteer->getPuppet()->pushRangeEnemyAnimations();
		addChild(puppeteer);
		m_enemyPuppeteers.push_back(puppeteer);
	});

	//std::merge(rangeEnemyPuppeteers.begin(), rangeEnemyPuppeteers.end(),
	//	meleeEnemyPuppeteers.begin(), meleeEnemyPuppeteers.end(),
	//	std::back_inserter(m_enemyPuppeteers));
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

