#include "WindowManager.h"

WindowManager::WindowManager() :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 40"),
	mTestShape(100.0f)
{
	mTestShape.setFillColor(sf::Color::Green);

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
	mWindow.draw(mTestShape);
	mWindow.display();

	return true;
}
