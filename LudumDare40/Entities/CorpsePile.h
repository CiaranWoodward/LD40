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

	const sf::IntRect mTexture1 = { 106, 41, 106, 53 };
	const sf::IntRect mTexture2 = { 271, 446, 106, 53 };
	const sf::IntRect mTexture3 = { 271, 446 + 53, 106, 53 };
	const sf::IntRect mTexture4 = { 271, 446 + (53 * 2), 106, 53 };
	const sf::IntRect mTexture5 = { 271, 446 + (53 * 3), 106, 53 };
	const sf::IntRect mTexture6 = { 271, 446 + (53 * 4), 106, 53 };
};

