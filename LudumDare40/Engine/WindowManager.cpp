#include "WindowManager.h"

WindowManager::WindowManager(DrawManager &aDrawManager) :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 40"),
	mDrawManager(aDrawManager)
{
	
}


WindowManager::~WindowManager()
{
}

bool WindowManager::Update()
{
	if (!mWindow.isOpen()) return false;

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	mWindow.clear();
	mDrawManager.DrawAll(mWindow);
	mWindow.display();

	return true;
}
