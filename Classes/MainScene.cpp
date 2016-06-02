#include "MainScene.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
//GAME LAYER
// stackoverflow.com/questions/33286400/how-to-get-the-current-position-of-my-screen-in-cocos2d

Scene* CMainScene::createScene()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *_background = Sprite::create();
	_background->initWithFile("background.png");
	_background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto scene = Scene::createWithPhysics();
    auto layer = make_cc<CMainScene>();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -500));
	//scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);

	scene->addChild(_background);
    scene->addChild(layer);
	scene->addChild(layer->uiLayer);
    return scene;
}

bool CMainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	m_level = new CLevel();
    m_level->loadMap("TileGameResources/map1.tmx");

	this->addChild(m_level->getMap());

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CMainScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CMainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	CCTMXObjectGroup *objectGroup = m_level->getMap()->objectGroupNamed("Objects");
	
	auto spawnPoint = objectGroup->objectNamed("player");

	Point playerPos = { spawnPoint.at("x").asFloat(), spawnPoint.at("y").asFloat() + 150};
	
	auto spawnEnemy = objectGroup->objectNamed("easyEnemy");
	Point enemyPos = { spawnEnemy.at("x").asFloat(), spawnEnemy.at("y").asFloat() };
	
	m_enemyPuppeteer = CEnemyPuppeteer::create(enemyPos);
	addChild(m_enemyPuppeteer);

	m_playerPuppeteer = CPlayerPuppeteer::create(playerPos);
	addChild(m_playerPuppeteer);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(m_playerPuppeteer->getPuppetPos().x);
	cameraTarget->setPositionY(visibleSize.height + origin.y);

	this->addChild(cameraTarget);

	auto camera = Follow::create(cameraTarget, Rect::ZERO);
	this->runAction(camera);


	uiLayer = Layer::create();

	m_toolbar = CToolbarManager::createBaseToolbar(visibleSize, m_playerPuppeteer->getPuppet(), this);
	uiLayer->addChild(m_toolbar);
	
	m_lifeBar = CLifeBar::create(Vec2(visibleSize.width * 0.13f, visibleSize.height * 1.05f),
					Vec2(visibleSize.width * 0.124f, visibleSize.height * 1.055f),
					Vec2(visibleSize.width * 0.126f, visibleSize.height * 1.026f),
				"hp_bar_1.png", "hp.png", "mana.png");
	uiLayer->addChild(m_lifeBar);

	createJoystick();
	uiLayer->addChild(joystickBase);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CMainScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

	m_action = Sprite::create();
	addChild(m_action);

    return true;
}

void CMainScene::createJoystick()
{
	CCRect joystickBaseDimensions;
	joystickBaseDimensions = CCRectMake(0, 0, 160.0f, 160.0f);

	CCPoint joystickBasePosition;
	joystickBasePosition = ccp(visibleSize.width * 0.1f, visibleSize.height*0.35f);

	joystickBase = SneakyJoystickSkinnedBase::create();
	joystickBase->init();
	joystickBase->setPosition(joystickBasePosition);
	joystickBase->setBackgroundSprite(CCSprite::create("joystick_background.png"));
	joystickBase->setThumbSprite(CCSprite::create("joystick_thumb.png"));

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(joystickBasePosition);
}

void CMainScene::update(float dt)
{

	cameraTarget->setPosition(m_playerPuppeteer->getPuppetPos().x, m_playerPuppeteer->getPuppetPos().y);

	m_playerPuppeteer->update(joystickBase->getJoystick()->getStickPosition());

	m_lifeBar->update(m_playerPuppeteer->getPuppet()->getHealthCount(), m_playerPuppeteer->getPuppet()->getManaCount());

	if (m_enemyPuppeteer && !m_enemyPuppeteer->hasPuppet())
	{
		if (m_action->getNumberOfRunningActions() == 0)
		{
			m_action->setTag(0);
		}
		else
		{
			if (m_enemyPuppeteer->getPuppet()->getBoundingBox().intersectsRect(m_action->getBoundingBox()))
			{
				m_enemyPuppeteer->puppetHasAttackedByMagic(m_action->getTag());
			}
		}
		m_enemyPuppeteer->update(m_playerPuppeteer->getPuppetPos(), m_playerPuppeteer->getPuppet()->getBoundingBox(), m_playerPuppeteer->isAttack());
		if (m_enemyPuppeteer->isAttack())
		{
			m_playerPuppeteer->damagePuppet(3);
		}
	}
	else
	{
		m_enemyPuppeteer->removeFromParent();

	}
}

bool CMainScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void CMainScene::onTouchEnded(Touch *touch, Event *event)
{
	m_playerPuppeteer->getPuppet()->idle();
}

bool CMainScene::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask())
		|| (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		a->setName("toOther!");
		b->setName("toOther!");
	}

	return true;
}


void CMainScene::createFrostToolbar()
{
	if (m_addToolbar != nullptr)
	{
		uiLayer->removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createFrostToolbar(visibleSize, m_playerPuppeteer->getPuppet(), this);
	uiLayer->addChild(m_addToolbar);
}


void CMainScene::createAttackToolbar()
{
	if (m_addToolbar != nullptr)
	{
		uiLayer->removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createMeleeToolbar(visibleSize, m_playerPuppeteer->getPuppet());
	uiLayer->addChild(m_addToolbar);
}


void CMainScene::frostCircle()
{
	if (m_playerPuppeteer->getPuppet()->getManaCount() >= 5)
	{
		auto m_actionAnim = CAnimationKit::create("frost_circle.png", Rect(540, 0, 540, 198), 6, false, 0.13f);
		m_actionAnim->autorelease();
		m_action->stopAllActions();
		m_action->setTag(1);
		m_action->setPosition(Vec2(m_playerPuppeteer->getPuppetPos().x, m_playerPuppeteer->getPuppetPos().y + 50));
		m_action->runAction(m_actionAnim->getAction());
		m_playerPuppeteer->burnPuppetMana(5);
	}
}

void CMainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
