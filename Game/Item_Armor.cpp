#include "stdafx.h"
#include "Item_Armor.h"


Item_Armor::Item_Armor(int damageReduction, int strengthRequired, std::string name, std::string description,
                       int textureIndex, int spriteRow, int index, ItemManager* manager, Texture* texture,
                       Player* player) :
	Item{textureIndex, index, texture, player}, m_Name{name}, m_pMyManager{manager}, m_pPlayer{player},
	m_MyIndex{index},
	m_DamageReduction{damageReduction}, m_StrengthRequired{strengthRequired}, m_TextureIndex{textureIndex},
	m_Texture{texture}
	, m_SpriteRow{spriteRow}, m_Description{description}
{
}

Item_Armor::Item_Armor(Item_Armor* pArmor, Point2f pos, int index, Inventory* i, int spriteRow) : Item{
		pArmor->m_TextureIndex, index, pArmor->m_Texture, pos, pArmor->m_pPlayer
	}, m_Name{pArmor->m_Name}, m_pMyManager{pArmor->m_pMyManager}
	, m_pPlayer{pArmor->m_pPlayer}, m_pInventory{i}, m_MyIndex{pArmor->m_MyIndex},
	m_DamageReduction{pArmor->m_DamageReduction}, m_StrengthRequired{pArmor->m_StrengthRequired},
	m_SpriteRow{spriteRow},
	m_Description{pArmor->m_Description}
{
}

Item_Armor::~Item_Armor()
{
}

void Item_Armor::Interact()
{
	m_pInventory->AddItem(this);
	m_pMyManager->RemoveItem(m_MyIndex);
	//Put in inventory
}

int Item_Armor::GetIndex()
{
	return m_MyIndex;
}

int Item_Armor::GetTextureIndex()
{
	return m_TextureIndex;
}

std::string Item_Armor::GetName()
{
	return m_Name;
}

std::string Item_Armor::GetType()
{
	return "ARMOR";
}

int Item_Armor::GetDefence()
{
	return m_DamageReduction;
}

int Item_Armor::GetSpriteRow()
{
	return m_SpriteRow;
}
