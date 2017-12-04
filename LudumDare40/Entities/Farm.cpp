#include <cstdlib>

#include "Farm.h"


Farm::Farm(GameManager & aGameManager, sf::Vector2<uint32_t> aTileCoord, uint32_t &aGrainCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTileObject(mGameManager.GetMapManager(), aTileCoord, 5, 5),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mTimeElapsed(sf::Time::Zero),
	mGrainCounter(aGrainCounter)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTexture1);
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
}

Farm::~Farm()
{
}

bool Farm::Update(sf::Time dt)
{
	mTimeElapsed += dt;

	if (mTileObject.GetKeenFactor() == 0) return false;

	if (mTimeElapsed < sf::seconds(3.f))
	{
		mSprite.setTextureRect(mTexture1);
	}
	else if (mTimeElapsed < sf::seconds(6.f))
	{
		mSprite.setTextureRect(mTexture2);
	}
	else if (mTimeElapsed < sf::seconds(9.f))
	{
		mSprite.setTextureRect(mTexture3);
	}
	else
	{
		mTimeElapsed -= sf::seconds(9.f);
		mGrainCounter += std::rand() % 6 + 1;
	}

	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);

	return true;
}
