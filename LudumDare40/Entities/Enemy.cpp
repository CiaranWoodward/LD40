#include <cstdlib>

#include "Enemy.h"



Enemy::Enemy(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mWorldCoords(),
	mSpeed(0.f, 0.f),
	mAccel(0.f, 0.f),
	mCooldown(sf::Time::Zero),
	mEnemyObject(mGameManager, mWorldCoords, 2 + mGameManager.GetDifficulty()),
	mDie(0)
{
	//Spawn along an edge
	uint8_t rn = std::rand() % 4;
	sf::Vector2<uint32_t> tileCoords;
	switch (rn)
	{
	case 0:
		tileCoords.x = 1;
		tileCoords.y = std::rand() % (MapManager::kMaxY - 1);
		break;

	case 1:
		tileCoords.x = MapManager::kMaxX-2;
		tileCoords.y = std::rand() % (MapManager::kMaxY - 1);
		break;

	case 2:
		tileCoords.y = MapManager::kMaxY-2;
		tileCoords.x = std::rand() % (MapManager::kMaxX - 1);
		break;

	default:
		tileCoords.y = 0;
		tileCoords.x = std::rand() % (MapManager::kMaxX - 1);
		break;
	}

	mWorldCoords = MapManager::GetTileDrawCenter(tileCoords);

	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTexture1);
	mSprite.setPosition(mWorldCoords);
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(mWorldCoords.y + 3));
}

Enemy::~Enemy()
{
}

bool Enemy::Update(sf::Time dt)
{
	//Hack
	if (mDie > 5) return false;
	if (mEnemyObject.Damage(0)) mDie++;

	//Apply Movement
	{
		//Check Accelleration doesn't cause velocity to go too high
		sf::Vector2f v = mAccel * dt.asSeconds() + mSpeed;
		float checkSpeed = std::sqrtf((v.x * v.x) + (v.y * v.y));

		if (checkSpeed > mMaxSpeed)
		{
			v = ((v / checkSpeed)*mMaxSpeed);
		}

		sf::Vector2f deltaMove = (v + mSpeed) * dt.asSeconds() / 2.f;
		deltaMove.y /= 2.f; //Half the move distance on the Y axis to account for dimetric projection
		mWorldCoords = mWorldCoords + deltaMove;
		mSpeed = v;

		//Update sprite
		mSprite.setPosition(mWorldCoords);
		mDrawObject.SetDrawLevel(static_cast<int32_t>(mWorldCoords.y + 3));

	}

	//Get current tile
	int32_t div = MapManager::kTileWidth + (2 * MapManager::kTileHeight);
	int32_t Sy = static_cast<int32_t>(mWorldCoords.y);
	int32_t Sx = static_cast<int32_t>(mWorldCoords.x);

	sf::Vector2<uint32_t> tileCoords(((2 * Sy) + Sx) / div, ((2 * Sy) - Sx) / div);
	tileCoords += {1, 1};

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

	//Set sprite darkness
	uint8_t oPac = static_cast<uint8_t>(std::log2(mGameManager.GetMapManager().GetTile(tileCoords).mSmellFactor) * 8.0);
	mSprite.setColor(sf::Color(oPac, oPac, oPac));
	
	//If current tile is blocking or attractive, stop and attack it
	if (mGameManager.GetMapManager().GetTile(tileCoords).GetBlockFactor() > 0 ||
		mGameManager.GetMapManager().GetTile(tileCoords).GetKeenFactor() > 0)
	{
		mSpeed.x = 0;
		mSpeed.y = 0;
		mAccel.x = 0;
		mAccel.y = 0;
		if (!mGameManager.GetMapManager().GetTile(tileCoords).Damage(1))
		{
			mCooldown = sf::seconds(1.f);
			return true;
		}
	}

	//Get best smelling neighbor
	uint32_t bestSmell = 0;
	sf::Vector2<uint32_t> bestCoords(0, 0);
	for (int x = -1; x < 2; x += 2)
	{
		for (int y = -1; y < 2; y += 2)
		{
			sf::Vector2<uint32_t> curCoords(tileCoords.x + x, tileCoords.y + y);
			uint32_t curSmell = mGameManager.GetMapManager().GetTile(curCoords).mSmellFactor;

			if (curSmell > bestSmell)
			{
				bestSmell = curSmell;
				bestCoords = curCoords;
			}
		}
	}

	//Special case for no smell - move towards center
	if (bestSmell == 0)
	{
		if (tileCoords.x < (MapManager::kMaxX / 2))
			bestCoords = sf::Vector2<uint32_t>(tileCoords.x + 1, tileCoords.y);
		else if (tileCoords.y < (MapManager::kMaxY / 2))
			bestCoords = sf::Vector2<uint32_t>(tileCoords.x, tileCoords.y + 1);
		else if (tileCoords.y > (MapManager::kMaxY / 2))
			bestCoords = sf::Vector2<uint32_t>(tileCoords.x, tileCoords.y - 1);
		else if (tileCoords.x > (MapManager::kMaxX / 2))
			bestCoords = sf::Vector2<uint32_t>(tileCoords.x - 1, tileCoords.y);
	}

	//accellerate towards neighbor
	sf::Vector2f targetCoords = MapManager::GetTileDrawCenter(bestCoords);
	sf::Vector2f v = targetCoords - mWorldCoords;
	float mag = std::sqrtf((v.x * v.x) + (4 * v.y * v.y));
	if (mag > 0)
	{
		mAccel = (v / mag) * mMaxAccel;
	}
	else
	{
		mAccel = sf::Vector2f(0.f, 0.f);
	}

	if (mAccel.x > 0)
		mSprite.setScale(-1.f, 1.f);
	else
		mSprite.setScale(1.f, 1.f);

	return true;
}
