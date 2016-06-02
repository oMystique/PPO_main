#pragma once
#include "Toolbar.h"
#include "player.h"

class CUILayer;
class CWorld;

class CToolbarManager
{
public:
	static CToolbar *createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *scene);
	static CToolbar *createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
	static CToolbar *createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *scene, CWorld * world);
	static CToolbar *createFireToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
	static CToolbar *createArcaneToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
};