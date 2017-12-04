#include "LogicManager.h"



LogicManager::LogicManager() :
	mLogicObjects(),
	mClock()
{
	mClock.restart();
}

LogicManager::~LogicManager()
{
	for (auto it = mLogicObjects.begin(); it != mLogicObjects.end(); )
	{
		delete(*it);
		it++;
	}
	mLogicObjects.erase(mLogicObjects.begin(), mLogicObjects.end());
}

bool LogicManager::Update()
{
	sf::Time dt = mClock.restart();

	for(auto it = mLogicObjects.begin(); it != mLogicObjects.end(); )
	{
		if (!(*it)->Update(dt))
		{
			delete (*it);
			it = mLogicObjects.erase(it);
		}
		else
		{
			it++;
		}
	}

	return true;
}

void LogicManager::Add(LogicObject *aLogicObject)
{
	mLogicObjects.push_back(aLogicObject);
}
