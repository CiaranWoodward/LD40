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

sf::Vector2<int32_t> MapManager::GetTileDrawOrigin(sf::Vector2<uint32_t> aTileCoord)
{
	return sf::Vector2<int32_t>((aTileCoord.x - aTileCoord.y) * kTileWidth,
	                            (aTileCoord.x + aTileCoord.y) * kTileHeight);
}

sf::Vector2<int32_t> MapManager::GetTileDrawCenter(sf::Vector2<uint32_t> aTileCoord)
{
	sf::Vector2<int32_t> rval = GetTileDrawOrigin(aTileCoord);

	rval.x += (kTileHeight / 2);

	return rval;
}
