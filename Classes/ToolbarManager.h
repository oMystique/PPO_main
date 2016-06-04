#pragma once
#include "Toolbar.h"
#include "player.h"

class CUILayer;
class CWorld;

enum class ToolbarType
{
	base, 
	melee,
	frost,
	fire,
	arcane
};

class CToolbarManager
{
public:
	static CToolbar *createBaseToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CUILayer *gameUI);
	static CToolbar *createMeleeToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
	static CToolbar *createFrostToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CWorld * world);
	static CToolbar *createFireToolbar(cocos2d::Size const &visibleSize, CPlayer *player, CWorld * world);
	static CToolbar *createArcaneToolbar(cocos2d::Size const &visibleSize, CPlayer *player);
};