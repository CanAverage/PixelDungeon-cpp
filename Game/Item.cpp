#include "stdafx.h"
#include "Item.h"
#include "ItemManager.h"

Item::Item(int textureIndex, int index, Texture* texture, Point2f pos, Player* player): m_InWorld{true},
	m_Spawning{true}
	, m_pTexture(texture)
	, m_TextureIndex{textureIndex}, m_DestRect{pos.x, pos.y, 32, 32}
	, m_SrcRect{(texture->GetWidth() / 8) * (m_TextureIndex % 8), (texture->GetHeight() / 16) * (textureIndex / 8) + (texture->GetHeight() / 16), texture->GetWidth() / 8, texture->GetHeight() / 16},
	m_pPlayer{player}, m_StartedPosition(pos)
{
}

Item::Item(int textureIndex, int index, Texture* texture, Player* player) : m_InWorld{false}
                                                                            , m_Spawning{true}
                                                                            , m_pTexture(texture),
                                                                            m_TextureIndex{textureIndex},
                                                                            m_SrcRect{
	                                                                            (texture->GetWidth() / 8) * (
		                                                                            m_TextureIndex % 8),
	                                                                            (texture->GetHeight() / 16) * (
		                                                                            textureIndex / 8) + (texture->
		                                                                            GetHeight() / 16),
	                                                                            texture->GetWidth() / 8,
	                                                                            texture->GetHeight() / 16
                                                                            }, m_pPlayer{player}
{
}

//(((texture->GetHeight()/16)*16) - ((textureIndex % 15 - 1) * 16))
Item::~Item()
{
}

void Item::Draw() const
{
	if (m_InWorld == true)
	{
		m_pTexture->Draw(m_DestRect, m_SrcRect);
	}
}

void Item::Draw(Rectf dstRct) const
{
	m_pTexture->Draw(dstRct, m_SrcRect);
}

void Item::Update(float elapsedSec)
{
	if (m_InWorld == true)
	{
		if (m_AnimationMoved < m_AnimationMovement && m_AnimationReached == false)
		{
			m_AnimationMoved += elapsedSec * 40;
			m_DestRect.bottom += elapsedSec * 40;
		}
		else if (m_AnimationReached == false)
		{
			m_AnimationReached = true;
			m_AnimationMoved = 0;
		}
		if (m_AnimationReached == true && m_AnimationFinished == false)
		{
			m_DestRect.bottom -= elapsedSec * 40;
			if (m_DestRect.bottom < m_StartedPosition.y)
			{
				m_DestRect.bottom = m_StartedPosition.y;
				m_AnimationFinished = true;
			}
		}
		if (m_StartedPosition == m_pPlayer->GetPosition())
		{
			Interact();
		}
	}
}

void Item::Interact()
{
}


int Item::GetIndex()
{
	return 0;
}

int Item::GetTextureIndex()
{
	return m_TextureIndex;
}

std::string Item::GetName()
{
	return "";
}

std::string Item::GetType()
{
	return "BASE ITEM";
}
