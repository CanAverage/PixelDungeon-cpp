#pragma once
#include "SoundStream.h"
#include "SoundEffect.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void PlayGameMusic();
	void StopGameMusic();
	void PlayDeathSoundEffect();
	void PlayDoorOpeningSoundEffect();
	void PlayHitSoundEffect();
	void PlayItemSpawnSoundEffect();
	void PlayLevelUpSoundEffect();
	void PlayMissSoundEffect();
	bool CheckIfGameIsPlaying();
	void EditVolume(int amount);
private:
	SoundStream* m_pGameMusic;
	SoundEffect* m_pDeathEffect;
	SoundEffect* m_pDoorOpening;
	SoundEffect* m_pHit;
	SoundEffect* m_pItemSpawn;
	SoundEffect* m_pLevelUp;
	SoundEffect* m_pMiss;
	int m_Volume{100};
	bool m_IsMusicPlaying{false};
};
