#pragma once
#include "SneakyInput\SneakyJoystickSkinnedBase.h"
#include "SneakyInput\SneakyButtonSkinnedBase.h"
#include "ButtonsKit.h"
#include "ToolbarManager.h"
#include "Lifebar.h"

class CWorld;
class CUILayer final
	: public cocos2d::Layer
{
public:
	static CUILayer * create();
	static CUILayer * create(CWorld * world);
	void setPtrToWorld(CWorld * world);
	void update();

	void createAttackToolbar();
	void createFrostToolbar();
	void createFireToolbar();
	void createArcaneToolbar();

	cocos2d::Vec2 getJoystickPosition()const;
private:
	void createJoyStick();
	bool init()override;
private:
	CWorld * m_world;
	CLifeBar *m_lifeBar;
	ObjectKeeper<SneakyJoystickSkinnedBase> m_joystickBase;
	ObjectKeeper<CToolbar> m_toolbar;
	CToolbar *m_addToolbar;
	cocos2d::Size m_visibleSize;
};