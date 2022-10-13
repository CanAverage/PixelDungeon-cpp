#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"

Enemy::Enemy(EnemyManager* myManager, FxManager* fxManager, TileManager* tManager, Texture* myTexture
             , Point2i coordinates, Point2f pos, Player* player, TextureInfo textureInfo, ItemManager* itemManager,
             int health)
	: m_Health{health}, m_Column{coordinates.x}, m_Row{coordinates.y}, m_Pos{pos}, m_pTexture{myTexture}
	  , m_TextureInfo(textureInfo), m_MyTileManager{tManager}, m_FxManager{fxManager}
	  , m_pMyManager{myManager}, m_pItemManager{itemManager}, m_pPlayer{player}
{
	m_GridPos = m_Pos;
}


Enemy::~Enemy()
{
	if (m_pDoor != nullptr)
	{
		m_pDoor->SetCurrentSpriteNumber(TileManager::ClosedDoor);
	}
}

Enemy::Node::Node()
{
}

Enemy::Node::Node(int x, int y, int distance) : x{x}, y{y}, distance{distance}
{
}

Enemy::Node::Node(Node* tempNode) : x{tempNode->x}, y{tempNode->y}, distance{tempNode->distance}
{
}


void Enemy::Draw() const
{
	if (m_Direction == direction::left)
	{
		glPushMatrix();
		glTranslatef(m_Pos.x + m_pTexture->GetWidth() / m_Column, m_Pos.y, 0.f);
		glScalef(-1.f, 1.0f, 0.f);
		glTranslatef(-m_Pos.x - m_pTexture->GetWidth() / m_Column, -m_Pos.y, 0.f);
		m_pTexture->Draw(m_DestRect, m_SrcRect);
		glPopMatrix();
	}
	else
	{
		m_pTexture->Draw(m_DestRect, m_SrcRect);
	}
	/*
	for (Node element : m_TempNodeList) {
	glColor3f(255, 255, 255);
	utils::DrawRect(element.x * 32, element.y * 32, 32, 32);

	}
	glColor3f(255, 0, 0);
	utils::DrawRect(tempV.x * 32, tempV.y * 32, 32, 32);
	for (Node element : m_NodeList) {
	glColor3f(255, 255, 0);
	utils::DrawRect(element.x * 32, element.y * 32, 32, 32);
	}
	*/
}

