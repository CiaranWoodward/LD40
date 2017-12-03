#pragma once
#include <vector>
#include <iterator>
#include <algorithm>

#include <SFML\Graphics.hpp>

#include "DrawObject.h"

class DrawManager
{
	friend DrawObject;

public:
	DrawManager();
	~DrawManager();

	void Refresh();
	void DrawAll(sf::RenderWindow &aWindow);

	sf::Texture &GetGlobalTexture() { return mTexture; }
	sf::Font &GetGlobalFont() { return mFont; }

protected:
	void Add(DrawObject &DrawObject);
	void Remove(DrawObject &DrawObject);

private:
	static bool CompareDrawObjects(DrawObject *l, DrawObject *r);

	std::vector<DrawObject*> mDrawObjects;
	sf::Texture mTexture;
	sf::Font mFont;
};

