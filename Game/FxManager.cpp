#include "stdafx.h"
#include "FxManager.h"
#include "Texture.h"

FxManager::FxManager()
{
	pFont = TTF_OpenFont("Resources/m04.ttf", 32);
	pBackFont = TTF_OpenFont("Resources/m04b.ttf", 32);
	pTextFont = TTF_OpenFont("Resources/m04.ttf", 20);
	pTextBackFont = TTF_OpenFont("Resources/m04b.ttf", 20);
}


FxManager::~FxManager()
{
	for (FxElement* element : m_pElements)
	{
		delete element;
		element = nullptr;
	}
}

void FxManager::Draw() const
{
	for (FxElement* element : m_pElements)
	{
		element->texture->Draw({
			element->rect.left, element->rect.bottom, element->texture->GetWidth() / 2,
			element->texture->GetHeight() / 2
		});
	}
}

void FxManager::Update(float elapsedSec)
{
	m_ElapsedSec += elapsedSec;
	for (int i{}; i < m_pElements.size(); ++i)
	{
		m_pElements[i]->rect.bottom += (m_ElapsedSec - m_pElements[i]->creationTimer) / 2;
		if (m_ElapsedSec - m_pElements[i]->creationTimer > 0.7)
		{
			FxElement* temp;
			temp = m_pElements.back();
			m_pElements.back() = m_pElements[i];
			m_pElements[i] = temp;
			m_pElements.pop_back();
		}
	}
}

void FxManager::CreateTexture(Rectf rect, int number)
{
	rect.width /= 2;
	rect.height /= 2;
	rect.left += rect.width / 2;
	rect.bottom += rect.height * 1.9f;
	m_pElements.push_back(new FxElement{
		rect, new Texture{std::to_string(number), pFont, Color4f(0.f, 0.f, 0.f, 1.f)}, m_ElapsedSec
	});
	m_pElements.push_back(new FxElement{
		rect, new Texture{std::to_string(number), pBackFont, Color4f(1.f, 0.f, 0.f, 1.f)}, m_ElapsedSec
	});
}

void FxManager::CreateTexture(Rectf rect, std::string input)
{
	rect.width /= 2;
	rect.height /= 2;
	rect.left += rect.width / 2;
	rect.bottom += rect.height * 1.9f;
	m_pElements.push_back(new FxElement{
		rect, new Texture{input, pTextFont, Color4f(0.f, 0.f, 0.f, 1.f)}, m_ElapsedSec
	});
	m_pElements.push_back(new FxElement{
		rect, new Texture{input, pTextBackFont, Color4f(0.f, 1.f, 0.f, 1.f)}, m_ElapsedSec
	});
}
