#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ItemManager.h"

class Enemy_Boss : public Enemy
{
public:
	Enemy_Boss(FxManager* fxManager, EnemyManager* MyManager, TileManager* tManager
	           , Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager);
	~Enemy_Boss() override;
	int getExp() override;
	void Die() override;
	bool IsBoss() override;
private:
	static const int m_Health{40};
	static Point2i m_SpriteCoordinates;
	EnemyManager* m_pMyManager;
	ItemManager* m_pItemManager;
	Player* m_pPlayer;
	Texture* m_pTexture;
	int CalculateDamage() override;
	FxManager* m_pFxManager;
	int m_BaseMinDamage{4};
	int m_BaseMaxDamage{6};
	float m_CritChance{0.10f};
	int m_CritMultiplier{2};
	int m_AmountOfExp{8};
};
