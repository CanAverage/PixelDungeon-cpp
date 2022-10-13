#pragma once
#include "Texture.h"
#include <iostream>

class TileManager;

class Tile
{
public:
	Tile(Point2f pos, int spriteNumber, Texture* sprite, TileManager* manager);
	Tile(int row, int column, int spriteNumber, Texture* sprite, TileManager* manager, bool walkAble);
	~Tile();

	void Draw() const;
	int GetColumn() const;
	int GetRow() const;
	int GetCurrentSpriteNumber() const;
	void UpdatePosCamera();
	void SetCurrentSpriteNumber(int number);
	bool m_WalkAble;
private:
	TileManager* m_pMyManager;
	const int m_TileSize{32};
	int m_CurrentSpriteNumber;
	Texture* m_pSprite;
	int m_Column;
	int m_Row;
	float m_WidthOffset;
	float m_HeightOffset;
	float m_Width;
	float m_Height;
	Rectf m_DestRect;
	Rectf m_srcRect;
};
