#include "stdafx.h"
#include "Enemy_Rat.h"

Point2i Enemy_Rat::m_SpriteCoordinates = {15, 1};

Enemy_Rat::Enemy_Rat(FxManager* fxManager, EnemyManager* myManager, TileManager* tManager,
                     Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager)
	: Enemy(myManager, fxManager, tManager, myTexture, m_SpriteCoordinates, pos, player,
	        {0, 2, 5, 6, 2, 2, 11, 4}, itemManager, m_Health)
	  , m_pMyManager(myManager), m_pItemManager{itemManager}, m_pFxManager(fxManager)
{
}


Enemy_Rat::~Enemy_Rat()
{
}


int Enemy_Rat::CalculateDamage()
{
	int damage;
	damage = (rand() % (m_BaseMaxDamage - m_BaseMinDamage)) + m_BaseMinDamage;
	float critTry;
	critTry = (rand() % 10) / 10.f;
	if (critTry <= m_CritChance)
	{
		damage *= 2;
	}
	//std::cout << damage;
	return damage;
}

int Enemy_Rat::getExp()
{
	return m_AmountOfExp;
}

void Enemy_Rat::Die()
{
	this->m_CurrentSpriteNumber = 0.f;
	this->m_IsDying = true;
	m_pItemManager->ChanceToSpawnItem(0, this->GetPos());
}
