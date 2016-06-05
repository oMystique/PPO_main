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
	static CWorld * create();
	void update();
	void setPtrToUiLayer(CUILayer * uiLayer);
	cocos2d::Vec2 getPlayerPos()const;
	int getPlayerHealthCount()const;
	int getPlayerManaCount()const;
	void createFrostCircle();
	void createFireCircle();
	CPlayer * getPlayer();
	bool init()override;
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
	CLevel * m_level;
	cocos2d::Sprite *m_action;
	cocos2d::Sprite * m_cameraTarget;
};