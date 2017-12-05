#include "Turret.h"
#include "../Entities/Bullet.h"


Turret::Turret(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord, uint32_t &aGrainCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mFirePoint(),
	mTileObject(mGameManager.GetMapManager(), aTileCoord, 5, 5),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mGrainCounter(aGrainCounter),
	mCooldown(sf::seconds(1.f))
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTexture1);
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
	mFirePoint = MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()) - sf::Vector2f(-13.f, 40.f);
}


Turret::~Turret()
{
}

bool Turret::Update(sf::Time dt)
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

	//If not enough food to shoot, continue
	if (mGrainCounter <= 0)
		return true;

	//Shoot if enemy is nearby
	EnemyObject *mEnemy = mGameManager.GetEnemyManager().GetClosestEnemy(mFirePoint);

	if (mEnemy != NULL && !mEnemy->Damage(0))
	{
		sf::Vector2f targetCoords = mEnemy->GetWorldCoords();
		sf::Vector2f v = targetCoords - mFirePoint;
		float mag = std::sqrtf((v.x * v.x) + (4 * v.y * v.y));

		if (mag < 350.f)
		{
			new Bullet(mGameManager, mFirePoint);
			mGrainCounter--;
			mCooldown = sf::seconds(8.f);
		}
	}

	return true;
}
