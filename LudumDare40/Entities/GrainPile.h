#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class GrainPile : 
	public LogicObject
{
public:
	GrainPile(GameManager &aGameManager);
	~GrainPile();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;
};

