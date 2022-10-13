#include "stdafx.h"
#include "UImanager.h"
#include "Player.h"

UImanager::UImanager(Player* player, Inventory* inventory, Window window, bool* menu)
{
	m_pPlayerStats = new UI_PlayerStats(player, inventory, window, menu);
}


UImanager::~UImanager()
{
	delete m_pPlayerStats;
}

void UImanager::Draw() const
{
	m_pPlayerStats->Draw();
}

void UImanager::Update()
{
	m_pPlayerStats->Update();
}

UI_PlayerStats* UImanager::GetPlayerStatsReference()
{
	return m_pPlayerStats;
}

void UImanager::ProcessMouseDownEvent(Point2f pos)
{
	m_pPlayerStats->ProcessMouseDownEvent(pos);
}
