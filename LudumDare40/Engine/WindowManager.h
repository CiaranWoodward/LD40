#pragma once
#include <SFML/Graphics.hpp>

class WindowManager
{
public:
	WindowManager();
	~WindowManager();

	//Returns false if close is requested
	bool Update();

private:
	sf::RenderWindow mWindow;
	sf::CircleShape mTestShape;
};

