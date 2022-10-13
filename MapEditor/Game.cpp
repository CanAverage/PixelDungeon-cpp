#include "stdafx.h"
#include "Game.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <errno.h>
#include <tchar.h>
#include <windows.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
Game::Game(const Window& window)
	: m_Window{window}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	HANDLE hLogFile;
	hLogFile = CreateFile(_T("D:\\log.txt"), GENERIC_WRITE,
	                      FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS,
	                      FILE_ATTRIBUTE_NORMAL, nullptr);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	if (m_EnemyDrawingMode == false)
	{
		if (m_MouseDown == true)
		{
			m_TileManager.CreateNewTile({
				                            static_cast<float>(m_CurrentMousePos.x - m_TranslateX),
				                            static_cast<float>(m_CurrentMousePos.y - m_TranslateY)
			                            }, m_CurrentSelectedSprite);
		}
		else
		{
			CreateHoverTile({
				static_cast<float>(m_CurrentMousePos.x - m_TranslateX),
				static_cast<float>(m_CurrentMousePos.y - m_TranslateY)
			});
		}
	}

	// Check keyboard state
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	if (m_EnemyDrawingMode == false)
	{
		if (pStates[SDL_SCANCODE_S] && pStates[SDL_SCANCODE_LCTRL])
		{
			m_TileManager.SaveLevel();
		}
		else if (pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S])
		{
			m_UnscaledTranslateY += 2;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
		{
			m_UnscaledTranslateX -= 2;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
		{
			m_UnscaledTranslateX += 2;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W])
		{
			m_UnscaledTranslateY -= 2;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
		}

		if (pStates[SDL_SCANCODE_L])
		{
			m_TileManager.LoadLevel();
		}
	}
	else
	{
		if (pStates[SDL_SCANCODE_S] && pStates[SDL_SCANCODE_LCTRL])
		{
			m_pEnemyManager.SaveEnemies();
		}
		else if (pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S])
		{
			m_UnscaledTranslateY += 2;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
		{
			m_UnscaledTranslateX -= 2;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
		{
			m_UnscaledTranslateX += 2;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
		}
		if (pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W])
		{
			m_UnscaledTranslateY -= 2;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
		}

		if (pStates[SDL_SCANCODE_L])
		{
			m_pEnemyManager.LoadEnemies();
		}
	}
}

