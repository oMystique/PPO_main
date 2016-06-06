#include "MainScene.h"
#include "MainMenuScene.h"

USING_NS_CC;
#define COCOS2D_DEBUG 1

Scene* CMainScene::createScene(int levelNumber)
{
    auto scene = Scene::createWithPhysics();
	auto layer = new (std::nothrow) CMainScene();
	if (layer && layer->init(levelNumber))
	{
		scene->getPhysicsWorld()->setGravity(Vec2(0, -500));
		scene->addChild(layer);
		return scene;
	}

	CC_SAFE_DELETE(layer);
	CC_SAFE_DELETE(scene);
	return nullptr;
}

bool CMainScene::init(int levelNumber)
{
    if ( !Layer::init() )
    {
        return false;
    }

	m_levelNumber = levelNumber;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = make_cc<Sprite>();
	background->initWithFile("background.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x
		, visibleSize.height / 2 + origin.y));
	addChild(background);

	m_world = CWorld::create(m_levelNumber);
	m_gameUI = CUILayer::create(m_world);
	m_world->setPtrToUiLayer(m_gameUI);

	addChild(m_world);
	addChild(m_gameUI);

	m_restartItem = MenuItemImage::create("restartButton.png", "restartButton.png", CC_CALLBACK_1(CMainScene::restartLevel, this));
	m_restartItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height + 30));
	m_restartItem->setScale(0.23f);
	auto menu = Menu::create(m_restartItem, NULL);
	menu->setPosition(Point::ZERO);
	addChild(menu, 20);

	scheduleUpdate();

    return true;
}

void CMainScene::update(float dt)
{
	if (m_world->isFinished())
	{
		m_levelNumber <= 1 ?
			CCDirector::getInstance()->replaceScene(CMainScene::createScene(m_levelNumber + 1)) :
			CCDirector::getInstance()->replaceScene(CMainMenuScene::createScene());
	}
	else if (m_world->getPlayerHealthCount() <= 0)
	{
		m_gameUI->removeAllChildren();
		createGameOverPlash();
		unscheduleUpdate();
	}
	else
	{
		m_world->update();
		m_gameUI->update();
	}
}

void CMainScene::restartLevel(cocos2d::Ref * sender)
{
	CCDirector::getInstance()->replaceScene(CMainScene::createScene(m_levelNumber));
}

void CMainScene::createGameOverPlash()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto gameOverTable = Sprite::create();
	gameOverTable->initWithFile("death.png");
	gameOverTable->setScale(0.95f);
	gameOverTable->setPosition(visibleSize / 2 + Size(0, 100));
	m_restartItem->setPosition(visibleSize / 2 + Size(230, -82));
	addChild(gameOverTable);

}

void CMainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