void Enemy::Update(float elapsedSec, bool playerFound)
{
	if (m_Health <= 0 && m_IsDying == false)
	{
		Die();
	}
	if (m_Pos == m_PrevPos && m_Move != Fighting)
	{
		m_Move = Stopped;
	}
	else if (m_Move != Fighting)
	{
		m_Move = Walking;
	}
	m_DestRect = {m_Pos.x, m_Pos.y, static_cast<float>(m_TileSize), static_cast<float>(m_TileSize)};
	if (m_IsDying == false)
	{
		if (m_Move == Walking)
		{
			m_CurrentSpriteNumber += 0.1f;
			m_SrcRect = {
				static_cast<float>(m_pTexture->GetWidth() / m_Column * (m_TextureInfo.walkBegin + (int(
						m_CurrentSpriteNumber) %
					m_TextureInfo.walkLength))),
				(m_pTexture->GetHeight() / m_Row), m_pTexture->GetWidth() / m_Column, m_pTexture->GetHeight() / m_Row
			};
		}
		else if (m_Move == Stopped)
		{
			m_CurrentSpriteNumber += 0.01f;
			m_SrcRect = {
				static_cast<float>(m_pTexture->GetWidth() / m_Column * ((int(m_CurrentSpriteNumber) % m_TextureInfo.
					idleLength))),
				(m_pTexture->GetHeight() / m_Row), m_pTexture->GetWidth() / m_Column, m_pTexture->GetHeight() / m_Row
			};
		}
		else if (m_Move == Fighting)
		{
			m_CurrentSpriteNumber += static_cast<float>(m_TextureInfo.attackLength) / 50;
			m_SrcRect = {
				static_cast<float>(m_pTexture->GetWidth() / m_Column * (m_TextureInfo.attackBegin + (int(
						m_CurrentSpriteNumber) %
					m_TextureInfo.attackLength))),
				(m_pTexture->GetHeight() / m_Row), m_pTexture->GetWidth() / m_Column, m_pTexture->GetHeight() / m_Row
			};
			if (m_CurrentSpriteNumber >= m_TextureInfo.attackLength)
			{
				m_Move = Stopped;
			}
		}
	}
	else if (m_IsDying == true && m_IsDead == false)
	{
		m_CurrentSpriteNumber += static_cast<float>(m_TextureInfo.deathLength) / 40;
		m_SrcRect = {
			static_cast<float>(m_pTexture->GetWidth() / m_Column * (m_TextureInfo.deathBegin + (int(
					m_CurrentSpriteNumber) %
				m_TextureInfo.deathLength))),
			(m_pTexture->GetHeight() / m_Row), m_pTexture->GetWidth() / m_Column, m_pTexture->GetHeight() / m_Row
		};
		if (m_CurrentSpriteNumber >= m_TextureInfo.deathLength - 0.5f)
		{
			m_IsDead = true;
		}
	}
	TryToFindPlayer(m_pPlayer);
	if (m_PathFinding && m_RemainingMoves == 1 && m_NextToPlayer == false && m_Move != Fighting)
	{
		PathFindToPlayer();
		m_TempNodeList.clear();
		int depth = m_NodeList.back()->distance - 1;
		//std::cout << depth << std::endl;
		//if (depth == 0) depth = 1;
		int teller = static_cast<int>(m_NodeList.size());
		for (int i{0}; i <= teller - 1; ++i)
		{
			if (m_NodeList[i]->distance == depth)
			{
				m_TempNodeList.push_back(m_NodeList[i]);
			}
		}
		for (Node* element : m_TempNodeList)
		{
			if (abs(m_Pos.x - element->x * 32) < 33 && abs(m_Pos.y - element->y * 32) < 33)
			{
				CheckColission({static_cast<float>(element->x) * 32, static_cast<float>(element->y) * 32});
				m_MoveDistanceX = static_cast<int>(element->x * 32 - m_Pos.x);
				m_MoveDistanceY = static_cast<int>(element->y * 32 - m_Pos.y);
			}
		}
		m_RemainingMoves--;
	}
	else if (m_RemainingMoves >= 1 && m_NextToPlayer == false && m_Move != Fighting)
	{
		int temp{static_cast<int>(rand() % 4)};
		bool hasMoved{false};
		switch (temp)
		{
		case 1:
			if (CheckColission({(m_Pos.x - m_TileSize), m_Pos.y}) == false)
			{
				m_MoveDistanceX -= m_TileSize;
				hasMoved = true;
			}
		case 2:
			if (CheckColission({(m_Pos.x + m_TileSize), m_Pos.y}) == false && hasMoved == false)
			{
				m_MoveDistanceX += m_TileSize;
				hasMoved = true;
			}
		case 3:
			if (CheckColission({m_Pos.x, (m_Pos.y - m_TileSize)}) == false && hasMoved == false)
			{
				m_MoveDistanceY -= m_TileSize;
				hasMoved = true;
			}
		case 4:
			if (CheckColission({m_Pos.x, (m_Pos.y + m_TileSize)}) == false && hasMoved == false)
			{
				m_MoveDistanceY += m_TileSize;
				hasMoved = true;
			}
			break;
		}
		m_RemainingMoves--;
	}
	m_PrevPos = m_Pos;
	if (m_MoveDistanceX != 0 || m_MoveDistanceY != 0 && m_Move != Fighting)
	{
		if (m_MoveDistanceX > 0)
		{
			if (m_Pos.x > m_GridPos.x)
			{
				m_GridPos.x += 32;
			}
			m_Pos.x += m_StepSpeed;
			m_MoveDistanceX -= m_StepSpeed;
			m_Direction = direction::right;
		}
		else if (m_MoveDistanceX < 0)
		{
			if (m_Pos.x < m_GridPos.x)
			{
				m_GridPos.x -= 32;
			}
			m_Pos.x -= m_StepSpeed;
			m_MoveDistanceX += m_StepSpeed;
			m_Direction = direction::left;
		}
		else if (m_MoveDistanceY > 0)
		{
			if (m_Pos.y > m_GridPos.y)
			{
				m_GridPos.y += 32;
			}
			m_Pos.y += m_StepSpeed;
			m_MoveDistanceY -= m_StepSpeed;
		}
		else if (m_MoveDistanceY < 0)
		{
			if (m_Pos.y < m_GridPos.y)
			{
				m_GridPos.y -= 32;
			}
			m_Pos.y -= m_StepSpeed;
			m_MoveDistanceY += m_StepSpeed;
		}
	}
	TryToFindPlayer(m_pPlayer);
	if (m_NextToPlayer == true && m_RemainingMoves >= 1 && m_IsDying == false)
	{
		m_pPlayer->Damage(CalculateDamage());
		m_RemainingMoves--;
		m_CurrentSpriteNumber = 0.f;
		m_Move = Fighting;
	}
}


