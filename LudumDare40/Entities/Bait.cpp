#include "Bait.h"

Bait::Bait(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTileObject(mGameManager.GetMapManager(), aTileCoord, 1, 30),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTexture1);
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
}


Bait::~Bait()
{
}

bool Bait::Update(sf::Time dt)
{
	int32_t health = mTileObject.GetKeenFactor();

	//Set tile brightness
	uint8_t oPac = static_cast<uint8_t>(std::log2(mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords()).mSmellFactor) * 8.0);
	mSprite.setColor(sf::Color(oPac, oPac, oPac));

	if (health == 0)
		return false;
	else if (health < 5)
		mSprite.setTextureRect(mTexture3);
	else if (health < 10)
		mSprite.setTextureRect(mTexture2);
	else
		mSprite.setTextureRect(mTexture1);

	return true;
}

