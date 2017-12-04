#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(GameManager & aGameManager, uint32_t & aGrainCounter) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mGrainCounter(aGrainCounter),
	mTime(sf::Time::Zero)
{
}

EnemySpawner::~EnemySpawner()
{
}

bool EnemySpawner::Update(sf::Time dt)
{
	mTime += dt;

	sf::Time targetSpawn = sf::seconds(10000.f * (1.f / (mGrainCounter + 1000.f)));

	if (mTime > targetSpawn)
	{
		mTime -= targetSpawn;
		new Enemy(mGameManager);
	}

	return true;
}
