#pragma once
#include "TileManager.h"
#include "utils.h"
#include "Enemy.h"

class EnemyManager
{
public:
	enum EnemyKind { rat, undead, monk, king };

	EnemyManager();
	~EnemyManager();
	void CreateNewEnemy(Point2f pos, int currentSelectedEnemy);
	void DrawEnemies() const;
	void SaveEnemies();
	void LoadEnemies();
	float GetWidthOffset() const;
	float GetHeightOffset() const;
private:
	int m_AmountOfEnemiesCreated;
	EnemyKind m_CurrentEnemy{};
	static Texture* m_pRatTexture;
	static Texture* m_pUndeadTexture;
	static Texture* m_pMonkTexture;
	static Texture* m_pKingTexture;
	std::vector<Enemy*> m_pEnemies;
	float m_WidthOffset;
	float m_HeightOffset;
};
