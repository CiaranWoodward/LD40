#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/PlayerChair.h"
#include "../Entities/GrainPile.h"
#include "../Entities/CorpsePile.h"
#include "../Entities/Wall.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(mDrawManager),
	mLogicManager()
{
}


GameManager::~GameManager()
{
}

int GameManager::run()
{
	bool run = true;

	//Game counters
	uint32_t numGrain = 10;
	uint32_t numCorpses = 0;
	
	new GrainPile(*this, numGrain);
	new CorpsePile(*this, numCorpses);
	new PlayerChair(*this);
	new Wall(*this, sf::Vector2<uint32_t>(28, 28));
	new Wall(*this, sf::Vector2<uint32_t>(28, 29));
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mLogicManager.Update();
	}
	return 0;
}
