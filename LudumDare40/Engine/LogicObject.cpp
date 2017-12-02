#include "LogicObject.h"
#include "LogicManager.h"

LogicObject::LogicObject(LogicManager &aLogicManager)
{
	aLogicManager.Add(this);
}

LogicObject::~LogicObject()
{
}
