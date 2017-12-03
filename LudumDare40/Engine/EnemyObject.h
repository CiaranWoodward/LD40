#pragma once
#include <SFML\System.hpp>

class GameManager;

class EnemyObject
{
public:
	EnemyObject(GameManager &aGameManager, sf::Vector2f &aWorldCoords, int32_t aHealthMax);
	~EnemyObject();

	//Returns true if enemy died
	bool Damage(int32_t damage);

	float DistanceTo(sf::Vector2f aWorldCoords);

private:
	GameManager &mGameManager;

	int32_t mHealth;
	sf::Vector2f &mWorldCoords;
};

