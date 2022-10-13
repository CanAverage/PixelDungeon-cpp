#include "stdafx.h"
#include "Player.h"
#include "Enemy_Rat.h"
#include "ItemManager.h"

Player::Player(Point2f pos, TileManager* manager, FxManager* fxManager, SoundManager* soundManager) :
	m_pMyManager{manager}, m_pFxManager{fxManager}, m_pSoundManager(soundManager),
	m_Pos{static_cast<float>(int(pos.x / m_TileSize)), static_cast<float>(int(pos.y / m_TileSize))}
{
	m_pSprite = new Texture{"Resources/warrior.png"};
	m_Pos.x *= m_TileSize;
	m_Pos.y *= m_TileSize;
	m_GridPos = m_Pos;
}


Player::~Player()
{
	delete m_pSprite;
}

void Player::Draw() const
{
	if (m_Direction == LEFT)
	{
		glPushMatrix();
		glTranslatef(m_Pos.x + m_pSprite->GetWidth() / 21 + 5, m_Pos.y, 0.f);
		glScalef(-1.f, 1.0f, 0.f);
		glTranslatef(-m_Pos.x - m_pSprite->GetWidth() / 21 - 5, -m_Pos.y, 0.f);
		m_pSprite->Draw(m_DestRect, m_SrcRect);
		glPopMatrix();
	}
	else
	{
		m_pSprite->Draw(m_DestRect, m_SrcRect);
	}
}

void Player::Draw(Rectf destRect) const
{
	Rectf srcRect{
		static_cast<float>(m_CharacterSpriteSize), (m_pSprite->GetHeight() / m_Row) * m_CurrentRow,
		m_pSprite->GetWidth() / m_Column, m_pSprite->GetHeight() / m_Row
	};
	m_pSprite->Draw(destRect, srcRect);
}

