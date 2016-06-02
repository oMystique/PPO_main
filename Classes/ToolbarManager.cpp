#include "ToolbarManager.h"
#include "UILayer.h"
#include "World.h"

CToolbar * CToolbarManager::createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *scene)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.75f), Rect(0, 0, 64.0f, 64.0f), "icon_melee");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::knivesOperate, &*player));
	attack->getButton()->m_onClick.connect(boost::bind(&CUILayer::createAttackToolbar, &*scene));
	m_toolbar->appendButton(attack);

	auto frost = m_toolbar->createButton({ visibleSize.width * 0.94f, visibleSize.height * 0.62f }, Rect(0, 0, 64.0f, 64.0f), "icon_frost");
	frost->getButton()->m_onClick.connect(boost::bind(&CPlayer::frostOperate, &*player));
	frost->getButton()->m_onClick.connect(boost::bind(&CUILayer::createFrostToolbar, &*scene));
	m_toolbar->appendButton(frost);

	auto fire = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.49f), Rect(0, 0, 64.0f, 64.0f), "icon_fire");
	fire->getButton()->m_onClick.connect(boost::bind(&CPlayer::fireOperate, &*player));
	m_toolbar->appendButton(fire);

	auto arcan = m_toolbar->createButton(Point(visibleSize.width * 0.94f, visibleSize.height * 0.36f), Rect(0, 0, 64.0f, 64.0f), "icon_arcan");
	arcan->getButton()->m_onClick.connect(boost::bind(&CPlayer::arcaneOperate, &*player));
	m_toolbar->appendButton(arcan);

	return m_toolbar;
}


CToolbar * CToolbarManager::createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *scene, CWorld * world)
{

	auto m_toolbar = CToolbar::create();

	auto button1 = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.23f), Rect(0, 0, 64.0f, 64.0f), "frost_1");
	button1->getButton()->m_onClick.connect(boost::bind(&CWorld::createFrostCircle, &*world));
	m_toolbar->appendButton(button1);

	auto button2 = m_toolbar->createButton(Point(visibleSize.width * 0.75f, visibleSize.height * 0.23f), Rect(0, 0, 64.0f, 64.0f), "frost_2");
	m_toolbar->appendButton(button2);

	return m_toolbar;
}

CToolbar * CToolbarManager::createFireToolbar(cocos2d::Size const & visibleSize, CPlayer * player)
{
	return nullptr;
}

CToolbar * CToolbarManager::createArcaneToolbar(cocos2d::Size const & visibleSize, CPlayer * player)
{
	return nullptr;
}

CToolbar * CToolbarManager::createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.83f, visibleSize.height * 0.23f), Rect(0, 0, 64.0f, 64.0f), "attack_spell");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::attack, &*player));
	m_toolbar->appendButton(attack);

	return m_toolbar;
}