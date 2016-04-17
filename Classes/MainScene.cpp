#include "MainScene.h"

USING_NS_CC;

Scene* CMainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CMainScene::create();
    scene->addChild(layer);
    return scene;
}

bool CMainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CMainScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CMainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	player = CPlayer::create();
	player->setPosition(Vec2(origin.x + visibleSize.width / 2
		, origin.y + visibleSize.height / 2));

	this->addChild(player, 1);

	m_toolbar = CToolbarManager::createBaseToolbar(visibleSize, player, this);

	addChild(m_toolbar);

	createJoystick();

	this->scheduleUpdate();

    return true;
}


void CMainScene::createJoystick()
{
	CCRect joystickBaseDimensions;
	joystickBaseDimensions = CCRectMake(0, 0, 160.0f, 160.0f);

	CCPoint joystickBasePosition;
	joystickBasePosition = ccp(visibleSize.width * 0.1f, visibleSize.height*0.25f);

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

	this->addChild(joystickBase);
}

void CMainScene::update(float dt)
{
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
	}
	player->update();
}

bool CMainScene::onTouchBegan(Touch *touch, Event *event)
{
	//if (touch->getLocation().x < player->getPositionX())
	//{
	//	player->move(0); // param '0' for left
	//}
	//if (touch->getLocation().x > player->getPositionX())
	//{
	//	player->move(1); // param '0' for right
	//}
	return true;
}

void CMainScene::onTouchEnded(Touch *touch, Event *event)
{
	player->idle();
}


void CMainScene::createFrostToolbar()
{
	if (m_addToolbar != nullptr)
	{
		removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createFrostToolbar(visibleSize, player);
	addChild(m_addToolbar);
}


void CMainScene::createAttackToolbar()
{
	if (m_addToolbar != nullptr)
	{
		removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createMeleeToolbar(visibleSize, player);
	addChild(m_addToolbar);
}


void CMainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
