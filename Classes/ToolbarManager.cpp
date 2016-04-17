#include "ToolbarManager.h"
#include "MainScene.h"

CToolbar * CToolbarManager::createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CMainScene *scene)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.9f, visibleSize.height * 0.5f), Rect(0, 0, 64.0f, 64.0f), "icon_melee");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::knivesOperate, &*player));
	attack->getButton()->m_onClick.connect(boost::bind(&CMainScene::createAttackToolbar, &*scene));
	m_toolbar->appendButton(attack);

	auto frost = m_toolbar->createButton({ visibleSize.width * 0.9f, visibleSize.height * 0.4f }, Rect(0, 0, 64.0f, 64.0f), "icon_frost");
	frost->getButton()->m_onClick.connect(boost::bind(&CPlayer::frostOperate, &*player));
	frost->getButton()->m_onClick.connect(boost::bind(&CMainScene::createFrostToolbar, &*scene));
	m_toolbar->appendButton(frost);

	auto fire = m_toolbar->createButton(Point(visibleSize.width * 0.9f, visibleSize.height * 0.3f), Rect(0, 0, 64.0f, 64.0f), "icon_fire");
	fire->getButton()->m_onClick.connect(boost::bind(&CPlayer::fireOperate, &*player));
	m_toolbar->appendButton(fire);

	auto arcan = m_toolbar->createButton(Point(visibleSize.width * 0.9f, visibleSize.height * 0.2f), Rect(0, 0, 64.0f, 64.0f), "icon_arcan");
	m_toolbar->appendButton(arcan);

	return m_toolbar;
}


CToolbar * CToolbarManager::createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player)
{

	auto m_toolbar = CToolbar::create();

	auto button1 = m_toolbar->createButton(Point(visibleSize.width * 0.8f, visibleSize.height * 0.13f), Rect(0, 0, 64.0f, 64.0f), "frost_1");
	m_toolbar->appendButton(button1);

	auto button2 = m_toolbar->createButton(Point(visibleSize.width * 0.7f, visibleSize.height * 0.13f), Rect(0, 0, 64.0f, 64.0f), "frost_2");
	m_toolbar->appendButton(button2);

	return m_toolbar;
}

CToolbar * CToolbarManager::createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player)
{
	auto m_toolbar = CToolbar::create();

	auto attack = m_toolbar->createButton(Point(visibleSize.width * 0.8f, visibleSize.height * 0.13f), Rect(0, 0, 64.0f, 64.0f), "attack_spell");
	attack->getButton()->m_onClick.connect(boost::bind(&CPlayer::attack, &*player));
	m_toolbar->appendButton(attack);

	return m_toolbar;
}