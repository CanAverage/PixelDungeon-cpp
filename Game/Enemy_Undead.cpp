#include "stdafx.h"
#include "Enemy_Undead.h"

Point2i Enemy_Undead::m_SpriteCoordinates = {17, 1};

Enemy_Undead::Enemy_Undead(FxManager* fxManager, EnemyManager* myManager, TileManager* tManager,
                           Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager)
	: Enemy(myManager, fxManager, tManager, myTexture, m_SpriteCoordinates, pos,
	        player, {0, 4, 5, 5, 14, 3, 11, 3}, itemManager, m_Health)
	  , m_pMyManager(myManager), m_pItemManager{itemManager}
{
}


Enemy_Undead::~Enemy_Undead()
{
}


int Enemy_Undead::CalculateDamage()
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

int Enemy_Undead::getExp()
{
	return m_AmountOfExp;
}

void Enemy_Undead::Die()
{
	this->m_CurrentSpriteNumber = 0.f;
	this->m_IsDying = true;
	m_pItemManager->ChanceToSpawnItem(1, this->GetPos());
}
