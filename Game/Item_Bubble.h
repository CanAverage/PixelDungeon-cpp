#pragma once
#include "Item.h"
#include "Player.h"
#include "ItemManager.h"

class Item_Bubble : public Item
{
public:
	Item_Bubble(int textureIndex, int index, Texture* texture, Point2f pos, ItemManager* manager, Player* player);
	~Item_Bubble() override;
	int GetAmountOfHealth();
	void Interact() override;
	int GetIndex() override;
private:
	const int m_AmountOfHealthRecieved{2};
	ItemManager* m_pMyManager;
	Player* m_pPlayer;
	int m_MyIndex{};
};
