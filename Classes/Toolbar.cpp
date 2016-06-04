#include "Toolbar.h"
#include "ObjectKeeper.h"

USING_NS_CC;

CToolbar * CToolbar::create()
{
	CToolbar *toolbar = new (std::nothrow) CToolbar();
	return toolbar;
}

SneakyButtonSkinnedBase* CToolbar::createButton(cocos2d::Point const & pos
	, cocos2d::Rect const & bounds
	, std::string const & buttonName)
{
	ObjectKeeper<SneakyButtonSkinnedBase> buttonBase = SneakyButtonSkinnedBase::create();
	buttonBase->setPosition(pos);
	buttonBase->setScale(1.4f);
	buttonBase->setDefaultSprite(Sprite::create(buttonName + ".png"));
	buttonBase->setActivatedSprite(Sprite::create(buttonName + ".png"));
	buttonBase->setDisabledSprite(Sprite::create(buttonName + ".png"));
	buttonBase->setPressSprite(Sprite::create(buttonName + "_pressed.png"));

	ObjectKeeper<SneakyButton> sButton = new SneakyButton();
	sButton->initWithRect(bounds);

	sButton->setIsHoldable(true);
	sButton->setIsToggleable(true);

	buttonBase->setButton(sButton);
	buttonBase->setPosition(pos);

	auto gButton = buttonBase->getButton();
	gButton->retain();

	return buttonBase;
}

void CToolbar::appendButton(SneakyButtonSkinnedBase *button)
{
	addChild(button);
}