void Player::Update(float elapsedSec)
{
	m_WalkedOverDoor = false;
	//Checking what tile we're on and doing certain events if it's a special one
	for (Tile* element : m_pMyManager->GetWalkableTiles())
	{
		float tempX = element->GetColumn() - m_Pos.x / m_TileSize;
		float tempY = element->GetRow() - m_Pos.y / m_TileSize;
		if (std::abs(tempX) < 1 && std::abs(tempY) < 1)
		{
			if (element->GetCurrentSpriteNumber() == TileManager::ClosedDoor)
			{
				element->SetCurrentSpriteNumber(TileManager::OpenDoor);
				m_pSoundManager->PlayDoorOpeningSoundEffect();
				m_WalkedOverDoor = true;
				if (m_Door != nullptr)
				{
					m_Door->SetCurrentSpriteNumber(TileManager::ClosedDoor);
				}
				m_Door = element;
			}
			else if (element->GetCurrentSpriteNumber() == TileManager::OpenDoor)
			{
				m_WalkedOverDoor = true;
			}

			else if (element->GetCurrentSpriteNumber() == TileManager::Grass)
			{
				element->SetCurrentSpriteNumber(TileManager::StompedGrass);
				m_pItemManager->SpawnBubble({
					static_cast<float>(element->GetColumn()) * 32, static_cast<float>(element->GetRow()) * 32
				});
			}
		}
	}
	//Closing the door
	if (m_WalkedOverDoor == false && m_Door != nullptr)
	{
		m_Door->SetCurrentSpriteNumber(TileManager::ClosedDoor);
		m_Door = nullptr;
	}
	//Moving player & Camera
	if (m_MoveDistance.x != 0 || m_MoveDistance.y != 0)
	{
		if (m_MoveDistance.x > 0)
		{
			m_Pos.x += m_StepSpeed;
			m_MoveDistance.x -= m_StepSpeed;
			m_TranslateX -= m_StepSpeed;
		}
		else if (m_MoveDistance.x < 0)
		{
			m_Pos.x -= m_StepSpeed;
			m_MoveDistance.x += m_StepSpeed;
			m_TranslateX += m_StepSpeed;
		}
		else if (m_MoveDistance.y > 0)
		{
			m_Pos.y += m_StepSpeed;
			m_MoveDistance.y -= m_StepSpeed;
			m_TranslateY -= m_StepSpeed;
		}
		else if (m_MoveDistance.y < 0)
		{
			m_Pos.y -= m_StepSpeed;
			m_MoveDistance.y += m_StepSpeed;
			m_TranslateY += m_StepSpeed;
		}
	}
	//Making Destrect
	m_DestRect = {m_Pos.x, m_Pos.y, static_cast<float>(m_TileSize), static_cast<float>(m_TileSize)};
	//Making sprites move (idle + moving)
	if (m_HealthState == Alive)
	{
		if (m_Move == Walking && m_EnemyAhead == false)
		{
			m_CurrentSpriteNumber += 0.1f;
			m_SrcRect = {
				static_cast<float>(m_CharacterSpriteSize * (2 + (int(m_CurrentSpriteNumber) % 6))),
				(m_pSprite->GetHeight() / m_Row) * m_CurrentRow, m_pSprite->GetWidth() / m_Column,
				m_pSprite->GetHeight() / m_Row
			};
		}
		else if (m_Move == Stopped)
		{
			m_CurrentSpriteNumber += 0.007f;
			m_SrcRect = {
				static_cast<float>(m_CharacterSpriteSize * ((int(m_CurrentSpriteNumber) % 2))),
				(m_pSprite->GetHeight() / m_Row) * m_CurrentRow, m_pSprite->GetWidth() / m_Column,
				m_pSprite->GetHeight() / m_Row
			};
		}
		else if (m_Move == Fighting)
		{
			m_CurrentSpriteNumber += 0.2f;
			if (m_CurrentSpriteNumber <= 2.f)
			{
				m_SrcRect = {
					static_cast<float>(m_CharacterSpriteSize * (14 + (int(m_CurrentSpriteNumber) % 2))),
					(m_pSprite->GetHeight() / m_Row) * m_CurrentRow, m_pSprite->GetWidth() / m_Column,
					m_pSprite->GetHeight() / m_Row
				};
			}
			else if (m_CurrentSpriteNumber >= 5)
			{
				m_Move = Stopped;
			}
		}
	}
	else if (m_HealthState == Dying)
	{
		m_CurrentSpriteNumber += 0.1f;
		m_SrcRect = {
			m_pSprite->GetWidth() / m_Column * (8 + (static_cast<int>(m_CurrentSpriteNumber) % 5)) - 0.3f,
			(m_pSprite->GetHeight() / m_Row) * m_Row, m_pSprite->GetWidth() / m_Column, m_pSprite->GetHeight() / m_Row
		};

		if (m_CurrentSpriteNumber >= 3.8)
		{
			m_HealthState = Dead;
		}
	}
	if (m_MoveDistance.x == 0 && m_MoveDistance.y == 0 && m_Move != Fighting)
	{
		m_Move = Stopped;
	}
}

void Player::Move(DirectionState direction)
{
	if (m_HealthState != Dead && m_HealthState != Dying && m_Move != Fighting)
	{
		if (direction == UP)
		{
			if (CheckColission({m_Pos.x, m_Pos.y + m_TileSize}) == false && m_MoveDistance.x == 0 && m_MoveDistance.y ==
				0)
			{
				m_MoveDistance.y += m_TileSize;
				m_GridPos.y += m_TileSize;
				m_pMyEnemyManager->AddMovePoint();
				m_Move = Walking;
			}
		}
		else if (direction == DOWN)
		{
			if (CheckColission({m_Pos.x, m_Pos.y - m_TileSize}) == false && m_MoveDistance.x == 0 && m_MoveDistance.y ==
				0)
			{
				m_MoveDistance.y -= m_TileSize;
				m_GridPos.y -= m_TileSize;
				m_pMyEnemyManager->AddMovePoint();
				m_Move = Walking;
			}
		}
		else if (direction == LEFT)
		{
			if (CheckColission({m_Pos.x - m_TileSize, m_Pos.y}) == false && m_MoveDistance.x == 0 && m_MoveDistance.y ==
				0)
			{
				m_MoveDistance.x -= m_TileSize;
				m_GridPos.x -= m_TileSize;
				m_pMyEnemyManager->AddMovePoint();
				m_Direction = LEFT;
				m_Move = Walking;
			}
		}
		else if (direction == RIGHT)
		{
			if (CheckColission({m_Pos.x + m_TileSize, m_Pos.y}) == false && m_MoveDistance.x == 0 && m_MoveDistance.y ==
				0)
			{
				m_MoveDistance.x += m_TileSize;
				m_GridPos.x += m_TileSize;
				m_pMyEnemyManager->AddMovePoint();
				m_Direction = RIGHT;
				m_Move = Walking;
			}
		}
	}
}

