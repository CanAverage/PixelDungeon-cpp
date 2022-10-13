#pragma once
#include "Item.h"
#include "Player.h"
#include "ItemManager.h"

class Item_Weapon : public Item
{
public:
	Item_Weapon(int speed, int damage, int strengthRequired, std::string name, std::string description,
	            int textureIndex, int index, ItemManager* manager, Texture* texture, Player* player);
	Item_Weapon(Item_Weapon* pWeapon, Point2f pos, int index, Inventory* i);
	~Item_Weapon() override;
	void Interact() override;
	int GetIndex() override;
	int GetTextureIndex() override;
	std::string GetName() override;
	std::string GetType() override;
	int GetDamage();
private:
	std::string m_Name{};
	ItemManager* m_pMyManager;
	Inventory* m_pInventory;
	Player* m_pPlayer;
	int m_MyIndex{};
	int m_Speed{};
	int m_Damage{};
	int m_StrengthRequired{};
	int m_TextureIndex{};
	Texture* m_pTexture{};
	std::string m_Description;
};
