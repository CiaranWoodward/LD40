#pragma once

#include "DrawManager.h"
#include "WindowManager.h"
#include "LogicManager.h"
#include "MapManager.h"

class Cursor;

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
	Cursor &GetCursor() { return *mCursor; }

private:
	DrawManager mDrawManager;
	WindowManager mWindowManager;
	LogicManager mLogicManager;
	MapManager mMapManager;

	Cursor *mCursor;

	uint32_t mCorpseCounter;
	uint32_t mGrainCounter;
};

