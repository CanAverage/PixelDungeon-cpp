#pragma once
#include "TileManager.h"
#include "EnemyManager.h"

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
	void ProcessWheelUpEvent(const SDL_MouseWheelEvent& e);
	TileManager m_TileManager{};
private:
	// DATA MEMBERS
	const Window m_Window;
	//OWN
	float m_CameraScale{1};
	int m_CurrentSelectedSprite{1};
	int m_CurrentSelectedEnemy{1};
	bool m_MouseDown{false};
	bool m_EnemyDrawingMode{false};
	float m_TranslateX{0};
	float m_TranslateY{0};
	float m_UnscaledTranslateX{0};
	float m_UnscaledTranslateY{0};

	Point2f m_CurrentMousePos{0, 0};

	EnemyManager m_pEnemyManager{};
	//HOVERTILE
	Rectf m_TempSrcRect{};
	Rectf m_TempDestRect{};
	bool m_HoverTileIsCreated{false};
	//HOVERENEMY
	Texture* m_pHoverEnemy{};
	bool m_HoverEnemyIsCreated{false};

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void CreateHoverTile(Point2f pos);
};
