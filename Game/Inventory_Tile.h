#pragma once
#include "Item.h"
#include "Item_Armor.h"
#include "Item_Weapon.h"

class Inventory_Tile
{
public:
	Inventory_Tile(Rectf dstRect);
	~Inventory_Tile();
	bool CheckIfEmpty();
	void Draw() const;
	void SetItem(Item* item);
	Item* GetItem();
	void RemoveItem();
	void DeleteItem();
	bool CheckIfClicked(Point2f pos);
	void DeSelect();
private:
	bool m_IsEmpty{true};
	bool m_IsSelected{false};
	Item* m_pItem;
	Item_Weapon* m_pWeapon;
	Item* m_pArmor;
	Rectf m_DestRect;
};
