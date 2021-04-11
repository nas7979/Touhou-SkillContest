#pragma once
class cTimer
{
	friend class cAnimation;
private:
	float m_Time;
	float m_CurTime;
	function<void()> m_Func;
	bool m_Loop;
public:
	cTimer(float Time, function<void()> Func, bool Loop = false);
	~cTimer();
	void Update();
};

