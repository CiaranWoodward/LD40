#pragma once

#include "WindowManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	int run();

private:
	WindowManager mWindowManager;
};

