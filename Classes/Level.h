#pragma once

#include "cocos2d.h"
#include <vector>
#include "ObjectKeeper.h"

class CLevel : public cocos2d::Object
{
public:
	void loadMap(const char* name);
	cocos2d::TMXTiledMap * getMap();
	std::vector<cocos2d::Sprite*> getMetas();

	cocos2d::Point tileCoordinateToPosition(cocos2d::Size s, cocos2d::Point point);
	cocos2d::Point positionToTileCoordinate(cocos2d::Size s, cocos2d::Point point);
	std::vector<cocos2d::Rect> getCollisionTiles(cocos2d::Point point, int fromX, int fromY);

	CLevel(void);
	virtual ~CLevel(void);
private:
	cocos2d::TMXTiledMap *map;
	ObjectKeeper<cocos2d::CCTMXLayer> m_meta;
	std::vector<cocos2d::Sprite*> m_metas;
};
