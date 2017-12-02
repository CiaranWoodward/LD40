#pragma once

#include <cstdint>

class TileObject
{
public:
	TileObject(int32_t aBlockFactor, int32_t aKeenFactor) : mBlockFactor(aBlockFactor), mKeenFactor(aKeenFactor) {}
	~TileObject() {}

	virtual bool Damage(int32_t damage);

	int32_t GetBlockFactor() const { return mBlockFactor; }
	int32_t GetKeenFactor() const { return mKeenFactor; }

private:
	int32_t mBlockFactor;
	int32_t mKeenFactor;
};