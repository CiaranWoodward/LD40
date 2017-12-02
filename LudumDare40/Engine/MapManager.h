#pragma once

#include <SFML\System.hpp>
#include "TileObject.h"

class Tile
{
public:
	Tile() : mTileObject(NULL) {};

	//Returns true if nothing left to attack (destroyed)
	bool Damage(uint32_t damage) { return (mTileObject == NULL) ? true : mTileObject->Damage(damage); }
	
	int32_t GetBlockFactor() const { return (mTileObject == NULL) ? 0 : mTileObject->GetBlockFactor; }
	int32_t GetKeenFactor() const { return (mTileObject == NULL) ? 0 : mTileObject->GetKeenFactor; };

	TileObject *GetTileObject() { return mTileObject; }
	void SetTileObject(TileObject *aTileObject) { mTileObject = aTileObject; }

private:
	TileObject *mTileObject;
};

class MapManager
{
public:
	MapManager();
	~MapManager();

	static const size_t kMaxX = 50;
	static const size_t kMaxY = 50;

	Tile GetTile(sf::Vector2<uint32_t> aTileCoord);
	sf::Vector2<int32_t> GetTileDrawOrigin(sf::Vector2<uint32_t> aTileCoord);
	sf::Vector2<int32_t> GetTileDrawCenter(sf::Vector2<uint32_t> aTileCoord);

private:
	Tile mTiles[kMaxX][kMaxY];
};

