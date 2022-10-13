#pragma once
#include "Texture.h"
#include <vector>
#include "Tile.h"
#include <fstream>
#include <iostream>

class TileManager
{
public:
	enum Sprites
	{
		Empty,
		Ground,
		StompedGrass,
		Hole,
		Wall,
		ClosedDoor,
		OpenDoor,
		StairsUp,
		StairsDown,
		BurnedGround,
		LockedDoor,
		Brick,
		WallHole,
		WoodenBarricade,
		WoodenFloor,
		Grass,
		GrimeyWall,
		GreenTrap,
		Floor2,
		OrangeTrap,
		Floor3,
		YellowTrap,
		Floor4,
		EmptryTrap,
		GrimeyFloor,
		LockedMetalDoor,
		OpenMetalDoor,
		PurpleTrap,
		Floor5,
		Sign,
		RedTrap,
		Floor6,
		BlueTrap,
		Floor7,
		Hole2,
		Statue,
		StatueWood,
		ExplosionTrap,
		Floor8,
		LightBlueTrap,
		Floor9,
		BookCase,
		Pot,
		FloorAbyss,
		WoodAbyss,
		ShadowWall,
		FloorHole,
		Floor10,
		WaterFloor1,
		WaterFloor2,
		WaterFloor3,
		WaterFloor4,
		WaterFloor5,
		WaterFloor6,
		WaterFloor7,
		WaterFloor8,
		WaterFloor9,
		WaterFloor10,
		WaterFloor11,
		WaterFloor12,
		WaterFloor13,
		WaterFloor14,
		WaterFloor15,
		WaterFloor16,
		Empty2
	};

	TileManager();
	~TileManager();
	void DrawTiles() const;
	void LoadLevel();
	Texture* GetTexture() const;
	void SetWidthOffset(float number);
	void SetHeightOffset(float number);
	float GetWidthOffset() const;
	float GetHeightOffset() const;
	std::vector<Tile*> GetWalkableTiles() const;
	std::vector<Tile*> GetNonWalkableTiles() const;
private:
	float m_WidthOffset;
	float m_HeightOffset;
	int m_AmountOfTilesCreated;
	static Texture* m_pTexture;
	std::vector<Tile*> m_pWalkableTiles;
	std::vector<Tile*> m_pNonWalkableTiles;
};
