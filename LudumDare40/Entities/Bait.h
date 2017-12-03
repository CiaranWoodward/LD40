#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Bait :
	public LogicObject
{
public:
	Bait(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord);
	~Bait();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;

	const sf::IntRect mTexture1 = { 378, 108, 54, 27 };
	const sf::IntRect mTexture2 = { 378, 108 + 27, 54, 27 };
	const sf::IntRect mTexture3 = { 378, 108 + (27*2), 54, 27 };
};

