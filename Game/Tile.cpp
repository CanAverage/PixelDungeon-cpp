#pragma once
#include "stdafx.h"
#include "Tile.h"
#include "TileManager.h"

Tile::Tile(Point2f pos, int spriteNumber, Texture* sprite, TileManager* manager) : m_pMyManager{manager}
	, m_CurrentSpriteNumber{spriteNumber}, m_pSprite{sprite}
{
	m_Row = static_cast<int>(pos.y) / m_TileSize;
	m_Column = static_cast<int>(pos.x) / m_TileSize;
	m_Height = m_pSprite->GetHeight() / 4;
	m_Width = m_pSprite->GetWidth() / 16;
	m_DestRect = {
		static_cast<float>(m_Column * m_TileSize), static_cast<float>(m_Row * m_TileSize), m_Width * 2, m_Height * 2
	};
}

Tile::Tile(int row, int column, int spriteNumber, Texture* sprite, TileManager* manager, bool walkAble) :
	m_WalkAble(walkAble)
	, m_pMyManager{manager}, m_CurrentSpriteNumber{spriteNumber}, m_pSprite{sprite}, m_Column{column}, m_Row{row}
{
	m_Height = m_pSprite->GetHeight() / 4;
	m_Width = m_pSprite->GetWidth() / 16;
	m_DestRect = {
		static_cast<float>(m_Column * m_TileSize), static_cast<float>(m_Row * m_TileSize), m_Width * 2, m_Height * 2
	};
}

Tile::~Tile()
{
}

void Tile::Draw() const
{
	Rectf srcRect{
		m_Width * m_CurrentSpriteNumber, m_Height + (m_Height * static_cast<int>(m_CurrentSpriteNumber / 16)), m_Width,
		m_Height
	};
	m_pSprite->Draw(m_DestRect, srcRect);
}

int Tile::GetColumn() const
{
	return m_Column;
}

int Tile::GetRow() const
{
	return m_Row;
}

int Tile::GetCurrentSpriteNumber() const
{
	return m_CurrentSpriteNumber;
}

void Tile::SetCurrentSpriteNumber(int number)
{
	m_CurrentSpriteNumber = number;
}

void Tile::UpdatePosCamera()
{
	m_DestRect.bottom = static_cast<float>(m_Column * m_TileSize);
	m_DestRect.left = static_cast<float>(m_Row * m_TileSize);
	m_DestRect.bottom += m_pMyManager->GetHeightOffset();
	m_DestRect.left += m_pMyManager->GetWidthOffset();
}
