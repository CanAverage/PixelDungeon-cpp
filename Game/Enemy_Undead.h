#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ItemManager.h"

class Enemy_Undead : public Enemy
{
public:
	Enemy_Undead(FxManager* fxManager, EnemyManager* MyManager, TileManager* tManager,
	             Texture* myTexture, Point2f pos, Player* player, ItemManager* itemManager);
	~Enemy_Undead() override;
	int getExp() override;
	void Die() override;
private:
	static const int m_Health{20};
	static Point2i m_SpriteCoordinates;
	EnemyManager* m_pMyManager;
	ItemManager* m_pItemManager;
	Player* m_pPlayer;
	Texture* m_pTexture;
	int CalculateDamage() override;
	FxManager* m_pFxManager;
	Rectf m_SrcRect, m_DestRect;
	int m_BaseMinDamage{2};
	int m_BaseMaxDamage{5};
	float m_CritChance{0.10f};
	int m_CritMultiplier{2};
	int m_AmountOfExp{4};

	Point2f m_Pos{};
	MovementState m_Move;
	int m_TileSize{32};
};
