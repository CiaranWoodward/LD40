#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Cursor
{
public:
	Cursor(GameManager &aGameManager, uint32_t &aGrainCounter, uint32_t &aCorpseCounter);
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

	int GetGrainCost(enum kItemTypes type)
	{
		switch (type)
		{
		case kItemClear:
			return 0;
		case kItemWall:
			return 0;
		case kItemFarm:
			return 0;
		case kItemBait:
			return 20;
		case kItemTurret:
			return 2;
		}
	}

	int GetCorpseCost(enum kItemTypes type)
	{
		switch (type)
		{
		case kItemClear:
			return 0;
		case kItemWall:
			return 8;
		case kItemFarm:
			return 2;
		case kItemBait:
			return 0;
		case kItemTurret:
			return 4;
		}
	}

	GameManager &mGameManager;

	sf::Sprite mSprite;
	DrawObject mDrawObject;

	enum kItemTypes mCurItem;

	uint32_t &mGrainCounter;
	uint32_t &mCorpseCounter;
};

