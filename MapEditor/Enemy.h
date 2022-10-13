#pragma once
#include "Texture.h"
class EnemyManager;

class Enemy
{
public:
	Enemy(Point2f pos, int currentEnemyType, Texture* texture, EnemyManager* myManager);
	Enemy(int row, int column, int currentEnemyType, Texture* texture, EnemyManager* myManager);
	~Enemy();
	void Draw() const;
	void Enemy::UpdatePosCamera();
	int GetColumn() const;
	int GetRow() const;
	int GetCurrentEnemyType() const;
private:
	int m_CurrentEnemyType{};
	int m_Row{}, m_Column{};
	float m_Height{}, m_Width{};
	Rectf m_DestRect, m_SrcRect;
	Texture* m_pTexture;
	EnemyManager* m_pMyManager;
	Point2f m_Pos;
};
