#pragma once
#include "SFML\System.hpp"

class LogicManager;

//Classes deriving from LogicObject must be dynamically allocated only, as memory is managed by the LogicManager.
class LogicObject
{
public:
	LogicObject(LogicManager &aLogicManager);
	virtual ~LogicObject();

	//To free, return false from Update
	virtual bool Update(sf::Time dt) = 0;
};

