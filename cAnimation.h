#pragma once
#include "cAnimator.h"
class cAnimator;
class cAnimation : public cComponent
{
	friend class cObject;
private:
	map<string, cAnimator*> m_Animators;
	cAnimator* m_CurrentAnimator = nullptr;
	float PlaySpeed;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cAnimation(cObject* Object);
	~cAnimation();

	string GetCurrentAnimatorKey()
	{
		return m_CurrentAnimator->m_Key;
	}

	float GetPlaySpeed()
	{
		return PlaySpeed;
	}
	void SetPlaySpeed(float Speed);
	
	int GetCurrentFrame()
	{
		if (!m_CurrentAnimator) return 0;
		return m_CurrentAnimator->m_CurrentFrame;
	}
	void SetCurrentFrame(int Frame);

	bool GetPaused()
	{
		return m_CurrentAnimator->m_Paused;
	}
	void SetPaused(bool Pause)
	{
		m_CurrentAnimator->m_Paused = Pause;
	}


	cAnimator* FindAnimator(string Key);
	cAnimator* AddAnimator(string Key, string ImageKey, float Delay, bool Once = false);
	void SetCurrentAnimator(string Key);
};

