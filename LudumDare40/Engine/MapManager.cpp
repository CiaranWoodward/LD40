#include "MapManager.h"



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
		if (minX > kMaxX) minX = 1;
		if (maxX >= kMaxX-1) maxX = kMaxX-2;

		bool StillGoing = 0;
		for (uint32_t tx = minX; tx <= maxX; tx++) //Wipe the 'lasttouched'
		{
			mTiles[tx][ty + 1].mLastTouched = 0;
		}
		for (uint32_t tx = minX; tx <= maxX; tx++) //3 tile projection for each tile in range
		{
			uint32_t curSmell = mTiles[tx][ty].mLastTouched;
			StillGoing = StillGoing || (curSmell > 2);

			mTiles[tx + 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx - 1][ty + 1].IncrementSmellFactor(curSmell / 4);
			mTiles[tx][ty + 1].IncrementSmellFactor(curSmell / 2);
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
