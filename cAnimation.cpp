#include "DXUT.h"
#include "cAnimation.h"
#include "cAnimator.h"

cAnimation::cAnimation(cObject* Object)
	:cComponent(Object)
{
}

cAnimation::~cAnimation()
{
}

void cAnimation::Init()
{
	PlaySpeed = 1 * SYSTEM->GetTimeSpeed();
}

void cAnimation::Update()
{
	if (m_CurrentAnimator)
	{
		m_CurrentAnimator->Update();
	}
}

void cAnimation::Render()
{
	
}

void cAnimation::Release()
{
	for (auto& iter = m_Animators.begin(); iter != m_Animators.end();)
	{
		(*iter).second->Release();
		SAFE_DELETE((*iter).second);
		iter++;
	}
	m_Animators.clear();
}

void cAnimation::SetPlaySpeed(float Speed)
{
	PlaySpeed = Speed * SYSTEM->GetTimeSpeed();
	if (!m_CurrentAnimator) return;
	m_CurrentAnimator->m_Delay = m_CurrentAnimator->m_DefaultDelay / PlaySpeed;
	m_CurrentAnimator->Timer->m_Time = abs(m_CurrentAnimator->m_Delay);
}

void cAnimation::SetCurrentFrame(int Frame)
{
	if (!m_CurrentAnimator) return;
	if (Frame > m_CurrentAnimator->m_Images.size() - 1) Frame = m_CurrentAnimator->m_Images.size() - 1;
	m_CurrentAnimator->m_CurrentFrame = Frame;
}

cAnimator* cAnimation::FindAnimator(string Key)
{
	auto iter = m_Animators.find(Key);
	if (iter != m_Animators.end()) return iter->second;
	return nullptr;
}

cAnimator* cAnimation::AddAnimator(string Key, string ImageKey, float Delay, bool Once)
{
	if (FindAnimator(Key)) return nullptr;

	cAnimator* Animator = new cAnimator(m_pObject, ImageKey, Delay, Once);
	Animator->m_Key = Key;
	m_Animators.insert(make_pair(Key, Animator));

	return Animator;
}

void cAnimation::SetCurrentAnimator(string Key)
{
	if (!FindAnimator(Key))
	{
		DEBUG_LOG("Animator dose not exist : " << Key.c_str());
	}
	m_CurrentAnimator = FindAnimator(Key);
	m_CurrentAnimator->Timer->m_CurTime = 0;
	m_CurrentAnimator->m_Paused = false;
	SetPlaySpeed(PlaySpeed);
}