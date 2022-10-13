#include "stdafx.h"
#include "UI_PlayerStats.h"
#include "Player.h"

UI_PlayerStats::UI_PlayerStats(Player* player, Inventory* inventory, Window window, bool* menu)
	: m_pPlayer(player), m_pInventory(inventory), m_ShowMenu(menu)
{
	m_pStatsTexture = new Texture("Resources/status_pane.png");
	m_pHealthTexture = new Texture("Resources/hp_bar.png");
	m_pExpTexture = new Texture("Resources/exp_bar.png");
	m_pInventoryTexture = new Texture("Resources/Toolbar.png");
	pFont = TTF_OpenFont("Resources/m04b.ttf", 32);

	//Initialising rects
	m_pStatsRect = {0, 545, window.width, m_pStatsTexture->GetHeight() * 4};
	m_pInventoryRect = {460, 0, window.width / 6, m_pInventoryTexture->GetHeight() * 4};
	m_pHealthRect = {129, 772, (m_pHealthTexture->GetWidth() * 4.3f), m_pHealthTexture->GetHeight() * 4};
	m_pExpRect = {0, 796, window.width, m_pExpTexture->GetHeight() * 4};
	m_pLevelRect = {100, 667, 36, 36};
	m_pLevelTexture = new Texture{std::to_string(m_Level), pFont, Color4f(1.f, 1.f, 1.f, 1.f)};
}


UI_PlayerStats::~UI_PlayerStats()
{
	delete m_pStatsTexture;
	delete m_pExpTexture;
	delete m_pInventoryTexture;
	delete m_pHealthTexture;
	delete m_pLevelTexture;
}

void UI_PlayerStats::Update()
{
}

void UI_PlayerStats::Draw() const
{
	m_pStatsTexture->Draw(m_pStatsRect);
	m_pInventoryTexture->Draw(m_pInventoryRect);
	if (m_Health > 0)
	{
		Rectf tempSrcRect{0, 0, m_pHealthTexture->GetWidth() * m_Health, m_pHealthTexture->GetHeight()};
		Rectf tempDestRect = {
			m_pHealthRect.left, m_pHealthRect.bottom, m_pHealthRect.width * m_Health, m_pHealthRect.height
		};
		m_pHealthTexture->Draw(tempDestRect, tempSrcRect);
	}
	if (m_Exp > 0)
	{
		Rectf tempSrcRect{0, 0, m_pExpTexture->GetWidth() * m_Exp, m_pExpTexture->GetHeight()};
		Rectf tempDestRect = {m_pExpRect.left, m_pExpRect.bottom, m_pExpRect.width * m_Exp, m_pExpRect.height};
		m_pExpTexture->Draw(tempDestRect, tempSrcRect);
	}
	m_pLevelTexture->Draw(m_pLevelRect);
}


void UI_PlayerStats::SetHealth(float health)
{
	m_Health = health;
}

void UI_PlayerStats::SetExp(float exp)
{
	m_Exp = exp;
}

void UI_PlayerStats::SetLevel(int level)
{
	m_Level = level;
	m_pLevelTexture = new Texture{std::to_string(m_Level), pFont, Color4f(1.f, 1.f, 1.f, 1.f)};
}

void UI_PlayerStats::ProcessMouseDownEvent(Point2f pos)
{
	if (utils::IsPointInRect(pos, m_pInventoryRect))
	{
		m_pInventory->ToggleVisibility();
	}
	if (utils::IsPointInRect(pos, m_MenuRect))
	{
		(*m_ShowMenu) = true;
	}
}
