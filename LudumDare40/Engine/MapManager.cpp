#include "MapManager.h"

#include <assert.h>


MapManager::MapManager() :
	mTiles()
{
}


MapManager::~MapManager()
{
}

bool MapManager::Update()
{
	//First reset the map smells
	for (uint32_t x = 0; x < kMaxX; x++)
	{
		for (uint32_t y = 0; y < kMaxY; y++)
		{
			mTiles[x][y].mSmellFactor = 0;
			mTiles[x][y].mLastTouched = 0;
		}
	}

	//Now spread the smells using the potentially garbage algorithm i just made up
	for (uint32_t x = 0; x < kMaxX; x++)
	{
		for (uint32_t y = 0; y < kMaxY; y++)
		{
			if (mTiles[x][y].GetTileObject() != NULL && mTiles[x][y].GetTileObject()->GetKeenFactor() > 4)
			{
				CastSmells(x, y, mTiles[x][y].GetTileObject()->GetKeenFactor());
			}
		}
	}

	return true;
}

void MapManager::CastSmells(uint32_t x, uint32_t y, int32_t aKeenFactor)
{
	if (aKeenFactor < 0) return;
	if (aKeenFactor > 31) aKeenFactor = 31;

	mTiles[x][y].IncrementSmellFactor(1 << aKeenFactor);
	
	//Cast in y+ direction
	for (uint32_t xRan = 1, ty=y; ty < kMaxY-1; xRan += 2, ty++)
	{
		uint32_t minX = x - (xRan / 2);
		uint32_t maxX = x + (xRan / 2);
		if (minX == 0 || minX > kMaxX) minX = 1;
		if (maxX >= kMaxX-1) maxX = kMaxX-2;

		bool StillGoing = 0;
		for (uint32_t tx = minX; tx <= maxX; tx++) //Wipe the 'lasttouched'
		{
			assert(tx >= 0 && tx < kMaxX);
			assert((ty + 1) >= 0 && (ty + 1) < kMaxY);
			assert((tx + 1) >= 0 && (tx + 1) < kMaxY);
			assert((tx - 1) >= 0 && (tx - 1) < kMaxY);
			mTiles[tx][ty + 1].mLastTouched = 0;
		}
		for (uint32_t tx = minX; tx <= maxX; tx++) //3 tile projection for each tile in range
		{
			uint32_t curSmell = mTiles[tx][ty].mLastTouched;
			StillGoing = StillGoing || (curSmell > 2);
			if (tx+1 > kMaxX || tx - 1 )
			mTiles[tx + 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx - 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx][ty + 1].IncrementSmellFactor(curSmell / 2);
		}
		if (!StillGoing) break;
	}

	//Cast in y- direction
	for (uint32_t xRan = 1, ty = y; ty > 1; xRan += 2, ty--)
	{
		uint32_t minX = x - (xRan / 2);
		uint32_t maxX = x + (xRan / 2);
		if (minX == 0 || minX > kMaxX) minX = 1;
		if (maxX >= kMaxX - 1) maxX = kMaxX - 2;

		bool StillGoing = 0;
		for (uint32_t tx = minX; tx <= maxX; tx++) //Wipe the 'lasttouched'
		{
			mTiles[tx][ty - 1].mLastTouched = 0;
		}
		for (uint32_t tx = minX; tx <= maxX; tx++) //3 tile projection for each tile in range
		{
			uint32_t curSmell = mTiles[tx][ty].mLastTouched;
			StillGoing = StillGoing || (curSmell > 2);

			mTiles[tx + 1][ty - 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx - 1][ty - 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx][ty - 1].IncrementSmellFactor(curSmell / 2);
		}
		if (!StillGoing) break;
	}

	//Cast in x+ direction
	for (uint32_t yRan = 1, tx = x; tx < kMaxX - 1; yRan += 2, tx++)
	{
		uint32_t minY = y - (yRan / 2);
		uint32_t maxY = y + (yRan / 2);
		if (minY == 0 || minY > kMaxY) minY = 1;
		if (maxY >= kMaxY - 1) maxY = kMaxY - 2;

		bool StillGoing = 0;
		for (uint32_t ty = minY; ty <= maxY; ty++) //Wipe the 'lasttouched'
		{
			mTiles[tx + 1][ty].mLastTouched = 0;
		}
		for (uint32_t ty = minY; ty <= maxY; ty++) //3 tile projection for each tile in range
		{
			uint32_t curSmell = mTiles[ty][tx].mLastTouched;
			StillGoing = StillGoing || (curSmell > 2);

			mTiles[tx + 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx + 1][ty - 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx + 1][ty].IncrementSmellFactor(curSmell / 2);
		}
		if (!StillGoing) break;
	}

	//Cast in x- direction
	for (uint32_t yRan = 1, tx = x; tx > 1; yRan += 2, tx--)
	{
		uint32_t minY = y - (yRan / 2);
		uint32_t maxY = y + (yRan / 2);
		if (minY == 0 || minY > kMaxY) minY = 1;
		if (maxY >= kMaxY - 1) maxY = kMaxY - 2;

		bool StillGoing = 0;
		for (uint32_t ty = minY; ty <= maxY; ty++) //Wipe the 'lasttouched'
		{
			mTiles[tx - 1][ty].mLastTouched = 0;
		}
		for (uint32_t ty = minY; ty <= maxY; ty++) //3 tile projection for each tile in range
		{
			uint32_t curSmell = mTiles[ty][tx].mLastTouched;
			StillGoing = StillGoing || (curSmell > 2);

			mTiles[tx - 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx - 1][ty - 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx - 1][ty].IncrementSmellFactor(curSmell / 2);
		}
		if (!StillGoing) break;
	}
	
}

Tile &MapManager::GetTile(sf::Vector2<uint32_t> aTileCoord)
{
	return mTiles[aTileCoord.x][aTileCoord.y];
}

sf::Vector2f MapManager::GetTileDrawOrigin(const sf::Vector2<uint32_t> &aTileCoord)
{
	return sf::Vector2f(((int32_t) aTileCoord.x - (int32_t) aTileCoord.y) * kTileWidth,
	                            (aTileCoord.x + aTileCoord.y) * kTileHeight);
}

sf::Vector2f MapManager::GetTileDrawCenter(const sf::Vector2<uint32_t> &aTileCoord)
{
	sf::Vector2f rval = GetTileDrawOrigin(aTileCoord);

	rval.x += (kTileHeight / 2);

	return rval;
}
