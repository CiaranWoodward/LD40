#include "WindowManager.h"
#include "MapManager.h"

WindowManager::WindowManager(DrawManager &aDrawManager) :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 40"),
	mDrawManager(aDrawManager)
{
	sf::Vector2f center = MapManager::GetTileDrawCenter(sf::Vector2<uint32_t>(MapManager::kMaxX/2, MapManager::kMaxY/2));
	sf::Vector2f dimens(640.f, 360.f);
	//sf::Vector2f dimens(1280.f, 720.f);
	mWindow.setView(sf::View(center, dimens));
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
