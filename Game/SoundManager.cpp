#include "stdafx.h"
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
	: m_pGameMusic{new SoundStream("Resources/game.mp3")}
	  , m_pDeathEffect{new SoundEffect("Resources/snd_death.mp3")}
	  , m_pDoorOpening{new SoundEffect("Resources/snd_door_open.mp3")}
	  , m_pHit{new SoundEffect("Resources/snd_hit.mp3")}
	  , m_pItemSpawn{new SoundEffect("Resources/snd_item.mp3")}
	  , m_pLevelUp{new SoundEffect("Resources/snd_levelup.mp3")}
	  , m_pMiss{new SoundEffect("Resources/snd_miss.mp3")}
{
}


SoundManager::~SoundManager()
{
	delete m_pGameMusic;
	delete m_pDeathEffect;
	delete m_pDoorOpening;
	delete m_pHit;
	delete m_pItemSpawn;
	delete m_pLevelUp;
	delete m_pMiss;
}

void SoundManager::PlayGameMusic()
{
	if (m_IsMusicPlaying == false)
	{
		m_IsMusicPlaying = true;
		m_pGameMusic->Play(true);
	}
}

void SoundManager::StopGameMusic()
{
	if (m_IsMusicPlaying == true)
	{
		m_IsMusicPlaying = false;
		m_pGameMusic->Stop();
	}
}

void SoundManager::PlayDeathSoundEffect()
{
	m_pDeathEffect->Play(0);
}

void SoundManager::PlayDoorOpeningSoundEffect()
{
	m_pDoorOpening->Play(0);
}

void SoundManager::PlayHitSoundEffect()
{
	m_pHit->Play(0);
}

void SoundManager::PlayItemSpawnSoundEffect()
{
	m_pItemSpawn->Play(0);
}

void SoundManager::PlayLevelUpSoundEffect()
{
	m_pLevelUp->Play(0);
}

void SoundManager::PlayMissSoundEffect()
{
	m_pMiss->Play(0);
}

bool SoundManager::CheckIfGameIsPlaying()
{
	return m_pGameMusic->IsPlaying();
}


void SoundManager::EditVolume(int volume)
{
	if (m_Volume <= 100 && m_Volume >= 0)
	{
		m_Volume += volume;
		m_pGameMusic->SetVolume(m_Volume);
	}
	if (m_Volume > 100)
	{
		m_Volume = 100;
	}
	else if (m_Volume < 0)
	{
		m_Volume = 0;
	}
}