void Player::Attack(DirectionState direction)
{
	if (m_EnemyAhead && m_pFoundEnemy != nullptr && m_HealthState == Alive && m_Move != Fighting)
	{
		if (direction == UP)
		{
			m_pFoundEnemy->Damage(CalculateDamage());
			m_pSoundManager->PlayHitSoundEffect();
			m_pMyEnemyManager->AddMovePoint();
			m_Move = Fighting;
			m_CurrentSpriteNumber = 0.f;
		}
		else if (direction == DOWN)
		{
			m_pFoundEnemy->Damage(CalculateDamage());
			m_pSoundManager->PlayHitSoundEffect();
			m_pMyEnemyManager->AddMovePoint();
			m_Move = Fighting;
			m_CurrentSpriteNumber = 0.f;
		}
		else if (direction == LEFT)
		{
			m_pFoundEnemy->Damage(CalculateDamage());
			m_pSoundManager->PlayHitSoundEffect();
			m_pMyEnemyManager->AddMovePoint();
			m_Move = Fighting;
			m_Direction = LEFT;
			m_CurrentSpriteNumber = 0.f;
		}
		else if (direction == RIGHT)
		{
			m_pFoundEnemy->Damage(CalculateDamage());
			m_pSoundManager->PlayHitSoundEffect();
			m_pMyEnemyManager->AddMovePoint();
			m_Move = Fighting;
			m_CurrentSpriteNumber = 0.f;
			m_Direction = RIGHT;
		}
	}
}

bool Player::CheckColission(Point2f pos)
{
	float tempX;
	float tempY;
	int teller{0};
	m_EnemyAhead = false;
	std::vector<Enemy*> enemies = m_pMyEnemyManager->GetEnemies();
	for (Enemy* element : enemies)
	{
		if (element != nullptr)
		{
			tempX = element->GetPos().x / m_TileSize - pos.x / m_TileSize;
			tempY = element->GetPos().y / m_TileSize - pos.y / m_TileSize;

			if (std::abs(tempX) < 1 && std::abs(tempY) < 1)
			{
				m_EnemyAhead = true;
				m_pFoundEnemy = element;
				return true;
			}
		}
	}
	for (Tile* element : m_pMyManager->GetNonWalkableTiles())
	{
		tempX = element->GetColumn() - pos.x / m_TileSize;
		tempY = element->GetRow() - pos.y / m_TileSize;
		if (std::abs(tempX) < 1 && std::abs(tempY) < 1)
		{
			if (element->m_WalkAble == 0)
			{
				return true;
			}
		}
	}
	return false;
}


void Player::SetPosition(Point2f pos)
{
	m_Pos.x = pos.x;
	m_Pos.y = pos.y;
	m_GridPos = m_Pos;
}

Point2f Player::GetPosition()
{
	return m_Pos;
}

Point2f Player::GetGridPosition()
{
	return m_GridPos;
}

void Player::Die()
{
	m_HealthState = Dying;
	m_CurrentSpriteNumber = 0.f;
	m_pSoundManager->PlayDeathSoundEffect();
}

void Player::SetEnemyManager(EnemyManager* Emanager)
{
	m_pMyEnemyManager = Emanager;
}

