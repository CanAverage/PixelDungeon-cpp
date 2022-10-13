#pragma once
#include "TileManager.h"
#include "Player.h"
#include  "EnemyManager.h"
#include "FxManager.h"
#include "UImanager.h"
#include "Menu.h"
#include "SoundManager.h"
#include "PopUpManager.h"
#include "ItemManager.h"
#include "Inventory.h"

class Game
{
public:
	explicit Game(const Window& window);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
private:
	// DATA MEMBERS
	const Window m_Window;
	TileManager m_TileManager{};
	EnemyManager* m_pEnemyManager;
	Player* m_pPlayer;
	UImanager* m_pUiManager;
	FxManager* m_pFxManager;
	SoundManager* m_pSoundManager;
	PopUpManager* m_pPopUpManager;
	ItemManager* m_pItemManager;
	Menu* m_pMenu;
	Inventory* m_pInventory;
	const int m_TileSize{32};
	float m_CameraScale{2};
	bool m_IsInMenu{true};
	bool m_HudEnabled{true};
	bool m_IsInMap{false};
	bool m_GameIsOver{false};
	Point2i m_FreeLookTranslate{400, 500};
	bool m_KingIsKilled{false};
	const Rectf m_PlayerIcon{37, 706, static_cast<float>(m_TileSize * 2), static_cast<float>(m_TileSize * 2)};
	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
};
