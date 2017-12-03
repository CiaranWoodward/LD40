#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class CorpsePile :
	public LogicObject
{
public:
	CorpsePile(GameManager &aGameManager, uint32_t &aCorpseCounter);
	~CorpsePile();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	sf::Text mTextCounter;

	TileObject mTileObject;
	DrawObject mDrawObject;
	DrawObject mDrawTextObject;

	uint32_t &mCorpseCounter;
};

