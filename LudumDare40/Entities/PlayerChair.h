#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../Engine/TileObject.h"
#include "../Engine/DrawObject.h"

class PlayerChair :
	public LogicObject
{
public:
	PlayerChair(GameManager &aGameManager);
	~PlayerChair();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;
};

