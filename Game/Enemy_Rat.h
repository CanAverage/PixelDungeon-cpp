#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ItemManager.h"

class Enemy_Rat : public Enemy
{
public:
	Enemy_Rat(FxManager* fxManager, EnemyManager* myManager, TileManager* tManager,
	          Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager);
	~Enemy_Rat() override;
	int getExp() override;
	void Die() override;
private:
	static const int m_Health{15};
	static Point2i m_SpriteCoordinates;
	EnemyManager* m_pMyManager;
	ItemManager* m_pItemManager;
	Player* m_Player;
	int CalculateDamage() override;
	FxManager* m_pFxManager;
	Rectf m_SrcRect, m_DestRect;
	int m_BaseMinDamage{1};
	int m_BaseMaxDamage{3};
	float m_CritChance{0.10f};
	int m_CritMultiplier{2};
	int m_AmountOfExp{2};
};
