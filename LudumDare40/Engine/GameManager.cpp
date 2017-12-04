#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/PlainTiles.h"
#include "../Entities/PlayerChair.h"
#include "../Entities/GrainPile.h"
#include "../Entities/CorpsePile.h"
#include "../Entities/Wall.h"
#include "../Entities/Farm.h"
#include "../Entities/Cursor.h"
#include "../Entities/Enemy.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(*this),
	mLogicManager(),
	mEnemyManager(),
	mCorpseCounter(100),
	mGrainCounter(20)
{
	std::srand(std::time(0));
	mCursor = new Cursor(*this, mGrainCounter, mCorpseCounter);
}


GameManager::~GameManager()
{
	delete mCursor;
}

int GameManager::run()
{
	bool run = true;
	
	new GrainPile(*this, mGrainCounter);
	new CorpsePile(*this, mCorpseCounter);
	new PlayerChair(*this);
	new Wall(*this, sf::Vector2<uint32_t>(28, 28));
	new Wall(*this, sf::Vector2<uint32_t>(28, 29));
	new Farm(*this, sf::Vector2<uint32_t>(30, 30), mGrainCounter);
	new Farm(*this, sf::Vector2<uint32_t>(31, 30), mGrainCounter);
	new Farm(*this, sf::Vector2<uint32_t>(31, 31), mGrainCounter);
	new Farm(*this, sf::Vector2<uint32_t>(30, 31), mGrainCounter);
	new PlainTiles(*this);

	Enemy *enem = new Enemy(*this);
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mMapManager.Update();
		run = run && mLogicManager.Update();
		run = run && mCursor->Update();
	}
	enem->Update(sf::Time::Zero);
	return 0;
}
