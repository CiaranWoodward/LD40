#pragma once
#include <vector>
#include "LogicObject.h"

class LogicManager
{
	friend LogicObject;
public:
	LogicManager();
	~LogicManager();

	bool Update();

protected:
	void Add(LogicObject *aLogicObject);

private:
	std::vector<LogicObject*> mLogicObjects;
	sf::Clock mClock;
};

