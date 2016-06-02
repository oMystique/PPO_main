#include "UILayer.h"
#include "World.h"


CUILayer * CUILayer::create()
{
	CUILayer * uiLayer = new (std::nothrow) CUILayer();
	if (uiLayer && uiLayer->init())
	{
		uiLayer->autorelease();
		return uiLayer;
	}
	CC_SAFE_DELETE(uiLayer);

	return nullptr;
}

CUILayer * CUILayer::create(CWorld * world)
{
	CUILayer * uiLayer = new (std::nothrow) CUILayer();
	uiLayer->setPtrToWorld(world);
	if (uiLayer && uiLayer->init())
	{
		uiLayer->autorelease();
		return uiLayer;
	}
	CC_SAFE_DELETE(uiLayer);

	return nullptr;
}

void CUILayer::setPtrToWorld(CWorld * world)
{
	m_world = world;
}

void CUILayer::update()
{
	m_lifeBar->update(m_world->getPlayerHealthCount(), m_world->getPlayerManaCount());
}

cocos2d::Vec2 CUILayer::getJoystickPosition()const
{
	return m_joystickBase->getJoystick()->getStickPosition();
}

bool CUILayer::init()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_toolbar = CToolbarManager::createBaseToolbar(m_visibleSize, m_world->getPlayer(), this);
	addChild(m_toolbar);

	m_lifeBar = CLifeBar::create(Vec2(m_visibleSize.width * 0.13f, m_visibleSize.height * 1.05f),
		Vec2(m_visibleSize.width * 0.124f, m_visibleSize.height * 1.055f),
		Vec2(m_visibleSize.width * 0.126f, m_visibleSize.height * 1.026f),
		"hp_bar_1.png", "hp.png", "mana.png");
	addChild(m_lifeBar);

	createJoyStick();
	addChild(m_joystickBase);

	scheduleUpdate();

	return true;
}

void CUILayer::createJoyStick()
{
	CCRect joystickBaseDimensions;
	joystickBaseDimensions = CCRectMake(0, 0, 160.0f, 160.0f);

	CCPoint joystickBasePosition;
	joystickBasePosition = ccp(m_visibleSize.width * 0.1f, m_visibleSize.height*0.35f);

	m_joystickBase = SneakyJoystickSkinnedBase::create();
	m_joystickBase->init();
	m_joystickBase->setPosition(joystickBasePosition);
	m_joystickBase->setBackgroundSprite(CCSprite::create("joystick_background.png"));
	m_joystickBase->setThumbSprite(CCSprite::create("joystick_thumb.png"));

	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	m_joystickBase->setJoystick(aJoystick);
	m_joystickBase->setPosition(joystickBasePosition);
}


void CUILayer::createFrostToolbar()
{
	if (m_addToolbar != nullptr)
	{
		removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createFrostToolbar(m_visibleSize, m_world->getPlayer(), this, m_world);
	addChild(m_addToolbar);
}

void CUILayer::createFireToolbar()
{
}

void CUILayer::createArcaneToolbar()
{
}


void CUILayer::createAttackToolbar()
{
	if (m_addToolbar != nullptr)
	{
		removeChild(m_addToolbar);
	}
	m_addToolbar = CToolbarManager::createMeleeToolbar(m_visibleSize, m_world->getPlayer());
	addChild(m_addToolbar);
}