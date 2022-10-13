#pragma once
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include "utils.h"
#include "Texture.h"
#include "TileManager.h"

#include "UImanager.h"
#include "UI_PlayerStats.h"
#include "SoundManager.h"
#include "EnemyManager.h"

class ItemManager;

class Player
{
public:
	enum MovementState { Walking, Stopped, Fighting };

	enum DirectionState { LEFT, RIGHT, DOWN, UP };

	enum HealthState { Alive, Dying, Dead };

	MovementState m_Move{Stopped};
	DirectionState m_Direction{UP};
	Player(Point2f pos, TileManager* manager, FxManager* fxManager, SoundManager* soundManager);
	~Player();
	void Draw() const;
	void Draw(Rectf destRect) const;
	void Update(float elapsedSec);
	void Move(DirectionState direction);
	void Attack(DirectionState direction);
	void AddExp(int exp);
	bool CheckColission(Point2f pos);
	void SetPosition(Point2f pos);
	void SetEnemyManager(EnemyManager* Emanager);
	void SetUIManager(UImanager* UImanager);
	void SetItemManager(ItemManager* IManager);
	void SetWeaponStats(int damage);
	void SetArmorStats(int damageReduction);
	void SetSpriteRow(int spriteRow);
	bool CheckIfDead();
	Rectf getRect();
	Point2f GetPosition();
	Point2f GetGridPosition();
	bool CheckIfFullhealth();
	float m_TranslateX{};
	float m_TranslateY{};
	void Die();
	void Damage(int damage);
	void IncreaseHealth(int health);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyBoardState(const Uint8* pStates);
private:
	//Private Function
	int CalculateDamage();
	// Damage stats
	const int m_BaseMinDamage{1};
	const int m_BaseMaxDamage{5};
	int m_WeaponDamage{};
	const float m_CritChance{0.10f};
	const int m_CritMultiplier{2};
	//Armor stats
	int m_DamageReduction{};
	// level stats
	int m_PlayerLevel{1};
	int m_AmountOfExp{0};
	int m_AmountOfExpNeededToLevel{4};
	//Sort of magic numbers
	int m_MaxHealth{30};
	int m_Health{m_MaxHealth};
	const int m_Column{21};
	const int m_Row{7};
	int m_CurrentRow{1};
	const int m_TileSize{32};
	const int m_StepSpeed{2};
	const int m_CharacterSpriteSize{12};
	//Variables
	HealthState m_HealthState{Alive};
	bool m_WalkedOverDoor{false};
	bool m_EnemyAhead;
	Tile* m_Door;
	//Managers
	TileManager* m_pMyManager;
	EnemyManager* m_pMyEnemyManager;
	FxManager* m_pFxManager;
	UI_PlayerStats* m_pPlayerStats;
	UImanager* m_pUiManager;
	SoundManager* m_pSoundManager;
	ItemManager* m_pItemManager;
	Enemy* m_pFoundEnemy;
	Point2f m_Pos, m_GridPos;
	Point2f m_MoveDistance;
	Texture* m_pSprite;
	float m_CurrentSpriteNumber{0};
	Rectf m_DestRect;
	Rectf m_SrcRect;
};
