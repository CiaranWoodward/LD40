#include <SFML/Graphics.hpp>
#include "GameManager.h"



GameManager::GameManager() :
	mWindowManager()
{
}


GameManager::~GameManager()
{
}

int GameManager::run()
{
	bool run = true;
	
	while (run)
	{
		run = run && mWindowManager.Update();
	}
	return 0;
}
