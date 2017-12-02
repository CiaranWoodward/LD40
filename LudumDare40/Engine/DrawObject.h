#pragma once

#include <cstdint>
#include <SFML\Graphics.hpp>

class DrawManager;

class DrawObject
{
public:
	DrawObject(DrawManager &aDrawManager, sf::Sprite &aSprite, int32_t aDrawLevel);
	~DrawObject();

	sf::Sprite &GetSprite() const { return mSprite; }

	int32_t GetDrawLevel() const { return mDrawLevel; }
	void SetDrawLevel(int32_t aDrawLevel);

private:
	DrawManager &mDrawManager;

	sf::Sprite &mSprite;
	int32_t mDrawLevel;
};

