#pragma once

#include "DrawManager.h"
#include "WindowManager.h"
#include "LogicManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	int run();

private:
	DrawManager mDrawManager;
	WindowManager mWindowManager;
	LogicManager mLogicManager;
};

