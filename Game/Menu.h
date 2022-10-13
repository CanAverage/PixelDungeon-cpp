#pragma once
#include "Texture.h"
#include "SoundStream.h"

class Menu
{
public:
	Menu(Point2f windowSize);
	~Menu();
	void Draw() const;
	void Update(float elapsedSec);
	bool Menu::HandleClickPos(Point2f mousePos);

private:
	Texture* m_pPixelDungeon;
	Texture* m_pDashBoard;
	Texture* m_pArches;
	Texture* m_pArches2;
	TTF_Font* pFont{};
	Point2f m_WindowSize;
	Rectf m_destRectArches{0, 0, m_WindowSize.x, m_WindowSize.y};
	Rectf m_srcRectArches{0, 0, m_WindowSize.x, m_WindowSize.y};
	Rectf m_destRectArches2{0, 0, m_WindowSize.x, m_WindowSize.y};
	Rectf m_srcRectArches2{0, 0, m_WindowSize.x, m_WindowSize.y};
	Rectf m_ClickAreaPlay{220, 257, 100, 145};
	SoundStream* m_Music;
	void StopMusic();
};
