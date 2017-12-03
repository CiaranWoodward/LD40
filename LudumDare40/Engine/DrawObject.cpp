#include "DrawObject.h"
#include "DrawManager.h"

DrawObject::DrawObject(DrawManager &aDrawManager, sf::Drawable &aDrawable, int32_t aDrawLevel) :
	mDrawManager(aDrawManager),
	mDrawable(aDrawable),
	mDrawLevel(aDrawLevel)
{
	mDrawManager.Add(*this);
	mDrawManager.Refresh();
}

DrawObject::~DrawObject()
{
	mDrawManager.Remove(*this);
}

void DrawObject::SetDrawLevel(int32_t aDrawLevel) 
{
	mDrawLevel = aDrawLevel; 
	mDrawManager.Refresh(); 
}