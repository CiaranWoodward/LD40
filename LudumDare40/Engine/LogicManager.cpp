#include "LogicManager.h"



LogicManager::LogicManager() :
	mLogicObjects(),
	mClock()
{
	mClock.restart();
}

LogicManager::~LogicManager()
{
	for (LogicObject *&lo : mLogicObjects)
	{
		delete (lo);
		lo = NULL;
	}

	mLogicObjects.erase(std::remove(mLogicObjects.begin(), mLogicObjects.end(), reinterpret_cast<LogicObject*>(NULL)), mLogicObjects.end());
}

bool LogicManager::Update()
{
	sf::Time dt = mClock.restart();

	for (uint32_t i = 0; i < mLogicObjects.size(); i++)
	{
		LogicObject *&lo = mLogicObjects.at(i);
		if (!(lo)->Update(dt))
		{
			delete (lo);
			lo = NULL;
		}
	}

	mLogicObjects.erase(std::remove(mLogicObjects.begin(), mLogicObjects.end(), reinterpret_cast<LogicObject*>(NULL)), mLogicObjects.end());

	return true;
}

void LogicManager::Add(LogicObject *aLogicObject)
{
	mLogicObjects.push_back(aLogicObject);
}
