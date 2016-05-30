#include "Level.h"

const double SCALE_FACTOR = 2;

void CLevel::loadMap(const char* mapname) {

	map = TMXTiledMap::create(mapname);
	{
		m_meta = map->layerNamed("floor");
		Size layerSize = m_meta->getLayerSize();
		for (int y = 0; y < layerSize.height; y++)
		{
			for (int x = 0; x < layerSize.width; x++)
			{
				auto tileSprite = m_meta->getTileAt(Point(x, y));
				if (tileSprite)
				{
					tileSprite->setPhysicsBody(PhysicsBody::createBox(tileSprite->getContentSize(), PhysicsMaterial(1000, 0, 0)));
					tileSprite->getPhysicsBody()->setDynamic(false);
					tileSprite->setVisible(false);
				}

			}
		}
	}
	{
		m_meta = map->layerNamed("walls");
		Size layerSize = m_meta->getLayerSize();
		for (int y = 0; y < layerSize.height; y++)
		{
			for (int x = 0; x < layerSize.width; x++)
			{
				auto tileSprite = m_meta->getTileAt(Point(x, y));
				if (tileSprite)
				{
					tileSprite->setPhysicsBody(PhysicsBody::createBox(tileSprite->getContentSize(), PhysicsMaterial(1000, 0, 0)));
					tileSprite->getPhysicsBody()->setDynamic(false);
					tileSprite->getPhysicsBody()->setContactTestBitmask(true);
					tileSprite->getPhysicsBody()->setCollisionBitmask(2);
					tileSprite->setVisible(false);
				}

			}
		}
	}
	map->retain();
}

TMXTiledMap * CLevel::getMap() 
{
	return map;
}

std::vector<Sprite*> CLevel::getMetas()
{
	return m_metas;
}

CLevel::CLevel(void)
{
}


Point CLevel::tileCoordinateToPosition(Size s, Point point) {

	float x = floor(s.width / 2 * SCALE_FACTOR + point.x * map->getTileSize().width * SCALE_FACTOR);
	float y = floor(s.height / 2 * SCALE_FACTOR + point.y * map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);

}

Point CLevel::positionToTileCoordinate(Size s, Point point) {

	float x = floor((point.x - s.width / 2 ) / (map->getTileSize().width ));
	float y = floor((point.y - s.height / 2 ) / (map->getTileSize().height ));

	return Point(x, y);
}

std::vector<Rect> CLevel::getCollisionTiles(Point point, int fromX, int fromY) {

	std::vector<Rect> list;

	TMXLayer *walls = map->getLayer("Meta");

	for (int a = 0; a < 2; a++) {

		for (int b = 0; b < 2; b++) {

			if (!(a == 0 && b == 0)) {

				Sprite *tile = walls->getTileAt(Point((int)point.x + a, (map->getMapSize().height - 1) - ((int)point.y + b)));

				if (tile != NULL) {

					Point tmp = walls->positionAt(Point((int)point.x + a, (map->getMapSize().height - 1) - ((int)point.y + b)));

					list.push_back(Rect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR));
				}
			}
		}
	}

	return list;

}
CLevel::~CLevel(void)
{
	map->release();
}
