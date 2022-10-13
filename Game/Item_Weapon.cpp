#include "stdafx.h"
#include "Item_Weapon.h"


Item_Weapon::Item_Weapon(int speed, int damage, int strengthRequired, std::string name, std::string description,
                         int textureIndex, int index, ItemManager* manager, Texture* texture, Player* player) :
	Item{textureIndex, index, texture, player}, m_Name{name}, m_pMyManager{manager}, m_pPlayer{player},
	m_MyIndex{index},
	m_Speed{speed}, m_Damage{damage}, m_StrengthRequired{strengthRequired}, m_TextureIndex{textureIndex},
	m_pTexture{texture}
	, m_Description{description}
{
}

Item_Weapon::Item_Weapon(Item_Weapon* pWeapon, Point2f pos, int index, Inventory* i) : Item{
		pWeapon->m_TextureIndex, index, pWeapon->m_pTexture, pos, pWeapon->m_pPlayer
	}, m_Name{pWeapon->m_Name}, m_pMyManager{pWeapon->m_pMyManager}
	, m_pInventory{i}, m_pPlayer{pWeapon->m_pPlayer}, m_MyIndex{pWeapon->m_MyIndex}, m_Speed{pWeapon->m_Speed},
	m_Damage{pWeapon->m_Damage}, m_StrengthRequired{pWeapon->m_StrengthRequired},
	m_Description{pWeapon->m_Description}
{
}

Item_Weapon::~Item_Weapon()
{
}

void Item_Weapon::Interact()
{
	m_pInventory->AddItem(this);
	m_pMyManager->RemoveItem(m_MyIndex);
	//Put in inventory
}

int Item_Weapon::GetIndex()
{
	return m_MyIndex;
}

int Item_Weapon::GetTextureIndex()
{
	return m_TextureIndex;
}

std::string Item_Weapon::GetName()
{
	return m_Name;
}

std::string Item_Weapon::GetType()
{
	return "WEAPON";
}

int Item_Weapon::GetDamage()
{
	return m_Damage;
}
