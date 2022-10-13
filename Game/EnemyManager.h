#pragma once
#include "TileManager.h"
#include "FxManager.h"
#include "utils.h"
class Player;

class Enemy_Rat;
class Enemy_Undead;
class Enemy_Monk;
class Enemy_Boss;
class Enemy;
class ItemManager;

class EnemyManager
{
public:
	EnemyManager(FxManager* fxManager, TileManager* manager, Player* player, ItemManager* itemManager,
	             bool* hasKingDied);
	~EnemyManager();
	void CreateEnemies();
	void DrawEnemies() const;
	void UpdateEnemies(float elapsedSec);
	void AddMovePoint();
	std::vector<Enemy*> GetEnemies() const;
	void DestroyEnemy(int i);
private:
	std::vector<Enemy*> m_pEnemies;
	Enemy_Undead* m_pUndead;
	Player* m_pPlayer;
	TileManager* m_pMyManager;
	FxManager* m_pFxManager;
	ItemManager* m_pItemManager;
	static Texture* m_pRatTexture;
	static Texture* m_pUndeadTexture;
	static Texture* m_pMonkTexture;
	static Texture* m_pKingTexture;
	void LoadEnemies();
	int m_TileSize{32};
	int m_MovementPoints;
	float m_DifficultyLevel;
	int m_AmountOfEnemies;
	int m_BaseHealth;
	bool* m_KingHasDied;
};
