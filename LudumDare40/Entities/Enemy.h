#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Enemy :
	public LogicObject
{
public:
	Enemy(GameManager &aGameManager);
	~Enemy();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;

	DrawObject mDrawObject;

	const sf::IntRect mTexture1 = { 0, 100, 47, 28 };
};

