#pragma once
#include "Texture.h"
class TileManager;

class Tile
{
public:
	Tile(Point2f pos, int spriteNumber, Texture* sprite, TileManager* manager);
	Tile(int row, int column, int spriteNumber, Texture* sprite, TileManager* manager);
	~Tile();

	void Draw() const;
	int GetColumn() const;
	int GetRow() const;
	int GetCurrentSpriteNumber() const;
	void UpdatePosCamera();
	void SetCurrentSpriteNumber(int number);
private:
	TileManager* m_pMyManager;
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
