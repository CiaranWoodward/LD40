#include <math.h>

#include "EnemyObject.h"



EnemyObject::EnemyObject(GameManager &aGameManager, sf::Vector2f &aWorldCoords, int32_t aHealthMax) :
	mGameManager(aGameManager),
	mWorldCoords(aWorldCoords),
	mHealth(aHealthMax)
{
}


EnemyObject::~EnemyObject()
{
}

bool EnemyObject::Damage(int32_t damage)
{
	mHealth -= damage;

	if (mHealth <= 0)
	{
		mHealth = 0;
	}

	return (mHealth == 0);
}

float EnemyObject::DistanceTo(sf::Vector2f aWorldCoords)
{
	sf::Vector2f delt = aWorldCoords - mWorldCoords;
	delt.y = delt.y * 2.f; //Double the Y to account for the dimetric projection

	return sqrtf((delt.x * delt.x) + (delt.y * delt.y));
}
