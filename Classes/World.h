#pragma once
#include "PlayerPuppeteer.h"
#include "EnemyPuppeteer.h"
#include "Level.h"
#include <vector>
#include <Bonus.h>


class CUILayer;
class CWorld final
	: public cocos2d::Layer
{
public:
	static CWorld * create(int levelNumber = 1);
	void update();
	void setPtrToUiLayer(CUILayer * uiLayer);
	cocos2d::Vec2 getPlayerPos()const;
	int getPlayerHealthCount()const;
	int getPlayerManaCount()const;
	void createFrostCircle();
	void createFireCircle();
	CPlayer * getPlayer()const;
	bool isFinished()const;
	bool init(int levelNumber = 1);
private:
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void fightEnemyPuppeteerEvents(CEnemyPuppeteer * enemyPuppeteer);
	void createBonuses();
	void createEnemyPuppeteers();
	void updateBonuses();
	void updateEnemyPuppeteers();
private:
	std::vector<cocos2d::RefPtr<CEnemyPuppeteer>> m_enemyPuppeteers;
	std::vector<cocos2d::RefPtr<CBonus>> m_bonuses;
	CUILayer * m_uiLayer;
	ObjectKeeper<CPlayerPuppeteer> m_playerPuppeteer;
	cocos2d::RefPtr<cocos2d::Sprite> m_flag;
	cocos2d::RefPtr<cocos2d::Sprite> m_finish;
	CLevel * m_level;
	cocos2d::Sprite *m_action;
	cocos2d::Sprite * m_cameraTarget;
	bool m_isFinished = false;
};