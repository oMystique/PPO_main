#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PlayerPuppeteer.h"
#include "SneakyInput\SneakyJoystickSkinnedBase.h"
#include "SneakyInput\SneakyButtonSkinnedBase.h"
#include "ButtonsKit.h"
#include "ToolbarManager.h"
#include "Level.h"
#include "EnemyPuppeteer.h"
#include "Lifebar.h"

class CMainScene : public cocos2d::Layer
{
public:
	Layer *uiLayer;

    static cocos2d::Scene* createScene();

    bool init() override;
    
	void createAttackToolbar();
	void createFrostToolbar();
	void createFireToolbar();


	void frostCircle();
    void menuCloseCallback(cocos2d::Ref* pSender);
private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void createJoystick();
	CCPoint tileCoordForPosition(CCPoint position);
	void setPlayerPosition(CCPoint position);
	void update(float dt);
	template <typename T>
	static Rect getGlobalRect(T const &sprite);
private:
	CLifeBar *m_lifeBar;
	CLevel * m_level;
	ObjectKeeper<CPlayerPuppeteer> m_playerPuppeteer;
	ObjectKeeper<CEnemyPuppeteer> m_enemyPuppeteer;
	ObjectKeeper<SneakyJoystickSkinnedBase> joystickBase;
	Size visibleSize;
	ObjectKeeper<CToolbar> m_toolbar;
	CToolbar *m_addToolbar;

	Sprite *cameraTarget;
	Sprite *m_action;
};

#endif // __HELLOWORLD_SCENE_H__
