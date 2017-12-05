#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Turret :
	public LogicObject
{
public:
	Turret(GameManager &aGameManager, sf::Vector2<uint32_t> aTileCoord, uint32_t &aGrainCounter);
	~Turret();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	TileObject mTileObject;
	DrawObject mDrawObject;

	sf::Time mCooldown;

	uint32_t &mGrainCounter;
	sf::Vector2f mFirePoint;

	const sf::IntRect mTexture1 = { 444, 115, 31, 46 };
};

