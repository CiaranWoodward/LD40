#include <cstdlib>

#include "PlainTiles.h"


PlainTiles::PlainTiles(GameManager & aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprites()
{
	for (uint32_t x = 0; x < MapManager::kMaxX; x++)
	{
		for (uint32_t y = 0; y < MapManager::kMaxY; y++)
		{
			sf::Sprite &sprite = mSprites[x][y];
			int randOffset = std::rand() % 10;
			
			sprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
			sprite.setTextureRect(sf::IntRect(54 * randOffset, 0, 54, 27));
			sprite.setPosition(MapManager::GetTileDrawOrigin(sf::Vector2<uint32_t>(x, y)));
			sprite.setOrigin(sprite.getTextureRect().width / 2.f, sprite.getTextureRect().height);

			mDrawObjects[x][y] = new DrawObject(mGameManager.GetDrawManager(), sprite, sprite.getPosition().y - 2);
		}
	}
}

PlainTiles::~PlainTiles()
{
	for (uint32_t x = 0; x < MapManager::kMaxX; x++)
	{
		for (uint32_t y = 0; y < MapManager::kMaxY; y++)
		{
			delete mDrawObjects[x][y];
		}
	}
}

bool PlainTiles::Update(sf::Time dt)
{
	return true;
}
