#include "EnemyManager.h"

EnemyManager::EnemyManager(uint32_t &aCorpseCounter, uint32_t &aCorpseTotal) :
	mCorpseCounter(aCorpseCounter),
	mCorpseTotal(aCorpseTotal)
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
			mCorpseCounter++;
			mCorpseTotal++;
		}
	}
	mEnemyObjects.erase(std::remove(mEnemyObjects.begin(), mEnemyObjects.end(), reinterpret_cast<EnemyObject*>(NULL)), mEnemyObjects.end());
	return true;
}

EnemyObject *EnemyManager::GetClosestEnemy(sf::Vector2f aWorldCoord)
{
	EnemyObject *rval = NULL;
	float curDist = 0.f;

	for (EnemyObject *eo : mEnemyObjects)
	{
		if (eo == NULL || eo->Damage(0)) continue;
		if (rval == NULL)
		{
			rval = eo;
			curDist = eo->DistanceTo(aWorldCoord);
		}
		else
		{
			if (eo->DistanceTo(aWorldCoord) < curDist)
			{
				rval = eo;
				curDist = eo->DistanceTo(aWorldCoord);
			}
		}
	}

	return rval;
}

void EnemyManager::Add(EnemyObject & aEnemyObject)
{
	mEnemyObjects.push_back(&aEnemyObject);
}
