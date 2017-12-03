#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

bool EnemyManager::Update()
{
	for (EnemyObject *&eo : mEnemyObjects)
	{
		if (eo->Damage(0))
		{
			eo = NULL;
		}
	}
	mEnemyObjects.erase(std::remove(mEnemyObjects.begin(), mEnemyObjects.end(), NULL), mEnemyObjects.end());
	return true;
}

EnemyObject *EnemyManager::GetClosestEnemy(sf::Vector2f aWorldCoord)
{
	EnemyObject *rval = NULL;
	float curDist = 0.f;

	for (EnemyObject *eo : mEnemyObjects)
	{
		if (rval == NULL)
		{
			rval = eo;
		}
		else
		{
			if (eo->DistanceTo(aWorldCoord) < curDist)
			{
				rval = eo;
			}
		}
	}

	return rval;
}

void EnemyManager::Add(EnemyObject & aEnemyObject)
{
	mEnemyObjects.push_back(&aEnemyObject);
}
