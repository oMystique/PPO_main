#pragma once
#include "Toolbar.h"
#include "player.h"

class CMainScene;

class CToolbarManager
{
public:
	static CToolbar *createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CMainScene *scene);
	static CToolbar *createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
	static CToolbar *createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
	static CToolbar *createFireToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
};