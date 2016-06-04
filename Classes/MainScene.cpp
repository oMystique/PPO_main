#include "MainScene.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1
//GAME LAYER
// stackoverflow.com/questions/33286400/how-to-get-the-current-position-of-my-screen-in-cocos2d

Scene* CMainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = make_cc<CMainScene>();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -500));

//	scene->getPhysicsWorld()->setDebugDrawMask(scene->getPhysicsWorld()->DEBUGDRAW_ALL);

    scene->addChild(layer);
    return scene;
}

bool CMainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = make_cc<Sprite>();
	background->initWithFile("background.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x
		, visibleSize.height / 2 + origin.y));
	addChild(background);

	m_world = make_cc<CWorld>();
	m_gameUI = CUILayer::create(m_world);
	m_world->setPtrToUiLayer(m_gameUI);

	addChild(m_world);
	addChild(m_gameUI);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CMainScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CMainScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

    return true;
}

void CMainScene::update(float dt)
{
	m_world->update();
	m_gameUI->update();
}

bool CMainScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void CMainScene::onTouchEnded(Touch *touch, Event *event)
{
}

void CMainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
