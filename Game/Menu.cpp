#include "stdafx.h"
#include "Menu.h"
#include <iostream>

Menu::Menu(Point2f windowSize) : m_WindowSize{windowSize}
{
	m_pPixelDungeon = new Texture("Resources/PixelDungeon.png");
	m_pDashBoard = new Texture("Resources/Dashboard.png");
	pFont = TTF_OpenFont("Resources/upheavtt.ttf", 75);
	m_pArches = new Texture("Resources/Arches.png");
	m_pArches2 = new Texture("Resources/Arches2.png");
	m_Music = new SoundStream("Resources/theme.mp3");
	m_Music->Play(true);
}


Menu::~Menu()
{
	delete m_pPixelDungeon;
	delete m_pDashBoard;
	delete m_pArches;
	delete m_pArches2;
	delete m_Music;
}


void Menu::Draw() const
{
	m_pArches2->Draw(m_destRectArches2, m_srcRectArches2);
	m_pArches->Draw(m_destRectArches, m_srcRectArches);

	Rectf DestRect{75, 550, 400, 200};
	m_pPixelDungeon->Draw(DestRect);

	Rectf SrcRect{0, 0, m_pDashBoard->GetWidth() / 4, m_pDashBoard->GetHeight()};
	DestRect = {220, 300, 100, 100};
	m_pDashBoard->Draw(DestRect, SrcRect);

	Texture levelTexture{"Play", pFont, Color4f(1.f, 1.f, 1.f, 1.f)};
	DestRect = {245, 257, 60, 40};
	levelTexture.Draw(DestRect);
}


void Menu::Update(float elapsedSec)
{
	if (m_Music->IsPlaying() == false)
	{
		m_Music->Play(true);
	}
	m_srcRectArches.bottom += 2;
	m_srcRectArches2.bottom += 3;
}


bool Menu::HandleClickPos(Point2f MousePos)
{
	if (utils::IsPointInRect(MousePos, m_ClickAreaPlay))
	{
		StopMusic();
		return false;
	}
	return true;
}


void Menu::StopMusic()
{
	m_Music->Stop();
}
