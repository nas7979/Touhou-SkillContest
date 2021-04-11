#include "DXUT.h"
#include "cSoundManager.h"

cSoundManager::cSoundManager()
{
	Init();
}


cSoundManager::~cSoundManager()
{
	Release();
}

void cSoundManager::Init()
{
	System_Create(&m_System);
	m_System->init(64, FMOD_INIT_NORMAL, 0);
	ChannelGroup* a;
	m_System->getMasterChannelGroup(&a);
	a->setVolume(0.3);
}

void cSoundManager::Update()
{
	bool IsPlaying;
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->isPlaying(&IsPlaying);
		if (IsPlaying == false)
		{
			iter = m_Channel.erase(iter);
		}
		else iter++;
	}
}

void cSoundManager::Release()
{
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->stop();
		iter = m_Channel.erase(iter);
	}
	for (auto& iter = m_Sounds.begin(); iter != m_Sounds.end();)
	{
		(*iter).second.Sound->release();
		iter = m_Sounds.erase(iter);
	}
	m_Sounds.clear();
	m_Channel.clear();
	m_System->release();
}

void cSoundManager::AddSound(string Key, string Path, float Volume)
{
	Sound* _Sound;
	m_System->createSound(Path.c_str(), FMOD_DEFAULT, NULL, &_Sound);
	m_Sounds.insert(make_pair(Key, SoundData{ _Sound,Volume }));
}

Sound* cSoundManager::Play(string Key, bool Loop)
{
	SoundData _Sound = m_Sounds.find(Key)->second;
	if ((_Sound.Sound) == nullptr) return nullptr;
	Channel * _Channel;
	m_System->playSound(_Sound.Sound, NULL, NULL, &_Channel);
	_Channel->setVolume(_Sound.Volume);
	m_Channel.push_back(_Channel);
	if (Key != "PlayerShot" && Key != "Graze" && Key != "PlayerSpell")
	_Channel->setPitch(min(SYSTEM->GetTimeSpeed(), 1));
	return (_Sound.Sound);
}

Sound* cSoundManager::Play(string Key, float Volume, bool Loop)
{
	SoundData _Sound = m_Sounds.find(Key)->second;
	if ((_Sound.Sound) == nullptr) return nullptr;
	Channel * _Channel;
	m_System->playSound(_Sound.Sound, NULL, NULL, &_Channel);
	_Channel->setVolume(Volume);
	m_Channel.push_back(_Channel);
	if (Key != "PlayerShot" && Key != "Graze" && Key != "PlayerSpell")
		_Channel->setPitch(min(SYSTEM->GetTimeSpeed(), 1));
	return (_Sound.Sound);
}

void cSoundManager::PauseAll()
{
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->setPaused(true);
	}
}

void cSoundManager::ResumeAll()
{
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->setPaused(false);
	}
}

void cSoundManager::EndAll()
{
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->stop();
		iter = m_Channel.erase(iter);
	}
	m_Channel.clear();
}

void cSoundManager::End(string Key)
{
	Sound* _Sound;
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->getCurrentSound(&_Sound);
		if (m_Sounds.find(Key)->second.Sound == _Sound)
		{
			(*iter)->stop();
			iter = m_Channel.erase(iter);
			break;
		}
		iter++;
	}
}

void cSoundManager::SetTimeSpeed()
{
	Sound* _Sound;
	float Pitch = min(SYSTEM->GetTimeSpeed(), 1);
	for (auto& iter = m_Channel.begin(); iter != m_Channel.end();)
	{
		(*iter)->getCurrentSound(&_Sound);
		if(!(_Sound == m_Sounds.find("PlayerShot")->second.Sound))
		(*iter)->setPitch(Pitch);
		iter++;
	}
}