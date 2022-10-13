#include "stdafx.h"
#include "Inventory_Tile.h"


Inventory_Tile::Inventory_Tile(Rectf dstRect) : m_DestRect{dstRect}
{
}

Inventory_Tile::~Inventory_Tile()
{
}


void Inventory_Tile::Draw() const
{
	if (m_IsSelected == true)
		glColor3f(0.30f, 0.34f, 0.32f);
	else
		glColor3f(0.26f, 0.30f, 0.28f);
	utils::FillRect(m_DestRect);
	if (m_IsEmpty == false && m_pItem != nullptr)
	{
		m_pItem->Draw(m_DestRect);
	}
}

bool Inventory_Tile::CheckIfEmpty()
{
	return m_IsEmpty;
}

void Inventory_Tile::SetItem(Item* item)
{
	m_pItem = item;
	m_IsEmpty = false;
}

void Inventory_Tile::RemoveItem()
{
	m_pItem = nullptr;
	m_IsEmpty = true;
}

void Inventory_Tile::DeleteItem()
{
	m_pItem->~Item();
	m_pItem = nullptr;
	m_IsEmpty = true;
}


bool Inventory_Tile::CheckIfClicked(Point2f pos)
{
	if (utils::IsPointInRect(pos, m_DestRect))
	{
		m_IsSelected = true;
		return true;
	}
	return false;
}

Item* Inventory_Tile::GetItem()
{
	return m_pItem;
}

void Inventory_Tile::DeSelect()
{
	m_IsSelected = false;
}
