#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "player.h"
#include "SneakyInput\SneakyJoystickSkinnedBase.h"
#include "SneakyInput\SneakyButtonSkinnedBase.h"
#include "ButtonsKit.h"
#include "ToolbarManager.h"

class CMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    bool init() override;
    
	void createAttackToolbar();
	void createFrostToolbar();
	void createFireToolbar();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CMainScene);
private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void createJoystick();


	void update(float dt);
private:
	CPlayer * player;
	ObjectKeeper<SneakyJoystickSkinnedBase> joystickBase;
	Size visibleSize;
	ObjectKeeper<CToolbar> m_toolbar;
	CToolbar *m_addToolbar;
};

#endif // __HELLOWORLD_SCENE_H__
