#include "stdafx.h"
#include "TileManager.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
Texture* TileManager::m_pTexture = nullptr;

TileManager::TileManager()
{
	m_pTexture = new Texture{"Resources/tiles0.png"};
}


TileManager::~TileManager()
{
	for (Tile* element : m_Tiles)
	{
		delete element;
	}
	delete m_pTexture;
}

void TileManager::CreateNewTile(Point2f pos, int currentSprite)
{
	bool isMade{false};
	for (Tile* element : m_Tiles)
	{
		int tempRow = static_cast<int>(pos.y) / 32;
		int tempColumn = static_cast<int>(pos.x) / 32;
		if (element->GetColumn() == tempColumn && element->GetRow() == tempRow)
		{
			element->SetCurrentSpriteNumber(currentSprite);
			isMade = true;
		}
	}
	if (isMade == false)
	{
		m_Tiles.push_back(new Tile(pos, currentSprite, m_pTexture, this));
		m_AmountOfTilesCreated++;
	}
}

void TileManager::DrawTiles() const
{
	for (Tile* element : m_Tiles)
	{
		if (element != nullptr)
		{
			//element->UpdatePosCamera();
			element->Draw();
		}
	}
}

void TileManager::SaveLevel()
{
	int tempTileCounter{0};
	std::vector<Tile*> tempVect;
	std::ofstream output{"output.txt"};
	remove("output.txt");
	for (Tile* element : m_Tiles)
	{
		if (element->GetCurrentSpriteNumber() != 0)
		{
			tempVect.push_back(element);
			tempTileCounter++;
		}
	}
	if (output)
	{
		for (Tile* element : tempVect)
		{
			int x = element->GetCurrentSpriteNumber();
			if (x == Hole || x == Wall || x == LockedDoor ||
				x == Brick || x == WallHole || x == WoodenBarricade ||
				x == GrimeyWall || x == LockedMetalDoor || x == Hole2 ||
				x == Statue || x == StatueWood || x == BookCase ||
				x == Pot || x == FloorAbyss || x == WoodAbyss ||
				x == ShadowWall || x == FloorHole)
			{
				output << element->GetColumn() << " " << element->GetRow() << " " << element->GetCurrentSpriteNumber()
					<< " " << 0 << '\t' << '\n';
			}
			else
			{
				output << element->GetColumn() << " " << element->GetRow() << " " << element->GetCurrentSpriteNumber()
					<< " " << 1 << '\t' << '\n';
			}
		}
	}
	std::cout << "LEVEL SAVED, there were " << tempTileCounter << " tiles" << '\n';
}

Texture* TileManager::GetTexture() const
{
	return m_pTexture;
}


void TileManager::LoadLevel()
{
	for (Tile* element : m_Tiles)
	{
		delete element;
	}
	m_Tiles.clear();
	std::ifstream in("output.txt");
	if (in)
	{
		std::string s;
		char delim{' '};
		Point2f temp2f{};
		int tempi{};
		int counter{0};
		while (in.good())
		{
			in >> s;
			if (counter == 0)
			{
				temp2f.x = stof(s);
				counter++;
			}
			else if (counter == 1)
			{
				temp2f.y = stof(s);
				counter++;
			}
			else if (counter == 2)
			{
				tempi = stoi(s);
				counter++;
				if (tempi < 0) tempi += 64;
				m_Tiles.push_back(new Tile(static_cast<int>(temp2f.y), static_cast<int>(temp2f.x), tempi, m_pTexture,
				                           this));
			}
			else if (counter == 3)
			{
				counter = 0;
			}
		}
	}
	std::cout << "LEVEL LOADED" << '\n';
}


void TileManager::SetWidthOffset(float number)
{
	m_WidthOffset = number;
}

void TileManager::SetHeightOffset(float number)
{
	m_HeightOffset = number;
}

float TileManager::GetWidthOffset() const
{
	return m_WidthOffset;
}

float TileManager::GetHeightOffset() const
{
	return m_HeightOffset;
}
