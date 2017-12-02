#include "MapManager.h"



MapManager::MapManager() :
	mTiles()
{
}


MapManager::~MapManager()
{
}

Tile &MapManager::GetTile(sf::Vector2<uint32_t> aTileCoord)
{
	return mTiles[aTileCoord.x][aTileCoord.y];
}

sf::Vector2f MapManager::GetTileDrawOrigin(const sf::Vector2<uint32_t> &aTileCoord)
{
	return sf::Vector2f((aTileCoord.x - aTileCoord.y) * kTileWidth,
	                            (aTileCoord.x + aTileCoord.y) * kTileHeight);
}

sf::Vector2f MapManager::GetTileDrawCenter(const sf::Vector2<uint32_t> &aTileCoord)
{
	sf::Vector2f rval = GetTileDrawOrigin(aTileCoord);

	rval.x += (kTileHeight / 2);

	return rval;
}
