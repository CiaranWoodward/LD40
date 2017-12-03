#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/PlayerChair.h"
#include "../Entities/GrainPile.h"
#include "../Entities/CorpsePile.h"

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

	new PlayerChair(*this);
	new GrainPile(*this);
	new CorpsePile(*this);
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mLogicManager.Update();
	}
	return 0;
}
