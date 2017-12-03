#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Wall :
	public LogicObject
{
public:
	Wall(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord);
	~Wall();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;
};

