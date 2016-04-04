#pragma once
#include "cocos2d.h"

class CEntities : public cocos2d::Sprite
{
public:
	virtual ~CEntities() = default;
	virtual void update() = 0;
};