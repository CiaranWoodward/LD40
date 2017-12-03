#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Cursor.h"



Cursor::Cursor(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, INT32_MAX - 10)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(54, 94, 54, 41));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mSprite.setColor(sf::Color(255, 255, 255, 128));
}


Cursor::~Cursor()
{
}

bool Cursor::Update(sf::Time dt)
{
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(mGameManager.GetWindowManager().GetWindow());
	// convert it to world coordinates
	sf::Vector2f worldPos = mGameManager.GetWindowManager().GetWindow().mapPixelToCoords(pixelPos);

	int32_t div = MapManager::kTileWidth + (2 * MapManager::kTileHeight);
	int32_t Sy = static_cast<int32_t>(worldPos.y);
	int32_t Sx = static_cast<int32_t>(worldPos.x);

	sf::Vector2<uint32_t> tileCoords(((2 * Sy) + Sx) / div, ((2 * Sy) - Sx) / div);
	tileCoords += {1, 1};

	mSprite.setPosition(MapManager::GetTileDrawOrigin(tileCoords));
	mDrawObject.SetDrawLevel(mSprite.getPosition().y);


	return true;
}