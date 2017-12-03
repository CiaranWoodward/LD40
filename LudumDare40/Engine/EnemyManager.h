#pragma once
#include <vector>

#include "EnemyObject.h"

class EnemyManager
{
	friend EnemyObject;
public:
	EnemyManager();
	~EnemyManager();

	bool Update();

	EnemyObject *GetClosestEnemy(sf::Vector2f aWorldCoord);

protected:
	void Add(EnemyObject &aEnemyObject);

private:
	std::vector<EnemyObject*> mEnemyObjects;
};

