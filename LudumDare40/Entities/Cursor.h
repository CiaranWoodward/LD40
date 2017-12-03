#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Cursor
{
public:
	Cursor(GameManager &aGameManager);
	~Cursor();

	bool HandleMouseEvent(sf::Event &aMouseEvent);
	bool Cursor::Update();

private:
	enum kItemTypes
	{
		kItemClear = 0,
		kItemWall,
		kItemFarm,
		kItemBait,
		kItemTurret
	};

	GameManager &mGameManager;

	sf::Sprite mSprite;
	DrawObject mDrawObject;

	enum kItemTypes mCurItem;
};

