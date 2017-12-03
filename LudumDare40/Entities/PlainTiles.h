#pragma once
#include "../Engine/MapManager.h"
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class PlainTiles :
	public LogicObject
{
public:
	PlainTiles(GameManager &aGameManager);
	~PlainTiles();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprites[MapManager::kMaxX][MapManager::kMaxY];
	DrawObject *mDrawObjects[MapManager::kMaxX][MapManager::kMaxY];
};

