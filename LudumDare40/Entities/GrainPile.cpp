#include "GrainPile.h"
#include <string>



GrainPile::GrainPile(GameManager &aGameManager, uint32_t &aGrainCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextCounter("000", mGameManager.GetDrawManager().GetGlobalFont(), 15),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(24, 26), 1, aGrainCounter),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextCounter, INT32_MAX),
	mGrainCounter(aGrainCounter),
	mPrevGrainCounter(aGrainCounter)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 41, 106, 53));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - 1); //-1 because takes up extra tiles

	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 0)).SetTileObject(&mTileObject);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 1)).SetTileObject(&mTileObject);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(0, 1)).SetTileObject(&mTileObject);

	mTextCounter.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 100.f));
	mTextCounter.setFillColor(sf::Color::White);
}


GrainPile::~GrainPile()
{
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 0)).SetTileObject(NULL);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(1, 1)).SetTileObject(NULL);
	mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords() - sf::Vector2u(0, 1)).SetTileObject(NULL);
}

bool GrainPile::Update(sf::Time dt)
{
	int32_t drawLevelOffset = MapManager::kTileHeight + 20;

	//Grain calcs for loss
	int32_t grainDiff = mPrevGrainCounter - mTileObject.GetKeenFactor();
	mGrainCounter -= grainDiff;
	mTileObject.SetKeenFactor(mGrainCounter);
	mPrevGrainCounter = mGrainCounter;

	//Set tile brightness
	uint8_t oPac = static_cast<uint8_t>(std::log2(mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords()).mSmellFactor) * 8.0);
	mSprite.setColor(sf::Color(oPac, oPac, oPac));

	mTextCounter.setString(std::to_string(mGrainCounter));
	mTextCounter.setOrigin(mTextCounter.getLocalBounds().width / 2, 0);

	if (mGrainCounter < 5)
		mSprite.setTextureRect(mTexture1);
	else if (mGrainCounter < 30)
		mSprite.setTextureRect(mTexture2);
	else if (mGrainCounter < 60)
		mSprite.setTextureRect(mTexture3);
	else if (mGrainCounter < 120)
		mSprite.setTextureRect(mTexture4);
	else if (mGrainCounter < 500)
		mSprite.setTextureRect(mTexture5);
	else if (mGrainCounter < 1500)
		mSprite.setTextureRect(mTexture6);
	else
	{
		mSprite.setTextureRect(mTexture7);
		drawLevelOffset = 1;
	}

	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y) - drawLevelOffset); //-1 because takes up extra tiles
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);

	return true;
}
