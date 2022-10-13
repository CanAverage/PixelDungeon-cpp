#include "stdafx.h"
#include "Item_Bubble.h"


Item_Bubble::Item_Bubble(int textureIndex, int index, Texture* texture, Point2f pos, ItemManager* manager,
                         Player* player)
	: Item(textureIndex, index, texture, pos, player), m_pMyManager{manager}, m_pPlayer{player}, m_MyIndex{index}

{
}


Item_Bubble::~Item_Bubble()
{
}

int Item_Bubble::GetAmountOfHealth()
{
	return m_AmountOfHealthRecieved;
}

void Item_Bubble::Interact()
{
	if (m_pPlayer->CheckIfFullhealth() == false)
	{
		m_pPlayer->IncreaseHealth(m_AmountOfHealthRecieved);
		m_pMyManager->DeleteItem(m_MyIndex);
	}
}

int Item_Bubble::GetIndex()
{
	return m_MyIndex;
}
