#pragma once
#include "cocos2d.h"
#include "SneakyInput\SneakyJoystickSkinnedBase.h"
#include "SneakyInput\SneakyButtonSkinnedBase.h"
#include <string>

class CToolbar: public cocos2d::Node
{
public:
	static CToolbar * create();
	SneakyButtonSkinnedBase * createButton (cocos2d::Point const &pos, cocos2d::Rect const &bounds, std::string const &buttonName);
	void appendButton(SneakyButtonSkinnedBase *button);
};