#include "CorpsePile.h"



CorpsePile::CorpsePile(GameManager &aGameManager, uint32_t &aCorpseCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(26, 24), 1, 100),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(106, 41, 106, 53));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - 1); //-1 because takes up extra tiles
}


CorpsePile::~CorpsePile()
{
}

bool CorpsePile::Update(sf::Time dt)
{
	return true;
}