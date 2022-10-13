#include "stdafx.h"
#include "Enemy_Boss.h"

Point2i Enemy_Boss::m_SpriteCoordinates = {16, 1};

Enemy_Boss::Enemy_Boss(FxManager* fxManager, EnemyManager* myManager, TileManager* tManager
                       , Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager)
	: Enemy(myManager, fxManager, tManager, myTexture, m_SpriteCoordinates
	        , pos, player, {0, 2, 2, 7, 9, 3, 12, 4}, itemManager, m_Health),
	  m_pMyManager(myManager), m_pItemManager{itemManager}
{
}


Enemy_Boss::~Enemy_Boss()
{
}


int Enemy_Boss::CalculateDamage()
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

int Enemy_Boss::getExp()
{
	return 0;
}

void Enemy_Boss::Die()
{
	this->m_CurrentSpriteNumber = 0.f;
	this->m_IsDying = true;
}

bool Enemy_Boss::IsBoss()
{
	return true;
}
