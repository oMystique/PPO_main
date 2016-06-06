#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* CMainMenuScene::createScene()
{
	auto scene = make_cc<Scene>();
	auto layer = make_cc<CMainMenuScene>();
	scene->addChild(layer);
	return scene;
}

bool CMainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("background_menu.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//backgroundSprite->setScale(BACKGROUND_SPRITE_SCALE);
	this->addChild(backgroundSprite);

	{
		auto playItem = MenuItemImage::create("play_button.png", "play_button_pressed.png",
			CC_CALLBACK_1(CMainMenuScene::goToGameScene, this));
		playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
		auto menu = Menu::create(playItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
	}
	{
		auto playItem = MenuItemImage::create("how_to_play_button.png", "how_to_play_button_pressed.png",
			CC_CALLBACK_1(CMainMenuScene::createHowToGameTable, this));
		playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 40));
		auto menu = Menu::create(playItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
	}
	{
		auto playItem = MenuItemImage::create("about_button.png", "about_button_pressed.png",
			CC_CALLBACK_1(CMainMenuScene::createAboutTable, this));
		playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 70));
		auto menu = Menu::create(playItem, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CMainMenuScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	return true;
}

void CMainMenuScene::createHowToGameTable(cocos2d::Ref *sender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_additionTable = Sprite::create();
	m_additionTable->initWithFile("how_to_play.png");
	m_additionTable->setScale(0.95f);
	m_additionTable->setPosition(visibleSize / 2 + Size(0, 100));
	addChild(m_additionTable);
}

void CMainMenuScene::createAboutTable(cocos2d::Ref *sender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_additionTable = Sprite::create();
	m_additionTable->initWithFile("about.png");
	m_additionTable->setScale(0.95f);
	m_additionTable->setPosition(visibleSize / 2 + Size(0, 100));
	addChild(m_additionTable);
}


bool CMainMenuScene::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (m_additionTable)
	{
		m_additionTable->removeFromParentAndCleanup(true);
	}
	return true;
}

void CMainMenuScene::goToGameScene(cocos2d::Ref *sender)
{
	auto scene = CMainScene::createScene();
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.7f, scene));
}