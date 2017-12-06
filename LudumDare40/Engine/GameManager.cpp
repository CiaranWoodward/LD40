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
#include "../Entities/EnemySpawner.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(*this),
	mLogicManager(),
	mEnemyManager(mCorpseCounter, mCorpseTotal),
	mCorpseCounter(4),
	mCorpseTotal(4),
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
	new Farm(*this, sf::Vector2<uint32_t>(26, 25), mGrainCounter);
	new Farm(*this, sf::Vector2<uint32_t>(25, 26), mGrainCounter);
	new PlainTiles(*this);

	new EnemySpawner(*this, mGrainCounter);
	
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mMapManager.Update();
		run = run && mLogicManager.Update();
		run = run && mCursor->Update();
		run = run && mEnemyManager.Update();
	}
	return 0;
}
