#pragma once

#include <cstdint>
#include <SFML\Graphics.hpp>

#include "DrawManager.h"

class DrawObject
{
public:
	DrawObject(DrawManager &aDrawManager, sf::Sprite &aSprite, int32_t aDrawLevel) :
		mDrawManager(aDrawManager),
		mSprite(aSprite),
		mDrawLevel(aDrawLevel)
	{
		mDrawManager.Add(*this);
		mDrawManager.Refresh();
	}

	~DrawObject()
	{
		mDrawManager.Remove(*this);
	}

	sf::Sprite &GetSprite() const { return mSprite; }

	int32_t GetDrawLevel() const { return mDrawLevel; }
	int32_t SetDrawLevel(int32_t aDrawLevel) { mDrawLevel = aDrawLevel; mDrawManager.Refresh(); }

private:
	DrawManager &mDrawManager;

	sf::Sprite &mSprite;
	int32_t mDrawLevel;
};

