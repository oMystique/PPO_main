#include "ToolbarManager.h"
#include "UILayer.h"
#include "World.h"

CToolbar * CToolbarManager::createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *gameUI)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.9f), Rect(0, 0, 64.0f, 64.0f), "icon_melee");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::knivesOperate, player));
	attack->getButton()->m_onClick.connect(boost::bind(&CUILayer::addToolbar, gameUI, ToolbarType::melee));
	m_toolbar->appendButton(attack);

	auto frost = m_toolbar->createButton({ visibleSize.width * 0.94f, visibleSize.height * 0.72f }, Rect(0, 0, 64.0f, 64.0f), "icon_frost");
	frost->getButton()->m_onClick.connect(boost::bind(&CPlayer::frostOperate, player));
	frost->getButton()->m_onClick.connect(boost::bind(&CUILayer::addToolbar, gameUI, ToolbarType::frost));
	m_toolbar->appendButton(frost);

	auto fire = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.54f), Rect(0, 0, 64.0f, 64.0f), "icon_fire");
	fire->getButton()->m_onClick.connect(boost::bind(&CPlayer::fireOperate, player));
	fire->getButton()->m_onClick.connect(boost::bind(&CUILayer::addToolbar, gameUI, ToolbarType::fire));
	m_toolbar->appendButton(fire);

	auto arcan = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.36f), Rect(0, 0, 64.0f, 64.0f), "icon_arcan");
	arcan->getButton()->m_onClick.connect(boost::bind(&CPlayer::arcaneOperate, player));
	arcan->getButton()->m_onClick.connect(boost::bind(&CUILayer::addToolbar, gameUI, ToolbarType::arcane));
	m_toolbar->appendButton(arcan);

	return m_toolbar;
}


CToolbar * CToolbarManager::createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CWorld * world)
{
	auto m_toolbar = CToolbar::create();

	auto button1 = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "frost_1");
	button1->getButton()->m_onClick.connect(boost::bind(&CWorld::createFrostCircle, &*world));
	m_toolbar->appendButton(button1);

	auto button2 = m_toolbar->createButton(Point(visibleSize.width * 0.73f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "frost_2");
	button2->getButton()->m_onClick.connect(boost::bind(&CPlayer::castFrostBalt, player));
	m_toolbar->appendButton(button2);

	return m_toolbar;
}

CToolbar * CToolbarManager::createFireToolbar(cocos2d::Size const & visibleSize, CPlayer * player, CWorld * world)
{
	auto m_toolbar = CToolbar::create();

	auto button1 = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "fire_circle");
	button1->getButton()->m_onClick.connect(boost::bind(&CWorld::createFireCircle, world));
	m_toolbar->appendButton(button1);

	auto button2 = m_toolbar->createButton(Point(visibleSize.width * 0.73f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "fire_ball");
	button2->getButton()->m_onClick.connect(boost::bind(&CPlayer::castFireBalt, player));
	m_toolbar->appendButton(button2);

	return m_toolbar;
}

CToolbar * CToolbarManager::createArcaneToolbar(cocos2d::Size const & visibleSize, CPlayer * player)
{
	auto m_toolbar = CToolbar::create();

	auto arcane = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "arcane_blast");
	arcane->getButton()->m_onClick.connect(boost::bind(&CPlayer::castArcanBlast, player));
	m_toolbar->appendButton(arcane);

	return m_toolbar;
}

CToolbar * CToolbarManager::createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.32f), Rect(0, 0, 64.0f, 64.0f), "attack_spell");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::attack, player));
	m_toolbar->appendButton(attack);

	return m_toolbar;
}