int Player::CalculateDamage()
{
	int damage;
	damage = (rand() % (m_BaseMaxDamage - m_BaseMinDamage)) + m_BaseMinDamage + m_WeaponDamage;
	float critTry;
	critTry = (rand() % 10) / 10.f;
	if (critTry <= m_CritChance)
	{
		damage *= 2;
	}
	return damage;
}


void Player::Damage(int damage)
{
	if (damage - m_DamageReduction > 0)
	{
		m_Health -= (damage - m_DamageReduction);
	}

	if (m_Health <= 0)
	{
		Die();
	}
	else
	{
		if (damage - m_DamageReduction > 0)
			m_pFxManager->CreateTexture({m_GridPos.x, m_GridPos.y, 32, 32}, damage - m_DamageReduction);
		else
			m_pFxManager->CreateTexture({m_GridPos.x, m_GridPos.y, 32, 32}, 0);
	}
	// Setting the UI
	if (m_Health != 0)
	{
		m_pPlayerStats->SetHealth(m_Health / static_cast<float>(m_MaxHealth));
	}
	else
	{
		m_pPlayerStats->SetHealth(static_cast<float>(m_Health));
	}
}

void Player::AddExp(int exp)
{
	m_AmountOfExp += exp;
	std::string temp{"+" + std::to_string(exp) + "exp"};
	m_pFxManager->CreateTexture(m_DestRect, temp);
	if (m_AmountOfExp >= m_AmountOfExpNeededToLevel)
	{
		m_AmountOfExp -= m_AmountOfExpNeededToLevel;
		m_PlayerLevel += 1;
		m_Health = m_MaxHealth;
		m_pPlayerStats->SetHealth(m_Health / static_cast<float>(m_MaxHealth));
		m_AmountOfExpNeededToLevel = static_cast<int>(1.5f * m_AmountOfExpNeededToLevel);
	}

	//Setting UI elements
	if (m_AmountOfExp != 0)
	{
		m_pPlayerStats->SetExp(m_AmountOfExp / static_cast<float>(m_AmountOfExpNeededToLevel));
	}
	else
	{
		m_pPlayerStats->SetExp(static_cast<float>(m_AmountOfExp));
	}

	m_pPlayerStats->SetLevel(m_PlayerLevel);
}

Rectf Player::getRect()
{
	return m_DestRect;
}

void Player::SetUIManager(UImanager* UImanager)
{
	m_pUiManager = UImanager;
	m_pPlayerStats = m_pUiManager->GetPlayerStatsReference();
}

void Player::SetItemManager(ItemManager* IManager)
{
	m_pItemManager = IManager;
}

void Player::IncreaseHealth(int health)
{
	m_Health += health;
	if (m_Health > m_MaxHealth)
	{
		m_Health = m_MaxHealth;
	}
	m_pPlayerStats->SetHealth(m_Health / static_cast<float>(m_MaxHealth));
}

bool Player::CheckIfFullhealth()
{
	if (m_Health == m_MaxHealth)
	{
		return true;
	}
	return false;
}


void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
	case SDLK_z:
		Attack(UP);
		break;
	case SDLK_LEFT:
	case SDLK_q:
		Attack(LEFT);
		break;
	case SDLK_DOWN:
	case SDLK_s:
		Attack(DOWN);
		break;
	case SDLK_RIGHT:
	case SDLK_d:
		Attack(RIGHT);
		break;
	}
}

void Player::ProcessKeyBoardState(const Uint8* pStates)
{
	if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
	{
		Move(RIGHT);
	}
	else if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
	{
		Move(LEFT);
	}
	else if (pStates[SDL_SCANCODE_DOWN] || pStates[SDL_SCANCODE_S])
	{
		Move(DOWN);
	}
	else if (pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W])
	{
		Move(UP);
	}
}


void Player::SetWeaponStats(int damage)
{
	m_WeaponDamage = damage;
}

void Player::SetArmorStats(int damageReduction)
{
	m_DamageReduction = damageReduction;
}


void Player::SetSpriteRow(int spriteRow)
{
	m_CurrentRow = spriteRow;
}

bool Player::CheckIfDead()
{
	if (m_HealthState == Dead)
	{
		return true;
	}
	return false;
}
