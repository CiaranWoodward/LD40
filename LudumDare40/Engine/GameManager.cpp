#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(mDrawManager)
{
}


GameManager::~GameManager()
{
}

int GameManager::run()
{
	bool run = true;

	sf::Sprite testSprite;
	testSprite.setTexture(mDrawManager.GetGlobalTexture());
	testSprite.setTextureRect(sf::IntRect(216, 28, 54, 80));
	testSprite.setPosition(sf::Vector2f(100, 100));
	DrawObject test(mDrawManager, testSprite, 10);
	
	while (run)
	{
		run = run && mWindowManager.Update();
	}
	return 0;
}
