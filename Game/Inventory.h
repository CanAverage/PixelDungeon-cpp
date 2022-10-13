#pragma once
#include "Texture.h"
#include <vector>

class Player;
class Item;
class ItemManager;
class Inventory_Tile;

class Inventory
{
public:
	Inventory(ItemManager* itemManager, Player* player);
	~Inventory();
	void Draw() const;
	void AddItem(Item* item);
	void ToggleVisibility();
	bool IsVisible();
	void ProcessMouseDownEvent(Point2f pos);
	void CreateStatsTexture();
private:
	TTF_Font* pFont{};
	TTF_Font* pBackFont{};
	Texture* m_pItemStats{};
	Texture* m_pItemStatsBack{};
	ItemManager* m_pItemManager;
	Texture* m_pInventoryBackground;
	Texture* m_pEquipButton;
	Texture* m_pDropButton;
	Player* m_pPlayer;
	bool m_ShowInventory{false};
	const Rectf m_InventoryDestRct{50, 50, 466, 700};
	const Rectf m_EquipButtonDestRct{100, 100, 150, 50};
	const Rectf m_DropButtonDestRct{318, 100, 150, 50};
	const Rectf m_ItemStartingRect{97, 625, 75, 75};
	const int m_VectorMaxSize{20};
	std::vector<Inventory_Tile*> m_pTiles;
	std::vector<Inventory_Tile*> m_pEquipedTiles;
	bool m_IsSelectedTileEquiped{false};
	bool m_ATileIsSelected{false};
	Inventory_Tile* m_SelectedTile;
};
