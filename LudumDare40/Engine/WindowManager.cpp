#include "WindowManager.h"
#include "MapManager.h"
#include "../Entities/Cursor.h"

WindowManager::WindowManager(GameManager &aGameManager) :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 40"),
	mGameManager(aGameManager)
{
	sf::Vector2f center = MapManager::GetTileDrawCenter(sf::Vector2<uint32_t>(MapManager::kMaxX/2, MapManager::kMaxY/2));
	sf::Vector2f dimens(640.f, 360.f);
	//sf::Vector2f dimens(1280.f, 720.f);
	mView = sf::View(center, dimens);
	mWindow.setView(mView);
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

		if (event.type == sf::Event::MouseButtonReleased)
			mGameManager.GetCursor().HandleMouseEvent(event);

	}

	mWindow.clear();
	mGameManager.GetDrawManager().DrawAll(mWindow);
	mWindow.display();

	return true;
}
