#include "MapManager.h"
#include "TileObject.h"

TileObject::TileObject(MapManager &aMapManager, sf::Vector2<int32_t> aTileCoord, int32_t aBlockFactor, int32_t aKeenFactor) :
	mMapManager(aMapManager),
	mTileCoord(aTileCoord),
	mBlockFactor(aBlockFactor),
	mKeenFactor(aKeenFactor)
{
	mMapManager.GetTile(mTileCoord).SetTileObject(this);
}

TileObject::~TileObject()
{
	mMapManager.GetTile(mTileCoord).SetTileObject(NULL);
}