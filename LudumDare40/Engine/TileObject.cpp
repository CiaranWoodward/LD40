#include "MapManager.h"
#include "TileObject.h"

TileObject::TileObject(MapManager &aMapManager, sf::Vector2<uint32_t> aTileCoord, int32_t aBlockFactor, int32_t aKeenFactor) :
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

bool TileObject::Damage(int32_t damage)
{
	mBlockFactor -= damage;
	if (mBlockFactor < 0)
	{
		mKeenFactor += mBlockFactor;
		mBlockFactor = 0;
	}
	if (mKeenFactor < 0)
	{
		mKeenFactor = 0;
	}

	return (mKeenFactor == 0);
}
