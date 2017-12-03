#include "GrainPile.h"
#include <string>



GrainPile::GrainPile(GameManager &aGameManager, uint32_t &aGrainCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextCounter("000", mGameManager.GetDrawManager().GetGlobalFont(), 10),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(24, 26), 1, 100),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextCounter, UINT32_MAX),
	mGrainCounter(aGrainCounter)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 41, 106, 53));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - 1); //-1 because takes up extra tiles

	mTextCounter.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 100.f));
	mTextCounter.setFillColor(sf::Color::White);
}


GrainPile::~GrainPile()
{
}

bool GrainPile::Update(sf::Time dt)
{

	mTextCounter.setString(std::to_string(mGrainCounter));
	mTextCounter.setOrigin(mTextCounter.getLocalBounds().width / 2, 0);

	return true;
}