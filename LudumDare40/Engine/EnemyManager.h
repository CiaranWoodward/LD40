#pragma once
#include <vector>

#include "EnemyObject.h"

class EnemyManager
{
	friend EnemyObject;
public:
	EnemyManager(uint32_t &aCorpseCounter);
	~EnemyManager();

	bool Update();

	EnemyObject *GetClosestEnemy(sf::Vector2f aWorldCoord);

protected:
	void Add(EnemyObject &aEnemyObject);

private:
	std::vector<EnemyObject*> mEnemyObjects;

	uint32_t &mCorpseCounter;
};

