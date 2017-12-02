#pragma once

#include <cstdint>

#include <SFML\System.hpp>

class MapManager;

class TileObject
{
public:
	TileObject(MapManager &aMapManager, sf::Vector2<int32_t> aTileCoord, int32_t aBlockFactor, int32_t aKeenFactor);

	~TileObject();

	bool Damage(int32_t damage);

	int32_t GetBlockFactor() const { return mBlockFactor; }
	int32_t GetKeenFactor() const { return mKeenFactor; }

	const sf::Vector2<uint32_t> GetTileCoords() const { return mTileCoord; }

private:
	MapManager &mMapManager;
	const sf::Vector2<uint32_t> mTileCoord;

	int32_t mBlockFactor;
	int32_t mKeenFactor;
};