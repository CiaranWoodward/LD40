#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Cursor :
	public LogicObject
{
public:
	Cursor(GameManager &aGameManager);
	~Cursor();

	bool Cursor::Update(sf::Time dt);

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	DrawObject mDrawObject;
};

