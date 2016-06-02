#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "UILayer.h"
#include "World.h"

class CMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
    void menuCloseCallback(cocos2d::Ref* pSender);
private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void update(float dt);
private:
	CWorld * m_world;
	CUILayer * m_uiLayer;
};

#endif // __HELLOWORLD_SCENE_H__
