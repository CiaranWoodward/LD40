#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "Cursor.h"

#include "Farm.h"
#include "Bait.h"
#include "Wall.h"
#include "Turret.h"


Cursor::Cursor(GameManager &aGameManager, uint32_t &aGrainCounter, uint32_t &aCorpseCounter) :
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, INT32_MAX - 10),
	mCurItem(kItemClear),
	mGrainCounter(aGrainCounter),
	mCorpseCounter(aCorpseCounter)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(54, 94, 54, 41));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mSprite.setColor(sf::Color(255, 255, 255, 0));
}


Cursor::~Cursor()
{
}

bool Cursor::HandleMouseEvent(sf::Event & aMouseEvent)
{
	if (aMouseEvent.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i gCoords(aMouseEvent.mouseButton.x, aMouseEvent.mouseButton.y);
		sf::Vector2f hudCoords = mGameManager.GetWindowManager().GetWindow().mapPixelToCoords(gCoords, mGameManager.GetWindowManager().GetWindow().getDefaultView());
		//Hacky HUD interaction
		if (hudCoords.x > 1160 && hudCoords.y > 390)
		{
			int y = static_cast<int>(hudCoords.y) - 390;
			int select = y / 82;

			if (select == 0)
				mCurItem = kItemTurret;
			else if (select == 1)
				mCurItem = kItemBait;
			else if (select == 2)
				mCurItem = kItemFarm;
			else if (select == 3)
				mCurItem = kItemWall;
			else
				mCurItem = kItemClear;

			mSprite.setColor(sf::Color(255, 255, 255, 255));
			//Set Sprite
			switch (mCurItem)
			{
			case kItemClear:
				mSprite.setColor(sf::Color(255, 255, 255, 0));
				break;

			case kItemTurret:
				mSprite.setTextureRect(sf::IntRect(444, 115, 31, 46));
				break;

			case kItemBait:
				mSprite.setTextureRect(sf::IntRect(378, 108, 54, 27));
				break;

			case kItemFarm:
				mSprite.setTextureRect(sf::IntRect(162, 102, 54, 33));
				break;

			case kItemWall:
				mSprite.setTextureRect(sf::IntRect(54, 94, 54, 41));
				break;
			}

			mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
		}
		else
		{
			sf::Vector2f worldPos = mGameManager.GetWindowManager().GetWindow().mapPixelToCoords(gCoords);

			int32_t div = MapManager::kTileWidth + (2 * MapManager::kTileHeight);
			int32_t Sy = static_cast<int32_t>(worldPos.y);
			int32_t Sx = static_cast<int32_t>(worldPos.x);

			sf::Vector2<uint32_t> tileCoords(((2 * Sy) + Sx) / div, ((2 * Sy) - Sx) / div);
			tileCoords += {1, 1};

			if (mGameManager.GetMapManager().GetTile(tileCoords).GetTileObject() == NULL)
			{
				//Tile Free
				if (mGrainCounter >= GetGrainCost(mCurItem) && mCorpseCounter >= GetCorpseCost(mCurItem))
				{
					mGrainCounter -= GetGrainCost(mCurItem);
					mCorpseCounter -= GetCorpseCost(mCurItem);

					switch (mCurItem)
					{
					case kItemClear:
						break;
					case kItemWall:
						new Wall(mGameManager, tileCoords);
						break;
					case kItemFarm:
						new Farm(mGameManager, tileCoords, mGrainCounter);
						break;
					case kItemBait:
						new Bait(mGameManager, tileCoords);
						break;
					case kItemTurret:
						new Turret(mGameManager, tileCoords, mGrainCounter);
						break;
					}
				}
				else
				{
					//Can't afford
				}
			}
			else
			{
				//Tile taken
			}
		}
	}
	else if (aMouseEvent.mouseButton.button == sf::Mouse::Right)
	{
		mCurItem = kItemClear;
		mSprite.setColor(sf::Color(255, 255, 255, 0));
	}

	return true;
}

bool Cursor::Update()
{
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(mGameManager.GetWindowManager().GetWindow());
	// convert it to world coordinates
	sf::Vector2f worldPos = mGameManager.GetWindowManager().GetWindow().mapPixelToCoords(pixelPos);

	int32_t div = MapManager::kTileWidth + (2 * MapManager::kTileHeight);
	int32_t Sy = static_cast<int32_t>(worldPos.y);
	int32_t Sx = static_cast<int32_t>(worldPos.x);

	sf::Vector2<uint32_t> tileCoords(((2 * Sy) + Sx) / div, ((2 * Sy) - Sx) / div);
	tileCoords += {1, 1};

	if (mCurItem == kItemClear) return true;

	if(mGameManager.GetMapManager().GetTile(tileCoords).GetTileObject())
		mSprite.setColor(sf::Color(255, 20, 20, 128));
	else
		mSprite.setColor(sf::Color(255, 255, 255, 128));

	mSprite.setPosition(MapManager::GetTileDrawOrigin(tileCoords));
	mDrawObject.SetDrawLevel(mSprite.getPosition().y + 1);

	return true;
}