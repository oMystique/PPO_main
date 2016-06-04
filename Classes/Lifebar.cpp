#include "Lifebar.h"

USING_NS_CC;

CLifeBar * CLifeBar::create(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, Vec2 const &manaPos
	, std::string const &backgroundPath, std::string const &hpPath, std::string const &manaPath)
{
	CLifeBar * lifebar = new (std::nothrow) CLifeBar();
	if (lifebar)
	{
		lifebar->autorelease();
		lifebar->initLifeBar(backgroundPos, hpPos, manaPos, backgroundPath, hpPath, manaPath);
		return lifebar;
	}

	CC_SAFE_DELETE(lifebar);
	return NULL;
}

CLifeBar * CLifeBar::create(cocos2d::Vec2 const & backgroundPos, cocos2d::Vec2 const & hpPos
	, std::string const &backgroundPath, std::string const &hpPath)
{
	CLifeBar * lifebar = new (std::nothrow) CLifeBar();
	if (lifebar)
	{
		lifebar->autorelease();
		lifebar->initLifeBar(backgroundPos, hpPos, backgroundPath, hpPath);
		return lifebar;
	}

	CC_SAFE_DELETE(lifebar);
	return NULL;
}

void CLifeBar::initLifeBar(Vec2 const &backgroundPos, Vec2 const &hpPos, Vec2 const &manaPos
	, std::string const &backgroundPath, std::string const &hpPath, std::string const &manaPath)
{
	initLifeBar(backgroundPos, hpPos, backgroundPath, hpPath);

	m_mana = Sprite::create();
	m_mana->initWithFile(manaPath);
	m_mana->ignoreAnchorPointForPosition(true);
	m_mana->setPosition(manaPos);
	addChild(m_mana);
}

void CLifeBar::initLifeBar(cocos2d::Vec2 const & backgroundPos, cocos2d::Vec2 const & hpPos
	, std::string const &backgroundPath, std::string const &hpPath)
{
	m_background = Sprite::create();
	m_background->initWithFile(backgroundPath);
	m_background->setPosition(backgroundPos);
	addChild(m_background);

	m_health = Sprite::create();
	m_health->initWithFile(hpPath);
	m_health->ignoreAnchorPointForPosition(true);
	m_health->setPosition(hpPos);
	addChild(m_health);
}


void CLifeBar::update(int health, int mana)
{
	update(health);

	mana < 0 ? mana = 0 : false;
	m_mana->setScaleX(float(mana) / 100.f);
}

void CLifeBar::update(int health)
{
	health < 0 ? health = 0 : false;
	m_health->setScaleX(float(health) / 100.f);
}

void CLifeBar::updateHealthBarPosition(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const & pos)
{
	m_background->setPosition(backgroundPos);
	m_health->setPosition(pos);
}
