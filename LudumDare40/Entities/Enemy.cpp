#include "Enemy.h"



Enemy::Enemy(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
}

Enemy::~Enemy()
{
}



bool Enemy::Update(sf::Time dt)
{
	return true;
}
