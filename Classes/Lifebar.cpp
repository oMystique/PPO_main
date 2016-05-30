#include "Lifebar.h"

USING_NS_CC;

CLifeBar * CLifeBar::create(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, Vec2 const &manaPos)
{
	CLifeBar * lifebar = new (std::nothrow) CLifeBar();
	if (lifebar)
	{
		lifebar->autorelease();
		lifebar->initLifeBar(backgroundPos, hpPos, manaPos);
		return lifebar;
	}

	CC_SAFE_DELETE(lifebar);
	return NULL;
}

void CLifeBar::initLifeBar(Vec2 const &backgroundPos, Vec2 const &hpPos, Vec2 const &manaPos)
{
	m_background = Sprite::create();
	m_background->initWithFile("hp_bar_1.png");
	m_background->setPosition(backgroundPos);
	addChild(m_background);

	m_health = Sprite::create();
	m_health->initWithFile("hp.png");
	m_health->setPosition(hpPos);
	addChild(m_health);

	m_mana = Sprite::create();
	m_mana->initWithFile("mana.png");
	m_mana->setPosition(manaPos);
	addChild(m_mana);
}


void CLifeBar::update(int health, int mana)
{
}