#include "stdafx.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Inventory_Tile.h"
#include "Item.h"
#include "Player.h"
#include "utils.h"

Inventory::Inventory(ItemManager* itemManager, Player* player) : m_pItemManager{itemManager}, m_pPlayer{player}
{
	pFont = TTF_OpenFont("Resources/m04.ttf", 32);
	pBackFont = TTF_OpenFont("Resources/m04b.ttf", 32);
	m_pItemManager->SetInventoryptr(this);
	m_pInventoryBackground = new Texture{"Resources/Inventory.png"};
	m_pDropButton = new Texture{"Resources/Drop.png"};
	m_pEquipButton = new Texture{"Resources/Equip.png"};
	// Making a grid
	//Don't want the top 2 right tiles, to show what ones are "equiped"
	m_pEquipedTiles.push_back(new Inventory_Tile{
		{m_ItemStartingRect.left, m_ItemStartingRect.bottom, m_ItemStartingRect.width, m_ItemStartingRect.height}
	});
	m_pEquipedTiles.push_back(new Inventory_Tile{
		{m_ItemStartingRect.left + 100, m_ItemStartingRect.bottom, m_ItemStartingRect.width, m_ItemStartingRect.height}
	});
	//Showing the others
	for (int j{1}; j <= 4; j++)
	{
		for (int i{0}; i <= 3; i++)
		{
			m_pTiles.push_back(new Inventory_Tile{
				{
					m_ItemStartingRect.left + (100 * i), m_ItemStartingRect.bottom - (100 * j),
					m_ItemStartingRect.width, m_ItemStartingRect.height
				}
			});
		}
	}
}


Inventory::~Inventory()
{
	delete m_pInventoryBackground;
	delete m_pDropButton;
	delete m_pEquipButton;
	for (Inventory_Tile* element : m_pTiles)
	{
		delete element;
		element = nullptr;
	}
	for (Inventory_Tile* element : m_pEquipedTiles)
	{
		delete element;
		element = nullptr;
	}
	if (m_pItemStats != nullptr)
	{
		delete m_pItemStats;
		delete m_pItemStatsBack;
	}
}


void Inventory::Draw() const
{
	if (m_ShowInventory == true)
	{
		m_pInventoryBackground->Draw(m_InventoryDestRct);
		m_pDropButton->Draw(m_DropButtonDestRct);
		m_pEquipButton->Draw(m_EquipButtonDestRct);

		for (Inventory_Tile* element : m_pTiles)
		{
			element->Draw();
		}
		for (Inventory_Tile* element : m_pEquipedTiles)
		{
			element->Draw();
		}
		if (m_pItemStats != nullptr)
		{
			m_pItemStats->Draw({100, 175, m_pItemStats->GetWidth(), 32});
			m_pItemStatsBack->Draw({100, 175, m_pItemStatsBack->GetWidth(), 32});
		}
	}
}

void Inventory::AddItem(Item* item)
{
	bool emptySlotFound{false};
	for (Inventory_Tile* element : m_pTiles)
	{
		if (element->CheckIfEmpty() == true && emptySlotFound == false)
		{
			element->SetItem(item);
			emptySlotFound = true;
		}
	}
}

void Inventory::ToggleVisibility()
{
	if (m_ShowInventory == true)
		m_ShowInventory = false;
	else
		m_ShowInventory = true;
}


bool Inventory::IsVisible()
{
	return m_ShowInventory;
}


void Inventory::ProcessMouseDownEvent(Point2f pos)
{
	if (utils::IsPointInRect(pos, m_InventoryDestRct) == false)
	{
		m_ShowInventory = false;
	}
	if (utils::IsPointInRect(pos, m_DropButtonDestRct) && m_SelectedTile != nullptr && m_IsSelectedTileEquiped == false)
	{
		m_SelectedTile->DeleteItem();
	}
	if (utils::IsPointInRect(pos, m_EquipButtonDestRct) && m_SelectedTile->CheckIfEmpty() == false
		&& m_SelectedTile->GetItem() != nullptr && m_IsSelectedTileEquiped == false)
	{
		if (m_SelectedTile->GetItem()->GetType() == "WEAPON")
		{
			if (m_pEquipedTiles[1]->GetItem() != nullptr)
			{
				AddItem(m_pEquipedTiles[1]->GetItem());
				m_pEquipedTiles[1]->RemoveItem();
			}
			m_pEquipedTiles[1]->SetItem(m_SelectedTile->GetItem());
			m_SelectedTile->RemoveItem();
			auto temp = static_cast<Item_Weapon*>(m_pEquipedTiles[1]->GetItem());
			m_pPlayer->SetWeaponStats(temp->GetDamage());
		}
		else if (m_SelectedTile->GetItem()->GetType() == "ARMOR")
		{
			if (m_pEquipedTiles[0]->GetItem() != nullptr)
			{
				AddItem(m_pEquipedTiles[0]->GetItem());
				m_pEquipedTiles[0]->RemoveItem();
			}
			m_pEquipedTiles[0]->SetItem(m_SelectedTile->GetItem());
			m_SelectedTile->RemoveItem();
			auto temp = static_cast<Item_Armor*>(m_pEquipedTiles[0]->GetItem());
			m_pPlayer->SetArmorStats(temp->GetDefence());
			m_pPlayer->SetSpriteRow(temp->GetSpriteRow());
		}
	}
	for (Inventory_Tile* element : m_pTiles)
	{
		if (element->CheckIfClicked(pos) == true && element != m_SelectedTile)
		{
			if (m_SelectedTile != nullptr && m_ATileIsSelected == true)
				m_SelectedTile->DeSelect();
			m_SelectedTile = element;
			CreateStatsTexture();
			m_IsSelectedTileEquiped = false;
			m_ATileIsSelected = true;
		}
	}
	for (Inventory_Tile* element : m_pEquipedTiles)
	{
		if (element->CheckIfClicked(pos) == true && element != m_SelectedTile)
		{
			if (m_SelectedTile != nullptr && m_ATileIsSelected == true)
				m_SelectedTile->DeSelect();
			m_SelectedTile = element;
			CreateStatsTexture();
			m_IsSelectedTileEquiped = true;
			m_ATileIsSelected = true;
		}
	}
}

void Inventory::CreateStatsTexture()
{
	if (m_SelectedTile->GetItem() != nullptr)
	{
		if (m_SelectedTile->GetItem()->GetType() == "WEAPON")
		{
			auto temp = static_cast<Item_Weapon*>(m_SelectedTile->GetItem());
			m_pItemStats = new Texture{"ATK " + std::to_string(temp->GetDamage()), pFont, Color4f(1.f, 1.f, 1.f, 1.f)};
			m_pItemStatsBack = new Texture{
				"ATK " + std::to_string(temp->GetDamage()), pBackFont, Color4f(0.f, 0.f, 0.f, 1.f)
			};
		}
		if (m_SelectedTile->GetItem()->GetType() == "ARMOR")
		{
			auto temp = static_cast<Item_Armor*>(m_SelectedTile->GetItem());
			m_pItemStats = new Texture{"DEF " + std::to_string(temp->GetDefence()), pFont, Color4f(1.f, 1.f, 1.f, 1.f)};
			m_pItemStatsBack = new Texture{
				"DEF " + std::to_string(temp->GetDefence()), pBackFont, Color4f(0.f, 0.f, 0.f, 1.f)
			};
		}
	}
}
