#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Farm :
	public LogicObject
{
public:
	Farm(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord, uint32_t &aGrainCounter);
	~Farm();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;

	sf::Time mTimeElapsed;

	uint32_t &mGrainCounter;

	const sf::IntRect mTexture1 = { 162, 162, 54, 27 };
	const sf::IntRect mTexture2 = { 162, 135, 54, 27 };
	const sf::IntRect mTexture3 = { 162, 102, 54, 33 };
};

