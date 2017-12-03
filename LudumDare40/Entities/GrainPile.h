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

	const sf::IntRect mTexture1 = { 0, 41, 106, 53 };
	const sf::IntRect mTexture2 = { 271, 110, 106, 53 };
	const sf::IntRect mTexture3 = { 271, 110 + 53, 106, 53 };
	const sf::IntRect mTexture4 = { 271, 110 + (53*2), 106, 53 };
	const sf::IntRect mTexture5 = { 271, 110 + (53 * 3), 106, 53 };
	const sf::IntRect mTexture6 = { 271, 110 + (53 * 4), 106, 53 };
	const sf::IntRect mTexture7 = { 271, 374, 106, 71 };
};

