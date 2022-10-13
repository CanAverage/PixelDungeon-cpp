#pragma once
#include "Texture.h"
#include "Player.h"
#include <iostream>
#include "utils.h"
#include "Texture.h"
#include "FxManager.h"
#include "ItemManager.h"
class EnemyManager;

class Enemy
{
public:
	enum MovementState { Walking, Stopped, Fighting };

	struct Node
	{
		Node();
		Node(Node* tempNode);
		Node(int x, int y, int distance);
		int x;
		int y;
		int distance;
	};

	Enemy(EnemyManager* myManager, FxManager* fxManager, TileManager* tManager,
	      Texture* myTexture, Point2i coordinates, Point2f pos, Player* player, TextureInfo textureInfo
	      , ItemManager* itemManager, int health);
	virtual ~Enemy();
	virtual void Die();
	virtual void Damage(int amount);
	virtual void Draw() const;
	virtual void Update(float elapsedSec, bool playerFound);
	virtual bool TryToFindPlayer(Player* player);
	virtual void IncreaseMovement();
	virtual Point2f GetPos() const;
	virtual Point2f GetGridPos() const;
	virtual bool IsDead();
	virtual int getExp();
	virtual bool IsBoss();
protected:
	float m_CurrentSpriteNumber{};
	bool m_IsDying{false};
private:
	enum class direction { left, right };

	direction m_Direction{direction::right};
	virtual bool CheckColission(Point2f pos);
	virtual bool CanReach(Point2f pos);
	virtual int CalculateDamage();
	virtual void PathFindToPlayer();
	virtual bool CheckIfTileIsValid(Node pos);
	virtual bool CheckIfTileIsValid(Point2f pos);
	virtual bool CheckIfPosInVector(Point2f pos);
	virtual bool Enemy::CheckIfLowerNodeExists(Node node);
	int m_Health{}, m_RemainingMoves{}, m_MoveDistanceX, m_MoveDistanceY;
	Rectf m_SrcRect, m_DestRect;

	int m_TileSize{32};
	int m_StepSpeed{2};
	int m_CharacterSpriteSize{16};
	int m_Column;
	int m_Row;
	bool m_NextToPlayer;
	MovementState m_Move;
	bool m_CanAttack;
	bool m_PathFinding{true};
	bool m_IsDead{false};
	int m_AmountOfExp{2};
	//TEMP REMOVE THIS
	Node tempV{};
	std::vector<Node*> m_TempNodeList;
	//----
	std::vector<Node*> m_NodeList;
	Point2f m_Pos{}, m_PrevPos{}, m_GridPos{};
	Tile* m_pDoor;
	Texture* m_pTexture;
	TextureInfo m_TextureInfo;
	TileManager* m_MyTileManager;
	FxManager* m_FxManager;
	EnemyManager* m_pMyManager;
	ItemManager* m_pItemManager;
	Player* m_pPlayer;
	//Enemy Attack stats
	int m_BaseMinDamage{};
	int m_BaseMaxDamage{};
	float m_CritChance{};
	int m_CritMultiplier{};
};