void Enemy::Die()
{
	m_CurrentSpriteNumber = 0.f;
	m_IsDying = true;
}

void Enemy::Damage(int amount)
{
	if (m_IsDying == false)
	{
		m_Health -= amount;
		if (m_Health < 0)
		{
			Die();
		}
		else
		{
			m_FxManager->CreateTexture(m_DestRect, amount);
		}
	}
}

bool Enemy::TryToFindPlayer(Player* player)
{
	Point2f temp{player->GetGridPosition()};
	m_pPlayer = player;
	float distance = sqrt(pow(temp.x - m_Pos.x, 2) + (pow(temp.y - m_Pos.y, 2)));
	if (distance < 40)
	{
		m_NextToPlayer = true;
	}
	else
	{
		m_NextToPlayer = false;
	}
	if (distance < 200)
	{
		m_PathFinding = true;
		return true;
	}
	m_PathFinding = false;
	return false;
}

void Enemy::IncreaseMovement()
{
	m_RemainingMoves++;
}

bool Enemy::CheckColission(Point2f pos)
{
	float tempX;
	float tempY;
	for (Tile* element : m_MyTileManager->GetWalkableTiles())
	{
		tempX = element->GetColumn() - pos.x / m_TileSize;
		tempY = element->GetRow() - pos.y / m_TileSize;
		if (std::abs(tempX) < 1 && std::abs(tempY) < 1)
		{
			if (element->GetCurrentSpriteNumber() == static_cast<int>(TileManager::ClosedDoor))
			{
				element->SetCurrentSpriteNumber(static_cast<int>(TileManager::OpenDoor));
				m_pDoor = element;
			}
			else if (m_pDoor != nullptr)
			{
				m_pDoor->SetCurrentSpriteNumber(TileManager::ClosedDoor);
				m_pDoor = nullptr;
			}
			return false;
		}
	}

	return true;
}

bool Enemy::CanReach(Point2f pos)
{
	if (pos.x < m_Pos.x)
	{
		if (m_Pos.x <= pos.x && CheckColission({pos.x, pos.y}) == false)
		{
			return true;
		}
	}
	if (pos.x > m_Pos.x)
	{
		if (m_Pos.x >= pos.x && CheckColission({pos.x, pos.y}) == false)
		{
			return true;
		}
	}
	if (pos.y < m_Pos.y)
	{
		if (m_Pos.y <= pos.y && CheckColission({pos.x, pos.y}) == false)
		{
			return true;
		}
	}
	if (pos.y > m_Pos.y)
	{
		if (m_Pos.y >= pos.y && CheckColission({pos.x, pos.y}) == false)
		{
			return true;
		}
	}
	return false;
}


