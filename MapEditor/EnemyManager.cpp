#include "stdafx.h"
#include "EnemyManager.h"
#include <fstream>
#include <iostream>
Texture* EnemyManager::m_pRatTexture = nullptr;
Texture* EnemyManager::m_pUndeadTexture = nullptr;
Texture* EnemyManager::m_pMonkTexture = nullptr;
Texture* EnemyManager::m_pKingTexture = nullptr;

EnemyManager::EnemyManager()
{
	m_pUndeadTexture = new Texture("Resources/undeadPrevieuw.png");
	m_pRatTexture = new Texture("Resources/ratPrevieuw.png");
	m_pMonkTexture = new Texture("Resources/monkPrevieuw.png");
	m_pKingTexture = new Texture("Resources/kingPrevieuw.png");
}

EnemyManager::~EnemyManager()
{
	delete m_pUndeadTexture;
	delete m_pRatTexture;
	delete m_pMonkTexture;
	delete m_pKingTexture;
	for (Enemy* element : m_pEnemies)
	{
		delete element;
	}
}


void EnemyManager::CreateNewEnemy(Point2f pos, int currentSelectedEnemy)
{
	bool isMade{false};
	for (Enemy* element : m_pEnemies)
	{
		int tempRow = static_cast<int>(pos.y) / 32;
		int tempColumn = static_cast<int>(pos.x) / 32;
		if (element->GetColumn() == tempColumn && element->GetRow() == tempRow)
		{
			isMade = true;
		}
	}
	if (isMade == false)
	{
		switch (currentSelectedEnemy)
		{
		case rat:
			m_pEnemies.push_back(new Enemy(pos, currentSelectedEnemy, m_pRatTexture, this));
			break;
		case undead:
			m_pEnemies.push_back(new Enemy(pos, currentSelectedEnemy, m_pUndeadTexture, this));
			break;
		case monk:
			m_pEnemies.push_back(new Enemy(pos, currentSelectedEnemy, m_pMonkTexture, this));
			break;
		case king:
			m_pEnemies.push_back(new Enemy(pos, currentSelectedEnemy, m_pKingTexture, this));
			break;
		}

		m_AmountOfEnemiesCreated++;
	}
}

void EnemyManager::DrawEnemies() const
{
	for (Enemy* element : m_pEnemies)
	{
		if (element != nullptr)
		{
			//element->UpdatePosCamera();
			element->Draw();
		}
	}
}

void EnemyManager::SaveEnemies()
{
	int tempTileCounter{0};
	std::vector<Enemy*> tempVect;
	std::ofstream output{"enemies.txt"};
	remove("enemies.txt");
	for (Enemy* element : m_pEnemies)
	{
		tempVect.push_back(element);
		tempTileCounter++;
	}
	if (output)
	{
		for (Enemy* element : tempVect)
		{
			output << element->GetColumn() * 32 << " " << element->GetRow() * 32 << " " << element->
				GetCurrentEnemyType() << '\t' << '\n';
		}
	}
	std::cout << "LEVEL SAVED, there were " << tempTileCounter << " tiles" << '\n';
}

void EnemyManager::LoadEnemies()
{
	for (Enemy* element : m_pEnemies)
	{
		delete element;
	}
	m_pEnemies.clear();
	std::ifstream in("enemies.txt");
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
				counter = 0;
				if (tempi == 0)
				{
					m_pEnemies.push_back(new Enemy(temp2f, tempi, m_pRatTexture, this));
				}
				else if (tempi == 1)
				{
					m_pEnemies.push_back(new Enemy(temp2f, tempi, m_pUndeadTexture, this));
				}
				else if (tempi == 2)
				{
					m_pEnemies.push_back(new Enemy(temp2f, tempi, m_pMonkTexture, this));
				}
			}
		}
	}
	std::cout << "LEVEL LOADED" << '\n';
}

float EnemyManager::GetWidthOffset() const
{
	return m_WidthOffset;
}

float EnemyManager::GetHeightOffset() const
{
	return m_HeightOffset;
}
