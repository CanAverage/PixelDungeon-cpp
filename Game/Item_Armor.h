#pragma once
#include "Item.h"
#include "Player.h"
#include "ItemManager.h"
class Inventory;

class Item_Armor : public Item
{
public:
	Item_Armor(int damageReduction, int strengthRequired, std::string name, std::string description,
	           int textureIndex, int spriteRow, int index, ItemManager* manager, Texture* texture, Player* player);
	Item_Armor(Item_Armor* pWeapon, Point2f pos, int index, Inventory* i, int spriteRow);
	~Item_Armor() override;
	void Interact() override;
	int GetIndex() override;
	int GetTextureIndex() override;
	std::string GetName() override;
	std::string GetType() override;
	int GetDefence();
	int GetSpriteRow();
private:
	std::string m_Name{};
	ItemManager* m_pMyManager;
	Player* m_pPlayer;
	Inventory* m_pInventory;
	int m_MyIndex{};
	int m_DamageReduction{};
	int m_StrengthRequired{};
	int m_TextureIndex{};
	Texture* m_Texture{};
	int m_SpriteRow{};
	std::string m_Description;
};
