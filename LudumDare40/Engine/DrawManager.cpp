#include "DrawManager.h"



DrawManager::DrawManager() :
	mDrawObjects()
{
}

DrawManager::~DrawManager()
{
}

void DrawManager::Refresh()
{
	std::sort(mDrawObjects.begin, mDrawObjects.end, CompareDrawObjects);
}

void DrawManager::Add(DrawObject &aDrawObject)
{
	mDrawObjects.push_back(&aDrawObject);
	Refresh();
}

void DrawManager::Remove(DrawObject & aDrawObject)
{
	//Todo: Optimise this to the correct potential range if it becomes an issue
	mDrawObjects.erase(std::remove(mDrawObjects.begin(), mDrawObjects.end(), &aDrawObject), mDrawObjects.end());
}

bool DrawManager::CompareDrawObjects(DrawObject * l, DrawObject * r)
{
	return l->GetDrawLevel() < r->GetDrawLevel();;
}
