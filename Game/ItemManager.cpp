#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"
#include "Item_Bubble.h"
#include "SoundManager.h"
#include <iostream>
#include "Item_Weapon.h"
#include "Item_Armor.h"
#include <algorithm>

ItemManager::ItemManager(Player* player, SoundManager* soundManager) : m_pSoundManager(soundManager), m_pPlayer(player)
{
	m_pItemTextures = new Texture{"Resources/items.png"};
	LoadWeapons();
	LoadArmor();
}


ItemManager::~ItemManager()

{
	for (Item_Weapon* element : m_pWeaponTemplates)
	{
		delete element;
		element = nullptr;
	}
	for (Item_Armor* element : m_pArmorTemplates)
	{
		delete element;
		element = nullptr;
	}
	for (Item* element : m_pItems)
	{
		delete element;
		element = nullptr;
	}
	delete m_pItemTextures;
}

void ItemManager::Draw() const
{
	for (Item* Element : m_pItems)
	{
		Element->Draw();
	}
}

void ItemManager::Update(float elapsedSec)
{
	for (Item* Element : m_pItems)
	{
		Element->Update(elapsedSec);
	}
}

void ItemManager::SpawnItem(int textureIndex, bool equipment, Point2f pos)
{
	if (equipment == true)
	{
		for (Item_Weapon* element : m_pWeaponTemplates)
		{
			if (element->GetTextureIndex() == textureIndex)
			{
				m_pItems.push_back(new Item_Weapon{element, pos, m_IndexCounter, m_pInventory});
			}
		}
		for (Item_Armor* element : m_pArmorTemplates)
		{
			if (element->GetTextureIndex() == textureIndex)
			{
				m_pItems.push_back(new Item_Armor{element, pos, m_IndexCounter, m_pInventory, element->GetSpriteRow()});
			}
		}
	}
	else
	{
		m_pItems.push_back(new Item{textureIndex, m_IndexCounter, m_pItemTextures, pos, m_pPlayer});
	}
	m_IndexCounter++;
}

void ItemManager::ChanceToSpawnItem(int Rarity, Point2f pos)
{
	int tempbrand{static_cast<int>(rand() % m_ChanceToSpawnItem)};
	int tempirand{static_cast<int>(rand() % 100)};
	if (tempirand > 100 - m_ChanceForTier3Item) { Rarity += 2; }
	if (tempirand > 100 - m_ChanceForTier2Item) { Rarity += 1; }
	switch (tempbrand)
	{
	case 0:
		SpawnItem(m_pArmorTemplates[Rarity]->GetTextureIndex(), true, pos);
		break;
	case 1:
		SpawnItem(m_pWeaponTemplates[Rarity]->GetTextureIndex(), true, pos);
		break;
	}
}

void ItemManager::SpawnBubble(Point2f pos)
{
	int temp = (rand() % 100) + 1;
	if (temp <= m_ChanceToDropBubble)
	{
		m_pItems.push_back(new Item_Bubble{Bubble, m_IndexCounter, m_pItemTextures, pos, this, m_pPlayer});
		if (m_pSoundManager != nullptr)
		{
			m_pSoundManager->PlayItemSpawnSoundEffect();
		}
		m_IndexCounter++;
	}
}

void ItemManager::RemoveItem(int index)
{
	for (Item* Element : m_pItems)
	{
		if (Element->GetIndex() == index)
		{
			Item* temp = m_pItems.back();
			m_pItems.back() = Element;
			Element = temp;
			m_pItems.pop_back();
		}
	}
}

void ItemManager::DeleteItem(int index)
{
	for (Item* Element : m_pItems)
	{
		if (Element->GetIndex() == index)
		{
			Item* temp = m_pItems.back();
			m_pItems.back() = Element;
			Element = temp;
			delete m_pItems.back();
			m_pItems.pop_back();
		}
	}
}

void ItemManager::LoadWeapons()
{
	std::ifstream in("weapons.txt");
	if (in)
	{
		int speed{};
		int damage{};
		int strengthRequired{};
		char delim{'_'};
		std::string s;
		std::string name;
		std::string description;
		int textureIndex{};
		int counter{0};
		while (in.good())
		{
			in >> s;
			if (counter == 0)
			{
				speed = stoi(s);
				counter++;
			}
			else if (counter == 1)
			{
				damage = stoi(s);
				counter++;
			}
			else if (counter == 2)
			{
				strengthRequired = stoi(s);
				counter++;
			}
			else if (counter == 3)
			{
				name = s;
				counter++;
			}
			else if (counter == 4)
			{
				description = s;
				std::replace(description.begin(), description.end(), '_', ' ');
				counter++;
			}
			else if (counter == 5)
			{
				textureIndex = stoi(s);
				m_pWeaponTemplates.push_back(new Item_Weapon{
					speed, damage, strengthRequired, name, description, textureIndex, m_IndexCounter, this,
					m_pItemTextures, m_pPlayer
				});
				counter = 0;
			}
		}
	}
	std::cout << "LEVEL LOADED" << '\n';
}

void ItemManager::LoadArmor()
{
	std::ifstream in("armor.txt");
	if (in)
	{
		int damageReduction{};
		int strengthRequired{};
		char delim{'_'};
		std::string s;
		std::string name;
		std::string description;
		int textureIndex{};
		int spriteRow{};
		int counter{0};
		while (in.good())
		{
			in >> s;
			if (counter == 0)
			{
				damageReduction = stoi(s);
				counter++;
			}
			else if (counter == 1)
			{
				strengthRequired = stoi(s);
				counter++;
			}
			else if (counter == 2)
			{
				name = s;
				counter++;
			}
			else if (counter == 3)
			{
				description = s;
				std::replace(description.begin(), description.end(), '_', ' ');
				counter++;
			}
			else if (counter == 4)
			{
				textureIndex = stoi(s);
				counter++;
			}
			else if (counter == 5)
			{
				spriteRow = stoi(s);
				m_pArmorTemplates.push_back(new Item_Armor{
					damageReduction, strengthRequired, name, description, textureIndex, spriteRow, m_IndexCounter, this,
					m_pItemTextures, m_pPlayer
				});
				counter = 0;
			}
		}
	}
	std::cout << "LEVEL LOADED" << '\n';
}

Item* ItemManager::GetItem(std::string name)
{
	for (Item_Armor* element : m_pArmorTemplates)
	{
		if (name == element->GetName())
		{
			return element;
		}
	}
	for (Item_Weapon* element : m_pWeaponTemplates)
	{
		if (name == element->GetName())
		{
			return element;
		}
	}
	return nullptr;
	std::cout << "Item not found, Check naming" << std::endl;
}

void ItemManager::SetInventoryptr(Inventory* i)
{
	m_pInventory = i;
}
