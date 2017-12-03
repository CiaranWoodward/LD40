#include <cstdlib>

#include "CorpsePile.h"

CorpsePile::CorpsePile(GameManager &aGameManager, uint32_t &aCorpseCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextCounter("000", mGameManager.GetDrawManager().GetGlobalFont(), 10),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(26, 24), 1, 100),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextCounter, INT32_MAX),
	mCorpseCounter(aCorpseCounter)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(106, 41, 106, 53));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - 1); //-1 because takes up extra tiles

	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 0)).SetTileObject(&mTileObject);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 1)).SetTileObject(&mTileObject);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(0, 1)).SetTileObject(&mTileObject);

	mTextCounter.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 100.f));
	mTextCounter.setFillColor(sf::Color::White);
}


CorpsePile::~CorpsePile()
{
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 0)).SetTileObject(NULL);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 1)).SetTileObject(NULL);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(0, 1)).SetTileObject(NULL);
}

bool CorpsePile::Update(sf::Time dt)
{
	int32_t drawLevelOffset = MapManager::kTileHeight + 20;

	mTextCounter.setString(std::to_string(mCorpseCounter));
	mTextCounter.setOrigin(mTextCounter.getLocalBounds().width / 2, 0);

	if (mCorpseCounter < 1)
		mSprite.setTextureRect(mTexture1);
	else if (mCorpseCounter < 2)
		mSprite.setTextureRect(mTexture2);
	else if (mCorpseCounter < 3)
		mSprite.setTextureRect(mTexture3);
	else if (mCorpseCounter < 6)
		mSprite.setTextureRect(mTexture4);
	else if (mCorpseCounter < 15)
		mSprite.setTextureRect(mTexture5);
	else
		mSprite.setTextureRect(mTexture6);

	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - drawLevelOffset); //-1 because takes up extra tiles
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);

	return true;
}
