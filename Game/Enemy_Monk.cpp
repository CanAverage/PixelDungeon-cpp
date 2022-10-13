#include "stdafx.h"
#include "Enemy_Monk.h"

Point2i Enemy_Monk::m_SpriteCoordinates = {17, 1};

Enemy_Monk::Enemy_Monk(FxManager* fxManager, EnemyManager* myManager, TileManager* tManager
                       , Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager)
	: Enemy(myManager, fxManager, tManager, myTexture, m_SpriteCoordinates
	        , pos, player, {0, 2, 11, 6, 3, 6, 6, 4}, itemManager, m_Health)
	  , m_pMyManager(myManager), m_pItemManager{itemManager}
{
}


Enemy_Monk::~Enemy_Monk()
{
}


int Enemy_Monk::CalculateDamage()
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

int Enemy_Monk::getExp()
{
	return m_AmountOfExp;
}

void Enemy_Monk::Die()
{
	this->m_CurrentSpriteNumber = 0.f;
	this->m_IsDying = true;
	m_pItemManager->ChanceToSpawnItem(2, this->GetPos());
}
