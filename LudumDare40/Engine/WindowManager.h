#pragma once
#include <SFML/Graphics.hpp>

#include "DrawManager.h"

class WindowManager
{
public:
	WindowManager(DrawManager &aDrawManager);
	~WindowManager();

	//Returns false if close is requested
	bool Update();

	sf::RenderWindow &GetWindow() { return mWindow; }

private:
	sf::RenderWindow mWindow;

	DrawManager &mDrawManager;
};

