#include "stdafx.h"
#include "PopUpManager.h"


PopUpManager::PopUpManager()
{
	m_pGameOver = new Texture{"Resources/GameOver.png"};
	m_pBossSlain = new Texture{"Resources/Boss slain.png"};
	m_pInfo = new Texture{"Resources/Help.png"};
}


PopUpManager::~PopUpManager()
{
	delete m_pGameOver;
	delete m_pBossSlain;
}

void PopUpManager::Draw() const
{
	if (m_ShowGameOver == true)
	{
		glColor4f(0.f, 0.f, 0.f, 0.6f);
		utils::FillRect(m_RectFullScreen);
		m_pGameOver->Draw(m_RectGameOver);
	}
	if (m_ShowBossSlain == true)
	{
		glColor4f(0.f, 0.f, 0.f, 0.6f);
		utils::FillRect(m_RectFullScreen);
		m_pBossSlain->Draw(m_RectBossSlain);
	}
	if (m_ShowInfo == true)
	{
		m_pInfo->Draw(m_RectFullScreen);
	}
}

void PopUpManager::ShowGameOver()
{
	m_ShowGameOver = true;
}

void PopUpManager::ShowBossSlain()
{
	m_ShowBossSlain = true;
}

void PopUpManager::ToggleHelp()
{
	if (m_ShowInfo == false)
	{
		m_ShowInfo = true;
	}
	else
	{
		m_ShowInfo = false;
	}
}
