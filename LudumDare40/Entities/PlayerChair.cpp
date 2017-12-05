#include "PlayerChair.h"
#include "../Engine/EnemyObject.h"
#include "../Entities/Bullet.h"



PlayerChair::PlayerChair(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mFirePoint(),
	mCooldown(sf::Time::Zero),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(25, 25), 100, 1),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(216, 28, 54, 80));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
	mFirePoint = MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()) - sf::Vector2f(0.f, 73.f);
}


PlayerChair::~PlayerChair()
{
}

bool PlayerChair::Update(sf::Time dt)
{
	//Set tile brightness
	uint8_t oPac = static_cast<uint8_t>(std::log2(mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords()).mSmellFactor) * 8.0);
	mSprite.setColor(sf::Color(oPac, oPac, oPac));

	//If in cooldown, just continue
	mCooldown -= dt;
	if (mCooldown <= sf::Time::Zero)
	{
		mCooldown = sf::Time::Zero;
	}
	else
	{
		return true;
	}

	//Shoot if enemy is nearby
	EnemyObject *mEnemy = mGameManager.GetEnemyManager().GetClosestEnemy(mFirePoint);

	if (mEnemy != NULL && !mEnemy->Damage(0))
	{
		sf::Vector2f targetCoords = mEnemy->GetWorldCoords();
		sf::Vector2f v = targetCoords - mFirePoint;
		float mag = std::sqrtf((v.x * v.x) + (4 * v.y * v.y));

		if (mag < 600.f)
		{
			new Bullet(mGameManager, mFirePoint);
			mCooldown = sf::seconds(3.f);
		}
	}

	return true;
}
