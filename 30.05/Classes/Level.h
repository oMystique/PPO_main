#pragma once

#include "cocos2d.h"
using namespace cocos2d;
#include <vector>
#include "ObjectKeeper.h"

class CLevel : public Object
{
public:
	void loadMap(const char* name);
	TMXTiledMap * getMap();
	std::vector<Sprite*> getMetas();

	Point tileCoordinateToPosition(Size s, Point point);
	Point positionToTileCoordinate(Size s, Point point);
	std::vector<Rect> getCollisionTiles(Point point, int fromX, int fromY);

	CLevel(void);
	virtual ~CLevel(void);
private:
	TMXTiledMap *map;
	ObjectKeeper<CCTMXLayer> m_meta;
	std::vector<Sprite*> m_metas;
};
