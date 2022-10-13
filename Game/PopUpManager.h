#pragma once
#include "Texture.h"

class PopUpManager
{
public:
	PopUpManager();
	~PopUpManager();
	void ShowGameOver();
	void ShowBossSlain();
	void ToggleHelp();
	void Draw() const;
private:
	Texture* m_pGameOver;
	Texture* m_pBossSlain;
	Texture* m_pInfo;
	bool m_ShowGameOver;
	bool m_ShowBossSlain;
	bool m_ShowInfo{false};
	const Rectf m_RectGameOver{75, 350, 400, 125};
	const Rectf m_RectBossSlain{25, 350, 500, 150};
	const Rectf m_RectFullScreen{0, 0, 550, 800};
};
