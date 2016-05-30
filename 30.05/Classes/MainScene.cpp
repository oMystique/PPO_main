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
	//_tileMap->setScale(2);

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

	enemy2 = CEnemy::create();
	enemy2->emptySprite->setPosition(Vec2(enemyPos.x + 300, enemyPos.y));
	addChild(enemy2->emptySprite);
	addChild(enemy2);
	
	enemy = CEnemy::create();
	enemy->emptySprite->setPosition(Vec2(enemyPos.x, enemyPos.y));
	addChild(enemy->emptySprite);
	addChild(enemy);

	player = CPlayer::create();
	//player->setPosition(Vec2(playerPos.x, playerPos.y));
	player->emptySprite->setPosition(Vec2(playerPos.x, playerPos.y));
	player->setScale(0.6f);
	
	addChild(player->emptySprite);

	addChild(player, 1);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(player->getPosition().x); // set to players x
	cameraTarget->setPositionY(visibleSize.height + origin.y); // center of height

	this->addChild(cameraTarget);

	auto camera = Follow::create(cameraTarget, Rect::ZERO);

	this->runAction(camera);

	m_toolbar = CToolbarManager::createBaseToolbar(visibleSize, player, this);

	uiLayer = Layer::create();

	uiLayer->addChild(m_toolbar);
	
	m_lifeBar = CLifeBar::create(Point(visibleSize.width * 0.13f, visibleSize.height * 0.92f),
					Point(visibleSize.width * 0.175f, visibleSize.height * 0.935f),
					Point(visibleSize.width * 0.176f, visibleSize.height * 0.91f));
	uiLayer->addChild(m_lifeBar);

	createJoystick();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CMainScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

	m_action = Sprite::create();
	addChild(m_action);

    return true;
}

CCPoint CMainScene::tileCoordForPosition(CCPoint position)
{
	int x = position.x / m_level->getMap()->getTileSize().width;
	int y = ((m_level->getMap()->getMapSize().height * m_level->getMap()->getTileSize().height) - position.y) / m_level->getMap()->getTileSize().height;
	return ccp(x, y);
}


void CMainScene::createJoystick()
{
	CCRect joystickBaseDimensions;
	joystickBaseDimensions = CCRectMake(0, 0, 160.0f, 160.0f);

	CCPoint joystickBasePosition;
	joystickBasePosition = ccp(visibleSize.width * 0.1f, visibleSize.height*0.17f);

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

	uiLayer->addChild(joystickBase);
}

void CMainScene::update(float dt)
{
	cameraTarget->setPositionX(player->getPosition().x);
	enemy->m_isPursuitTarget = false;
	if (joystickBase->getJoystick()->getStickPosition().x < 0)
	{
		player->move(PlayerState::moveLeft);
	}
	else if (joystickBase->getJoystick()->getStickPosition().x > 0)
	{
		player->move(PlayerState::moveRight);
	}
	else if (joystickBase->getJoystick()->getStickPosition().x == 0)
	{
		player->idle();
	};
	if (joystickBase->getJoystick()->getStickPosition().y > 50)
	{
		player->m_isJump = true;
	}
	if (abs(enemy->getPosition().x - player->getPosition().x) < 200)
	{
		if (enemy->getBoundingBox().intersectsRect(player->getBoundingBox()))
		{
			if (enemy->m_state != EnemyAction::attack)
				enemy->attack();
		}
		else
		{
			enemy->m_isPursuitTarget = true;
			if (enemy->m_state == EnemyAction::attack)
			{
				enemy->idle();
			}
			if (enemy->getPosition().x < player->getPosition().x)
			{
				enemy->m_state = EnemyAction::moveRight;
			}
			else
			{
				enemy->m_state = EnemyAction::moveLeft;
			}
		}
	}
	player->update();
	enemy->update();
	enemy2->update();
}

bool CMainScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void CMainScene::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
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
	m_addToolbar = CToolbarManager::createFrostToolbar(visibleSize, player, this);
	uiLayer->addChild(m_addToolbar);
}


void CMainScene::createAttackToolbar()
{
	if (m_addToolbar != nullptr)
	{
		uiLayer->removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createMeleeToolbar(visibleSize, player);
	uiLayer->addChild(m_addToolbar);
}


void CMainScene::frostCircle()
{
	auto m_actionAnim = CAnimationKit::create("frost_circle.png", Rect(540, 0, 540, 198), 6, false, 0.13f);
	m_actionAnim->autorelease();
	m_action->stopAllActions();
	m_action->setPosition(Vec2(player->getPosition().x, player->getPosition().y + 50));
	m_action->runAction(m_actionAnim->getAction());
}

void CMainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
