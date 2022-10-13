#include "stdafx.h"
#include "EnemyManager.h"
#include "TileManager.h"
#include "FxManager.h"
#include "Enemy_Rat.h"
#include "Enemy_Undead.h"
#include "Enemy_Monk.h"
#include "Enemy_Boss.h"
#include "Player.h"
Texture* EnemyManager::m_pRatTexture = nullptr;
Texture* EnemyManager::m_pUndeadTexture = nullptr;
Texture* EnemyManager::m_pMonkTexture = nullptr;
Texture* EnemyManager::m_pKingTexture = nullptr;

EnemyManager::EnemyManager(FxManager* fxManager, TileManager* manager, Player* player, ItemManager* itemManager,
                           bool* hasKingDied)
	: m_pPlayer{player}, m_pMyManager{manager}, m_pFxManager{fxManager}, m_pItemManager{itemManager},
	  m_KingHasDied{hasKingDied}
{
	m_pRatTexture = new Texture{"Resources/rat.png"};
	m_pUndeadTexture = new Texture{"Resources/Undead.png"};
	m_pMonkTexture = new Texture{"Resources/monk.png"};
	m_pKingTexture = new Texture{"Resources/king.png"};
}

EnemyManager::~EnemyManager()
{
	delete m_pRatTexture;
	delete m_pUndeadTexture;
	delete m_pMonkTexture;
	delete m_pKingTexture;
	for (Enemy* element : m_pEnemies)
	{
		if (element != nullptr)
			delete element;
	}
}

void EnemyManager::CreateEnemies()
{
	LoadEnemies();
	//m_Rat = new Enemy_Rat{m_FxManager, this, m_MyManager, m_RatTexture,{ 19 * 32,20 * 32 }, m_Player };
	//m_Undead = new Enemy_Undead{ m_MyManager, m_RatTexture , { 19 * 32,20 * 32 } };
}

void EnemyManager::DrawEnemies() const
{
	for (Enemy* element : m_pEnemies)
	{
		if (element != nullptr)
		{
			element->Draw();
		}
	}
	//m_Undead->Draw();
}

void EnemyManager::UpdateEnemies(float elapsedSec)
{
	for (int i{0}; i < m_pEnemies.size(); ++i)
	{
		if (m_pEnemies[i]->IsDead() && m_pEnemies[i]->getExp() != 0)
		{
			DestroyEnemy(i);
			--i;
		}
		else if (m_pEnemies[i]->IsDead() && m_pEnemies[i]->getExp() == 0)
		{
			(*m_KingHasDied) = true;
		}
		else
		{
			if (m_pEnemies[i] != nullptr)
			{
				if (m_MovementPoints > 0)
				{
					m_pEnemies[i]->IncreaseMovement();
					//m_pKing->IncreaseMovement();
					//m_Undead->IncreaseMovement();
				}
			}
			m_pEnemies[i]->Update(elapsedSec, m_pEnemies[i]->TryToFindPlayer(m_pPlayer));
		}
		//m_pKing->Update(elapsedSec, m_pKing->TryToFindPlayer(m_pPlayer));
	}
	if (m_MovementPoints > 0)
	{
		m_MovementPoints--;
	}
	//m_Undead->Update(elapsedSec, m_Undead->TryToFindPlayer(m_Player));
}

void EnemyManager::AddMovePoint()
{
	m_MovementPoints++;
}

std::vector<Enemy*> EnemyManager::GetEnemies() const
{
	return m_pEnemies;
}

void EnemyManager::DestroyEnemy(int i)
{
	Enemy* temp;
	temp = m_pEnemies.back();
	m_pPlayer->AddExp(m_pEnemies[i]->getExp());
	m_pEnemies.back() = m_pEnemies[i];
	m_pEnemies[i] = temp;

	delete m_pEnemies.back();
	m_pEnemies.pop_back();
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
					m_pEnemies.push_back(new Enemy_Rat{
						m_pFxManager, this, m_pMyManager, m_pRatTexture, temp2f, m_pPlayer, m_pItemManager
					});
				}
				else if (tempi == 1)
				{
					m_pEnemies.push_back(new Enemy_Undead{
						m_pFxManager, this, m_pMyManager, m_pUndeadTexture, temp2f, m_pPlayer, m_pItemManager
					});
				}
				else if (tempi == 2)
				{
					m_pEnemies.push_back(new Enemy_Monk{
						m_pFxManager, this, m_pMyManager, m_pMonkTexture, temp2f, m_pPlayer, m_pItemManager
					});
				}
				else if (tempi == 3)
				{
					m_pEnemies.push_back(new Enemy_Boss{
						m_pFxManager, this, m_pMyManager, m_pKingTexture, temp2f, m_pPlayer, m_pItemManager
					});
				}
			}
		}
	}
	std::cout << "LEVEL LOADED" << '\n';
}
