#pragma once

#include "cocos2d.h"
#include <vector>
#include "ObjectKeeper.h"

class CLevel : public cocos2d::Object
{
public:
	void loadMap(const char* name);
	cocos2d::TMXTiledMap * getMap();

	template <typename T>
	std::vector<ObjectKeeper<T>> getObjects(std::string const &name);
	cocos2d::Vec2 getPlayerPos(std::string const &playerName);
	
	cocos2d::Point tileCoordinateToPosition(cocos2d::Size s, cocos2d::Point point);
	cocos2d::Point positionToTileCoordinate(cocos2d::Size s, cocos2d::Point point);
private:
	cocos2d::TMXTiledMap *map;
};


template<typename T>
std::vector<ObjectKeeper<T>> CLevel::getObjects(std::string const & name)
{
	std::vector<ObjectKeeper<T>> objects;
	for (auto &it : getMap()->getObjectGroup(name)->getObjects())
	{
		auto value = it.asValueMap();
		auto pos = cocos2d::Vec2(value["x"].asFloat(), value["y"].asFloat());
		auto object = T::create(pos);
		objects.push_back(object);
	}
	return objects;
}