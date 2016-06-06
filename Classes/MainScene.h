#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "UILayer.h"
#include "World.h"

class CMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int levelNumber = 1);

    bool init(int levelNumber = 1);
    
    void menuCloseCallback(cocos2d::Ref* pSender);
private:
	void createGameOverPlash();
	void update(float dt);
	void restartLevel(cocos2d::Ref *sender);
private:
	CWorld * m_world;
	CUILayer * m_gameUI;
	MenuItemImage * m_restartItem;
	int m_levelNumber;
};

#endif // __HELLOWORLD_SCENE_H__
