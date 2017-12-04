#include "WindowManager.h"
#include "MapManager.h"
#include "../Entities/Cursor.h"

WindowManager::WindowManager(GameManager &aGameManager) :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 40"),
	mGameManager(aGameManager),
	mHUD()
{
	sf::Vector2f center = MapManager::GetTileDrawCenter(sf::Vector2<uint32_t>(MapManager::kMaxX/2, MapManager::kMaxY/2));
	//sf::Vector2f dimens(640.f, 360.f);
	sf::Vector2f dimens(1280.f, 720.f);
	mView = sf::View(center, dimens);
	mWindow.setView(mView);
	mWindow.setFramerateLimit(60);

	mHUD.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mHUD.setTextureRect(sf::IntRect(1473, 177, 255, 687));
	mHUD.setPosition(1280, 720);
	mHUD.setOrigin(mHUD.getTextureRect().width, mHUD.getTextureRect().height);
	mHUD.setScale(0.5f, 0.5f);
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
	mWindow.setView(mView);
	mGameManager.GetDrawManager().DrawAll(mWindow);
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mHUD);
	mWindow.setView(mView);
	mWindow.display();
	
	return true;
}
