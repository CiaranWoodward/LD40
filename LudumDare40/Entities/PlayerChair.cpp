#include "PlayerChair.h"



PlayerChair::PlayerChair(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<int32_t>(25, 25), 100, 1),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(216, 28, 54, 80));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
}


PlayerChair::~PlayerChair()
{
}

bool PlayerChair::Update(sf::Time dt)
{
	return true;
}
