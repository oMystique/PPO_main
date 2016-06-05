#include "Level.h"

USING_NS_CC;

const double SCALE_FACTOR = 2;

void CLevel::loadMap(const char* mapname) {

	map = TMXTiledMap::create(mapname);
	{
		auto m_meta = map->layerNamed("floor");
		Size layerSize = m_meta->getLayerSize();
		for (int y = 0; y < layerSize.height; y++)
		{
			for (int x = 0; x < layerSize.width; x++)
			{
				auto tileSprite = m_meta->getTileAt(Point(x, y));
				if (tileSprite)
				{
					tileSprite->setPhysicsBody(PhysicsBody::createBox(tileSprite->getContentSize(), PhysicsMaterial(1000.f, 0, 0)));
					tileSprite->getPhysicsBody()->setDynamic(false);
					tileSprite->setVisible(false);
				}

			}
		}
	}
	{
		auto m_meta = map->layerNamed("walls");
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

cocos2d::Vec2 CLevel::getPlayerPos(std::string const & playerName)
{
	auto objectGroup = getMap()->objectGroupNamed("Objects");
	auto spawnPoint = objectGroup->objectNamed(playerName);
	auto playerPos = Vec2(spawnPoint.at("x").asFloat(), spawnPoint.at("y").asFloat());
	return playerPos;
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
