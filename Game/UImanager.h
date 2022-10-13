#pragma once
#include "UI_PlayerStats.h"
#include "Inventory.h"
#include "Menu.h"
class Player;

class UImanager
{
public:
	UImanager(Player* player, Inventory* inventory, Window window, bool* menu);
	~UImanager();
	void Draw() const;
	void Update();
	void ProcessMouseDownEvent(Point2f pos);
	UI_PlayerStats* GetPlayerStatsReference();
private:
	UI_PlayerStats* m_pPlayerStats;
};
