#pragma once

#include "MainScene.h"


class CMainMenuScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(CMainMenuScene);
	static cocos2d::Scene* createScene();
	bool init() override;
private:
	void createHowToGameTable(cocos2d::Ref *sender);
	void createAboutTable(cocos2d::Ref *sender);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void goToGameScene(cocos2d::Ref *sender);
private:
	cocos2d::Sprite * m_additionTable;
};