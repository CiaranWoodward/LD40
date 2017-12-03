#pragma once

#include "DrawManager.h"
#include "WindowManager.h"
#include "LogicManager.h"
#include "MapManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	int run();

	MapManager &GetMapManager() { return mMapManager; }
	LogicManager &GetLogicManager() { return mLogicManager; }
	DrawManager &GetDrawManager() { return mDrawManager; }
	WindowManager &GetWindowManager() { return mWindowManager; }

private:
	DrawManager mDrawManager;
	WindowManager mWindowManager;
	LogicManager mLogicManager;
	MapManager mMapManager;

	uint32_t mCorpseCounter;
	uint32_t mGrainCounter;
};

