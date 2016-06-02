#pragma once
#include <cocos2d.h>
#include <string>

class CLifeBar
	: public cocos2d::Layer
{
public:
	static CLifeBar * create(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, cocos2d::Vec2 const &manaPos
		, std::string const &backgroundPath, std::string const &hpPath, std::string const &manaPath);
	static CLifeBar * create(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos
		, std::string const &backgroundPath, std::string const &hpPath);

	void update(int health, int mana);
	void update(int health);
	void updateHealthBarPosition(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos);
	~CLifeBar() = default;
private:
	void initLifeBar(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos, cocos2d::Vec2 const &manaPos
		, std::string const &backgroundPath, std::string const &hpPath, std::string const &manaPath);
	void initLifeBar(cocos2d::Vec2 const &backgroundPos, cocos2d::Vec2 const &hpPos
		, std::string const &backgroundPath, std::string const &hpPath);
private:
	cocos2d::Sprite *m_background = nullptr;
	cocos2d::Sprite *m_health = nullptr;
	cocos2d::Sprite *m_mana = nullptr;
};