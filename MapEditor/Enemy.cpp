#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

Enemy::Enemy(Point2f pos, int currentEnemyType, Texture* texture, EnemyManager* myManager):
	m_CurrentEnemyType(currentEnemyType), m_pTexture(texture), m_pMyManager(myManager), m_Pos(pos)
{
	m_Row = static_cast<int>(pos.y) / 32;
	m_Column = static_cast<int>(pos.x) / 32;
	m_Height = m_pTexture->GetHeight();
	m_Width = m_pTexture->GetWidth();
	m_DestRect = {static_cast<float>(m_Column * 32), static_cast<float>(m_Row * 32), m_Width * 2, m_Height * 2};
}

Enemy::Enemy(int row, int column, int currentEnemyType, Texture* texture, EnemyManager* myManager):
	m_CurrentEnemyType(currentEnemyType), m_Row(row), m_Column(column), m_pTexture(texture), m_pMyManager(myManager)
{
	m_Pos.x = row * 32;
	m_Pos.y = column * 32;
	m_Height = m_pTexture->GetHeight();
	m_Width = m_pTexture->GetWidth();
	m_DestRect = {static_cast<float>(m_Column * 32), static_cast<float>(m_Row * 32), m_Width * 2, m_Height * 2};
}

Enemy::~Enemy()
{
}

int Enemy::GetColumn() const
{
	return m_Column;
}

int Enemy::GetRow() const
{
	return m_Row;
}

void Enemy::Draw() const
{
	Rectf srcRect{0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight()};
	m_pTexture->Draw(m_DestRect, srcRect);
}

void Enemy::UpdatePosCamera()
{
	m_DestRect.bottom = static_cast<float>(m_Column * 32);
	m_DestRect.left = static_cast<float>(m_Row * 32);
	m_DestRect.bottom += m_pMyManager->GetHeightOffset();
	m_DestRect.left += m_pMyManager->GetWidthOffset();
}

int Enemy::GetCurrentEnemyType() const
{
	return m_CurrentEnemyType;
}
