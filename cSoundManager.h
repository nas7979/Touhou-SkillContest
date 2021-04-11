#pragma once
#include "singleton.h"

struct SoundData
{
	Sound* Sound;
	float Volume;
};

class cSoundManager : public singleton <cSoundManager>
{
private:
	map<string, SoundData> m_Sounds;
	list<Channel*>  m_Channel;
	System* m_System;

public:
	cSoundManager();
	virtual ~cSoundManager();

	void Init();
	void Release();
	void Update();

	void AddSound(string Key, string Path, float Volume);
	Sound* Play(string Key, bool Loop = false);
	Sound* Play(string Key, float Volume, bool Loop = false);
	void PauseAll();
	void ResumeAll();
	void EndAll();
	void End(string Key);
	void SetTimeSpeed();
};

#define SOUND cSoundManager::GetInstance()