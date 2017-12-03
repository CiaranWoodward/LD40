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

	mTextCounter.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 100.f));
	mTextCounter.setFillColor(sf::Color::White);
}


CorpsePile::~CorpsePile()
{
}

bool CorpsePile::Update(sf::Time dt)
{
	mTextCounter.setString(std::to_string(mCorpseCounter));
	mTextCounter.setOrigin(mTextCounter.getLocalBounds().width / 2, 0);

	return true;
}
