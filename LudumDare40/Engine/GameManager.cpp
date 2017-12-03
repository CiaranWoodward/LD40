#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/PlainTiles.h"
#include "../Entities/PlayerChair.h"
#include "../Entities/GrainPile.h"
#include "../Entities/CorpsePile.h"
#include "../Entities/Wall.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(mDrawManager),
	mLogicManager(),
	mCorpseCounter(0),
	mGrainCounter(20)
{
}


GameManager::~GameManager()
{
}

int GameManager::run()
{
	bool run = true;
	
	
	new GrainPile(*this, mGrainCounter);
	new CorpsePile(*this, mCorpseCounter);
	new PlayerChair(*this);
	new Wall(*this, sf::Vector2<uint32_t>(28, 28));
	new Wall(*this, sf::Vector2<uint32_t>(28, 29));
	new PlainTiles(*this);
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mLogicManager.Update();
	}
	return 0;
}
