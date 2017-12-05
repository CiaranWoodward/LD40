#include "Bullet.h"


Bullet::Bullet(GameManager &aGameManager, sf::Vector2f aWorldCoords) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, INT32_MAX-40),
	mWorldCoords(aWorldCoords),
	mSpeed(0.f, 0.f),
	mAccel(0.f, 0.f),
	mCooldown(sf::seconds(1.f)),
	mTarget(static_cast<EnemyObject *>(NULL))
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTexture1);
	mSprite.setPosition(mWorldCoords);
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
}

Bullet::~Bullet()
{
}

bool Bullet::Update(sf::Time dt)
{
	if (mTarget == NULL || mTarget->Damage(0)) mTarget = NULL;

	//If in cooldown, just continue
	mCooldown -= dt;
	if (mCooldown <= sf::Time::Zero)
	{
		mSprite.setColor(sf::Color(255, 255, 255));

		if (mCooldown < sf::seconds(-20))
			return false;
	}
	else
	{
		int8_t glow = static_cast<uint8_t>(255.f * (1.f - mCooldown.asSeconds()));
		mSprite.setColor(sf::Color(glow, glow, glow));
		return true;
	}

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
	}

	if (mTarget != NULL && !mTarget->Damage(0))
	{

		//accellerate towards neighbor
		sf::Vector2f targetCoords = mTarget->GetWorldCoords();
		sf::Vector2f v = targetCoords - mWorldCoords;
		float mag = std::sqrtf((v.x * v.x) + (4 * v.y * v.y));

		if (mag < 5)
		{
			//hit
			mTarget->Damage(1);
			return false;
		}

		mAccel = (v / mag) * mMaxAccel;

		if (mAccel.x > 0)
			mSprite.setScale(-1.f, 1.f);
		else
			mSprite.setScale(1.f, 1.f);
	}
	else
	{
		mTarget = mGameManager.GetEnemyManager().GetClosestEnemy(mWorldCoords);
	}

	return true;
}