void Game::Draw() const
{
	glPushMatrix();
	glTranslatef(m_UnscaledTranslateX, m_UnscaledTranslateY, 0);
	glScalef(m_CameraScale, m_CameraScale, 0);

	ClearBackground();
	m_TileManager.DrawTiles();
	m_pEnemyManager.DrawEnemies();
	if (m_HoverTileIsCreated == true && m_EnemyDrawingMode == false)
	{
		m_TileManager.GetTexture()->Draw(m_TempDestRect, m_TempSrcRect);
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (m_EnemyDrawingMode == false)
	{
		switch (e.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_DELETE:
		case SDLK_0:
			m_CurrentSelectedSprite = 0;
			std::cout << "DELETER SELECTED" << '\n';
			break;
		case SDLK_1:
			m_CurrentSelectedSprite = 1;
			std::cout << "GROUND SELECTED" << '\n';
			break;
		case SDLK_2:
			m_CurrentSelectedSprite = 2;
			std::cout << "GRASSY GROUND SELECTED" << '\n';
			break;
		case SDLK_3:
			m_CurrentSelectedSprite = 3;
			std::cout << "HOLE SELECTED" << '\n';
			break;
		case SDLK_4:
			m_CurrentSelectedSprite = 4;
			std::cout << "WALL SELECTED" << '\n';
			break;
		case SDLK_5:
			m_CurrentSelectedSprite = 5;
			std::cout << "DOOR SELECTED" << '\n';
			break;
		case SDLK_6:
			m_CurrentSelectedSprite = 6;
			std::cout << "INDENT SELECTED" << '\n';
			break;
		case SDLK_7:
			m_CurrentSelectedSprite = 7;
			std::cout << "STAIRS (UP) SELECTED" << '\n';
			break;
		case SDLK_8:
			m_CurrentSelectedSprite = 8;
			std::cout << "STAIRS (DOWN) SELECTED" << '\n';
			break;
		case SDLK_9:
			m_CurrentSelectedSprite = 9;
			std::cout << "BURNED GROUND SELECTED" << '\n';
			break;
		case SDLK_e:
			m_EnemyDrawingMode = true;
			break;
		case SDLK_KP_PLUS:
			m_CameraScale += 0.1f;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
			break;
		case SDLK_KP_MINUS:
			m_CameraScale -= 0.1f;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
			break;
		}
	}
	// If we're drawing enemys -------------------------------
	else
	{
		switch (e.keysym.sym)
		{
		case SDLK_1:
			m_CurrentSelectedEnemy = 0;
			std::cout << "RAT SELECTED" << '\n';
			break;
		case SDLK_2:
			m_CurrentSelectedEnemy = 1;
			std::cout << "Skeleton SELECTED" << '\n';
			break;
		case SDLK_3:
			m_CurrentSelectedEnemy = 2;
			std::cout << "Monk Selected" << '\n';
			break;
		case SDLK_4:
			m_CurrentSelectedEnemy = 3;
			std::cout << "King Selected" << '\n';
			break;
		case SDLK_e:
			m_EnemyDrawingMode = false;
			break;
		case SDLK_KP_PLUS:
			m_CameraScale += 0.1f;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
			break;
		case SDLK_KP_MINUS:
			m_CameraScale -= 0.1f;
			m_TranslateX = m_UnscaledTranslateX / m_CameraScale;
			m_TranslateY = m_UnscaledTranslateY / m_CameraScale;
			break;
		}
	}
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
	m_CurrentMousePos = {e.x / m_CameraScale, (m_Window.height - e.y) / m_CameraScale};
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	if (m_EnemyDrawingMode == false)
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			m_TileManager.CreateNewTile({
				                            static_cast<float>(m_CurrentMousePos.x - m_TranslateX),
				                            static_cast<float>(m_CurrentMousePos.y - m_TranslateY)
			                            }, m_CurrentSelectedSprite);
			m_MouseDown = true;
			break;
		}
	}
	else
	{
		switch (e.button)
		{
		case SDL_BUTTON_LEFT:
			m_pEnemyManager.CreateNewEnemy({
				                               static_cast<float>(m_CurrentMousePos.x - m_TranslateX),
				                               static_cast<float>(m_CurrentMousePos.y - m_TranslateY)
			                               }, m_CurrentSelectedEnemy);
			m_MouseDown = true;
			break;
		}
	}
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_MouseDown = false;
		break;
	}
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessWheelUpEvent(const SDL_MouseWheelEvent& e)
{
	if (m_EnemyDrawingMode == false)
	{
		switch (e.y)
		{
		case(1):
			if (m_CurrentSelectedSprite < 64)m_CurrentSelectedSprite += 1;
			else m_CurrentSelectedSprite = 0;
			std::cout << m_CurrentSelectedSprite << '\n';
			CreateHoverTile({m_CurrentMousePos.x - m_TranslateX, m_CurrentMousePos.y - m_TranslateY});
			break;
		case(-1):
			if (m_CurrentSelectedSprite > 0)m_CurrentSelectedSprite -= 1;
			else m_CurrentSelectedSprite = 64;
			std::cout << m_CurrentSelectedSprite << '\n';
			CreateHoverTile({m_CurrentMousePos.x - m_TranslateX, m_CurrentMousePos.y - m_TranslateY});
			break;
		}
	}
}


void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Game::CreateHoverTile(Point2f pos)
{
	int tempRow = static_cast<int>(pos.y) / 32;
	int tempColumn = static_cast<int>(pos.x) / 32;
	Texture* pTempSprite = m_TileManager.GetTexture();
	float tempHeight = pTempSprite->GetHeight() / 4;
	float tempWidth = pTempSprite->GetWidth() / 16;
	m_TempSrcRect = {
		tempWidth * m_CurrentSelectedSprite, tempHeight + (tempHeight * static_cast<int>(m_CurrentSelectedSprite / 16)),
		tempWidth, tempHeight
	};
	m_TempDestRect = {
		static_cast<float>(tempColumn * 32), static_cast<float>(tempRow * 32), tempWidth * 2, tempHeight * 2
	};
	m_HoverTileIsCreated = true;
}
