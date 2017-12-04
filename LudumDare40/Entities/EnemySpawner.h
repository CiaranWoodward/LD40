#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "Enemy.h"

class EnemySpawner :
	public LogicObject
{
public:
	EnemySpawner(GameManager &aGameManager, uint32_t &aGrainCounter);
	~EnemySpawner();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;
	uint32_t &mGrainCounter;

	sf::Time mTime;
};

