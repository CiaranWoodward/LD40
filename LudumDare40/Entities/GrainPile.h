#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class GrainPile : 
	public LogicObject
{
public:
	GrainPile(GameManager &aGameManager, uint32_t &aGrainCounter);
	~GrainPile();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	sf::Text mTextCounter;

	TileObject mTileObject;
	DrawObject mDrawObject;
	DrawObject mDrawTextObject;

	uint32_t &mGrainCounter;
};

