#pragma once
class cTimer;
class cAnimator : private cComponent
{
	friend class cObject;
	friend class cAnimation;
private:
	vector<texture*> m_Images;
	int m_CurrentFrame;
	cTimer* Timer = nullptr;
	string m_Key;
	bool m_Once;
	bool m_Paused;
	float m_Delay;
	float m_DefaultDelay;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cAnimator(cObject* Object, string ImageKey, float Delay, bool Once = false);
	~cAnimator();
};

