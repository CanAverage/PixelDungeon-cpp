#pragma once

#include "Texture.h"
#include "Inventory.h"
#include "Menu.h"
class Player;

class UI_PlayerStats
{
public:
	UI_PlayerStats(Player* player, Inventory* inventory, Window window, bool* menu);
	~UI_PlayerStats();
	void Draw() const;
	void Update();
	void SetHealth(float health);
	void SetExp(float exp);
	void SetLevel(int level);
	void ProcessMouseDownEvent(Point2f pos);
private:
	Player* m_pPlayer;
	Texture* m_pStatsTexture;
	Rectf m_pStatsRect{};
	Texture* m_pHealthTexture;
	Rectf m_pHealthRect{};
	Texture* m_pExpTexture;
	Rectf m_pExpRect{};
	Texture* m_pLevelTexture;
	Rectf m_pLevelRect{};
	Texture* m_pInventoryTexture;
	Rectf m_pInventoryRect{};
	const Rectf m_MenuRect{480, 735, 70, 65};
	Inventory* m_pInventory;
	float m_Health{1};
	float m_Exp{0};
	int m_Level{1};
	TTF_Font* pFont{};
	bool* m_ShowMenu{};
};
