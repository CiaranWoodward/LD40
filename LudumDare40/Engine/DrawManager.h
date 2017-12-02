#pragma once
#include "DrawObject.h"

#include <vector>
#include <iterator>
#include <algorithm>

class DrawManager
{
	friend DrawObject;

public:
	DrawManager();
	~DrawManager();

	void Refresh();

protected:
	void Add(DrawObject &DrawObject);
	void Remove(DrawObject &DrawObject);

private:
	bool CompareDrawObjects(DrawObject *l, DrawObject *r);

	std::vector<DrawObject*> mDrawObjects;
};

