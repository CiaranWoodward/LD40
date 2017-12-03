#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class CorpsePile :
	public LogicObject
{
public:
	CorpsePile(GameManager &aGameManager);
	~CorpsePile();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;
};

