#include "PlayerChair.h"
#include "../Engine/EnemyObject.h"
#include "../Entities/Bullet.h"



PlayerChair::PlayerChair(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextMessage("Welcome!", mGameManager.GetDrawManager().GetGlobalFont(), 20),
	mFirePoint(),
	mCooldown(sf::Time::Zero),
	mTextCooldown(sf::seconds(5.f)),
	mTileObject(mGameManager.GetMapManager(), sf::Vector2<uint32_t>(25, 25), 20, 20),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mTextCounter(0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextMessage, INT32_MAX)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(216, 28, 54, 80));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()).y));
	mFirePoint = MapManager::GetTileDrawOrigin(mTileObject.GetTileCoords()) - sf::Vector2f(0.f, 73.f);

	mTextMessage.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 75.f));
	mTextMessage.setOrigin(mTextMessage.getLocalBounds().width / 2, 0);
	mTextMessage.setFillColor(sf::Color::White);
}


PlayerChair::~PlayerChair()
{
}

bool PlayerChair::Update(sf::Time dt)
{
	//Set tile brightness
	uint8_t oPac = static_cast<uint8_t>(std::log2(mGameManager.GetMapManager().GetTile(mTileObject.GetTileCoords()).mSmellFactor) * 8.0);
	mSprite.setColor(sf::Color(oPac, oPac, oPac));

	if (isGameOver)
	{
		mTextMessage.setString("Game Over! Score: " + std::to_string(score));
		mTextMessage.setOrigin(mTextMessage.getLocalBounds().width / 2, 0);
		return true;
	}

	if (mTileObject.GetKeenFactor() <= 0)
	{
		isGameOver = true;
		return true;
	}

	if (score < mGameManager.GetGrainCount())
	{
		score = mGameManager.GetGrainCount();
	}

	//Text Cooldown
	mTextCooldown -= dt;
	if (mTextCooldown <= sf::Time::Zero)
	{
		mTextCooldown = sf::seconds(5.f);
		mTextCounter++;

		switch (mTextCounter)
		{
		case 1:
			mTextMessage.setString("What are you doing here?");
			break;
		case 3:
			mTextMessage.setString("Need grain!");
			break;
		case 4:
			mTextMessage.setString("Use the menu on the right to build");
			break;
		case 5:
			mTextMessage.setString("So many bugs...");
			break;
		case 6:
			mTextMessage.setString("I guess they like grain too...");
			break;
		case 8:
			mTextMessage.setString("I can bait the bugs with grain to keep them away");
			break;
		case 10:
			mTextMessage.setString("I can use dead bugs as fertilizer!");
			break;
		case 12:
			mTextMessage.setString("If i enchant the corpses, I can make them shoot!");
			break;
		case 16:
			mTextMessage.setString("\"C++ is faster\", they said, \"use that\", they said");
			break;
		case 20:
			mTextMessage.setString("Shame these aren't the only bugs...");
			break;
		case 25:
			mTextMessage.setString("I'm a bit deaf");
			break;
		case 30:
			mTextMessage.setString("The prophecies say that one day a great necromancer will sit on me.");
			break;
		case 35:
			mTextMessage.setString("I'm surprised this thing even runs at this point");
			break;
		default:
			mTextMessage.setString("");
			break;
		}
		mTextMessage.setOrigin(mTextMessage.getLocalBounds().width / 2, 0);

	}

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
