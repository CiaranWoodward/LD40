#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../Engine/EnemyObject.h"

class Bullet :
	public LogicObject
{
public:
	Bullet(GameManager &aGameManager, sf::Vector2f aWorldCoords);
	~Bullet();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	DrawObject mDrawObject;
	sf::Vector2f mWorldCoords;
	sf::Vector2f mSpeed;
	sf::Vector2f mAccel;
	sf::Time mCooldown;

	const float mMaxSpeed = 70.f;
	const float mMaxAccel = 300.f;

	EnemyObject *mTarget;

	const sf::IntRect mTexture1 = { 285, 721, 14, 14 };
};

