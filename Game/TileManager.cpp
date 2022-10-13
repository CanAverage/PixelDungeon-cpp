#pragma once
#include "stdafx.h"
#include "TileManager.h"

Texture* TileManager::m_pTexture = nullptr;

TileManager::TileManager()
{
	m_pTexture = new Texture{"Resources/tiles0.png"};
}


TileManager::~TileManager()
{
	for (Tile* element : m_pWalkableTiles)
	{
		delete element;
		element = nullptr;
	}
	for (Tile* element : m_pNonWalkableTiles)
	{
		delete element;
		element = nullptr;
	}
	delete m_pTexture;
	m_pTexture = nullptr;
}

void TileManager::DrawTiles() const
{
	for (Tile* element : m_pWalkableTiles)
	{
		if (element != nullptr)
		{
			//element->UpdatePosCamera();
			element->Draw();
		}
	}
	for (Tile* element : m_pNonWalkableTiles)
	{
		if (element != nullptr)
		{
			//element->UpdatePosCamera();
			element->Draw();
		}
	}
}

Texture* TileManager::GetTexture() const
{
	return m_pTexture;
}


void TileManager::LoadLevel()
{
	for (Tile* element : m_pWalkableTiles)
	{
		delete element;
	}
	for (Tile* element : m_pNonWalkableTiles)
	{
		delete element;
	}
	m_pWalkableTiles.clear();
	m_pNonWalkableTiles.clear();
	std::ifstream in("output.txt");
	if (in)
	{
		std::string s;
		char delim{' '};
		Point2f temp2f{};
		int tempi{};
		bool tempb;
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
			}
			else if (counter == 3)
			{
				tempb = stoi(s);
				counter = 0;
				if (tempb == true)
				{
					m_pWalkableTiles.push_back(new Tile(static_cast<int>(temp2f.y), static_cast<int>(temp2f.x), tempi,
					                                    m_pTexture, this, tempb));
				}
				else
				{
					m_pNonWalkableTiles.push_back(new Tile(static_cast<int>(temp2f.y), static_cast<int>(temp2f.x),
					                                       tempi, m_pTexture, this, tempb));
				}
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

std::vector<Tile*> TileManager::GetWalkableTiles() const
{
	return m_pWalkableTiles;
}

std::vector<Tile*> TileManager::GetNonWalkableTiles() const
{
	return m_pNonWalkableTiles;
}
