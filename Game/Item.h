#pragma once
#include "Texture.h"
#include "Player.h"

class Item
{
public:
	Item(int textureIndex, int index, Texture* texture, Point2f pos, Player* player);
	Item(int textureIndex, int index, Texture* texture, Player* player);
	virtual ~Item();
	virtual void Draw() const;
	virtual void Draw(Rectf dstRct) const;
	virtual void Update(float elapsedSec);
	virtual void Interact();
	virtual int GetIndex();
	virtual int GetTextureIndex();
	virtual std::string GetName();
	virtual std::string GetType();
private:
	bool m_InWorld;
	bool m_Spawning;
	Texture* m_pTexture;
	int m_TextureIndex;
	Rectf m_DestRect;
	Rectf m_SrcRect;
	Player* m_pPlayer;
	const int m_AnimationMovement{8};
	float m_AnimationMoved{0};
	Point2f m_StartedPosition{};
	bool m_AnimationReached{false};
	bool m_AnimationFinished{false};
};
