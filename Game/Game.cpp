#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game(const Window& window) : m_Window{window}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_pFxManager = new FxManager{};
	m_pSoundManager = new SoundManager{};
	m_pPopUpManager = new PopUpManager{};
	m_pPlayer = new Player{{230, 170}, &m_TileManager, m_pFxManager, m_pSoundManager};
	m_pItemManager = new ItemManager{m_pPlayer, m_pSoundManager};
	m_pEnemyManager = new EnemyManager{m_pFxManager, &m_TileManager, m_pPlayer, m_pItemManager, &m_KingIsKilled};
	m_pInventory = new Inventory{m_pItemManager, m_pPlayer};
	m_pMenu = new Menu{{m_Window.width, m_Window.height}};
	m_pUiManager = new UImanager{m_pPlayer, m_pInventory, m_Window, &m_IsInMenu};
	m_pInventory->AddItem(m_pItemManager->GetItem("ChainMail")); // "Cheated"
	m_pInventory->AddItem(m_pItemManager->GetItem("Sledgehammer")); // "Cheated"
	m_pPlayer->SetEnemyManager(m_pEnemyManager);
	m_pPlayer->SetUIManager(m_pUiManager);
	m_pPlayer->SetItemManager(m_pItemManager);
	m_TileManager.LoadLevel();
	m_pEnemyManager->CreateEnemies();
	for (Tile* element : m_TileManager.GetWalkableTiles())
	{
		if (element->GetCurrentSpriteNumber() == 7)
		{
			m_pPlayer->SetPosition({
				static_cast<float>(element->GetColumn() * m_TileSize),
				static_cast<float>(element->GetRow() * m_TileSize)
			});
			m_pPlayer->m_TranslateX = -static_cast<float>(element->GetColumn() * m_TileSize) + m_Window.width / 4;
			m_pPlayer->m_TranslateY = -static_cast<float>(element->GetRow() * m_TileSize) + m_Window.height / 4;
		}
	}
}

void Game::Cleanup()
{
	delete m_pEnemyManager;
	delete m_pPlayer;
	delete m_pMenu;
	delete m_pUiManager;
	delete m_pSoundManager;
	delete m_pPopUpManager;
	delete m_pFxManager;
	delete m_pInventory;
	delete m_pItemManager;
}

void Game::Update(float elapsedSec)
{
	//m_pPopUpManager->ShowGameOver();
	if (m_pPlayer->CheckIfDead() == true)
	{
		m_pPopUpManager->ShowGameOver();
		m_GameIsOver = true;
	}
	else if (m_KingIsKilled == true)
	{
		m_pPopUpManager->ShowBossSlain();
		m_GameIsOver = true;
	}
	else
	{
		if (m_IsInMenu)
		{
			if (m_pSoundManager->CheckIfGameIsPlaying() == true)
			{
				m_pSoundManager->StopGameMusic();
			}
			m_pMenu->Update(elapsedSec);
		}
		else
		{
			m_pItemManager->Update(elapsedSec);
			if (!m_pSoundManager->CheckIfGameIsPlaying())
			{
				m_pSoundManager->PlayGameMusic();
			}
			// Check keyboard state
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);
			if (m_IsInMap == false)
			{
				m_pPlayer->ProcessKeyBoardState(pStates);
			}
			else
			{
				if (pStates[SDL_SCANCODE_RIGHT])
				{
					m_FreeLookTranslate.x -= 10;
				}
				if (pStates[SDL_SCANCODE_LEFT])
				{
					m_FreeLookTranslate.x += 10;
				}
				if (pStates[SDL_SCANCODE_DOWN])
				{
					m_FreeLookTranslate.y += 10;
				}
				if (pStates[SDL_SCANCODE_UP])
				{
					m_FreeLookTranslate.y -= 10;
				}
				if (pStates[SDL_SCANCODE_KP_MINUS])
				{
					if (m_CameraScale > 0.2f)
						m_CameraScale -= 0.01f;
				}
				if (pStates[SDL_SCANCODE_KP_PLUS])
				{
					if (m_CameraScale < 2.f)
						m_CameraScale += 0.01f;
				}
			}


			m_pPlayer->Update(elapsedSec);
			m_pEnemyManager->UpdateEnemies(elapsedSec);
			m_pFxManager->Update(elapsedSec);
			m_pUiManager->Update();
		}
	}
}

void Game::Draw() const
{
	ClearBackground();
	if (m_IsInMenu)
	{
		m_pMenu->Draw();
	}
	else
	{
		glPushMatrix();
		if (m_IsInMap == true)
		{
			glTranslatef(m_Window.width / 2, m_Window.height / 2, 0);
			glScalef(m_CameraScale, m_CameraScale, 1);
			glTranslatef(-m_Window.width / 2, -m_Window.height / 2, 0);
			glTranslatef(static_cast<float>(m_FreeLookTranslate.x), static_cast<float>(m_FreeLookTranslate.y), 0);
		}
		if (m_IsInMap == false)
		{
			glScalef(m_CameraScale, m_CameraScale, 1);
			glTranslatef(m_pPlayer->m_TranslateX, m_pPlayer->m_TranslateY, 0);
		}
		m_TileManager.DrawTiles();
		m_pItemManager->Draw();
		m_pPlayer->Draw();
		if (m_IsInMap == false)
			m_pEnemyManager->DrawEnemies();

		m_pFxManager->Draw();
		glPopMatrix();

		if (m_HudEnabled)m_pUiManager->Draw();
		if (m_IsInMap == false)
			m_pPlayer->Draw(m_PlayerIcon);
		m_pPopUpManager->Draw();
		m_pInventory->Draw();
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_PAGEUP:
		m_pSoundManager->EditVolume(+2);
		break;
	case SDLK_PAGEDOWN:
		m_pSoundManager->EditVolume(-2);
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (m_GameIsOver == false)
	{
		if (!m_IsInMenu)
		{
			if (m_IsInMap == false)
			{
				m_pPlayer->ProcessKeyUpEvent(e);
			}
			switch (e.keysym.sym)
			{
			case SDLK_m:
				if (m_HudEnabled)m_HudEnabled = false;
				else if (m_HudEnabled == false) m_HudEnabled = true;
				if (m_IsInMap)
				{
					m_IsInMap = false;
					m_CameraScale = 2.f;
				}
				else
				{
					m_FreeLookTranslate.x = static_cast<int>(m_pPlayer->m_TranslateX);
					m_FreeLookTranslate.y = static_cast<int>(m_pPlayer->m_TranslateY);
					m_IsInMap = true;
					m_CameraScale = 0.5f;
				}
				break;
			case SDLK_i:
				m_pInventory->ToggleVisibility();
				break;
			case SDLK_h:
				if (m_IsInMap == false)
				{
					m_pPopUpManager->ToggleHelp();
				}
				break;
			case SDLK_ESCAPE:
				m_IsInMenu = true;
			}
		}
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	if (m_GameIsOver == false)
	{
		if (m_pInventory->IsVisible())
			m_pInventory->ProcessMouseDownEvent({static_cast<float>(e.x), m_Window.height - static_cast<float>(e.y)});
		else
			m_pUiManager->ProcessMouseDownEvent({static_cast<float>(e.x), m_Window.height - static_cast<float>(e.y)});
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (m_GameIsOver == false)
	{
		if (m_IsInMenu)
		{
			m_IsInMenu = m_pMenu->HandleClickPos({static_cast<float>(e.x), m_Window.height - static_cast<float>(e.y)});
		}
	}
}

void Game::ClearBackground() const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
