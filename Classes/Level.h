#pragma once

#include "cocos2d.h"
#include <vector>
#include "ObjectKeeper.h"
#include "Bonus.h"

class CLevel : public cocos2d::Object
{
public:
	void loadMap(const char* name);
	cocos2d::TMXTiledMap * getMap();

	template <typename T>
	std::vector<cocos2d::RefPtr<T>> getObjects(std::string const &name);

	cocos2d::Vec2 getPlayerPos(std::string const &playerName);
	
	cocos2d::Point tileCoordinateToPosition(cocos2d::Size s, cocos2d::Point point);
	cocos2d::Point positionToTileCoordinate(cocos2d::Size s, cocos2d::Point point);
private:
	cocos2d::TMXTiledMap *map;
};


template<typename T>
std::vector<cocos2d::RefPtr<T>> CLevel::getObjects(std::string const & name)
{
	std::vector<cocos2d::RefPtr<T>> objects;
	for (auto &it : getMap()->getObjectGroup(name)->getObjects())
	{
		auto value = it.asValueMap();
		auto pos = cocos2d::Vec2(value["x"].asFloat(), value["y"].asFloat());
		auto object = T::create(pos);
		objects.push_back(object);
	}
	return objects;
}