void Enemy::PathFindToPlayer()
{
	m_NodeList.clear();
	Node tempNode{};
	tempNode = new Node{
		static_cast<int>(m_pPlayer->GetGridPosition().x / 32), static_cast<int>(m_pPlayer->GetGridPosition().y / 32), 0
	};
	m_NodeList.push_back(&tempNode);
	std::vector<Node> tempNodeList;
	int depth{0};
	while (CheckIfPosInVector(m_Pos) == false && depth < 20)
	{
		for (int i{}; i < m_NodeList.size(); ++i)
		{
			if (m_NodeList[i]->distance == depth - 1)
			{
				tempNodeList.push_back({m_NodeList[i]->x + 1, m_NodeList[i]->y, depth});
				tempNodeList.push_back({m_NodeList[i]->x - 1, m_NodeList[i]->y, depth});
				tempNodeList.push_back({m_NodeList[i]->x, m_NodeList[i]->y + 1, depth});
				tempNodeList.push_back({m_NodeList[i]->x, m_NodeList[i]->y - 1, depth});
				for (Node elem : tempNodeList)
				{
					if (CheckIfTileIsValid(elem) && CheckIfLowerNodeExists(elem) == false)
					{
						m_NodeList.push_back(new Node{elem.x, elem.y, elem.distance});
					}
				}
				tempNodeList.clear();
			}
		}
		depth++;
	}
}

bool Enemy::CheckIfTileIsValid(Node pos)
{
	for (Tile* element : m_MyTileManager->GetNonWalkableTiles())
	{
		if (element->GetColumn() == pos.x && element->GetRow() == pos.y)
		{
			return false;
		}
	}
	float tempX{};
	float tempY{};
	for (Enemy* element : m_pMyManager->GetEnemies())
	{
		tempX = element->GetGridPos().x / m_TileSize - pos.x;
		tempY = element->GetGridPos().y / m_TileSize - pos.y;
		if (std::abs(tempX < 1 && std::abs(tempY) < 1 && element != this))
		{
			return false;
		}
	}
	return true;
}

bool Enemy::CheckIfTileIsValid(Point2f pos)
{
	for (Tile* element : m_MyTileManager->GetNonWalkableTiles())
	{
		if (element->GetColumn() == pos.x && element->GetRow() == pos.y)
		{
			return false;
		}
	}
	float tempX{};
	float tempY{};
	for (Enemy* element : m_pMyManager->GetEnemies())
	{
		tempX = element->GetGridPos().x / m_TileSize - pos.x;
		tempY = element->GetGridPos().y / m_TileSize - pos.y;
		if (std::abs(tempX < 1 && std::abs(tempY) < 1 && element != this))
		{
			return false;
		}
	}
	return true;
}

bool Enemy::CheckIfPosInVector(Point2f pos)
{
	for (Node* element : m_NodeList)
	{
		int tempx = static_cast<int>(pos.x / 32);
		int tempy = static_cast<int>(pos.y / 32);
		if (tempx == element->x && tempy == element->y)
		{
			return true;
		}
	}
	return false;
}

bool Enemy::CheckIfLowerNodeExists(Node node)
{
	for (Node* element : m_NodeList)
	{
		if (node.x == element->x && node.y == element->y && element->distance <= node.distance)
		{
			return true;
		}
	}
	return false;
}

Point2f Enemy::GetPos() const
{
	return m_Pos;
}

Point2f Enemy::GetGridPos() const
{
	return m_GridPos;
}

int Enemy::CalculateDamage()
{
	return 0;
}


bool Enemy::IsDead()
{
	return m_IsDead;
}


int Enemy::getExp()
{
	return 0;
}

bool Enemy::IsBoss()
{
	return false;
}
