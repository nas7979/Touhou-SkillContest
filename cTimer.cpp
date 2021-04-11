#include "DXUT.h"
#include "cTimer.h"


cTimer::cTimer(float Time, function<void()> Func, bool Loop)
	:m_Time(Time), m_Func(Func), m_Loop(Loop)
{
	m_CurTime = 0;
}

cTimer::~cTimer()
{
}

void cTimer::Update()
{
	m_CurTime++;
	if (m_CurTime >= m_Time)
	{
		m_Func();
		if (m_Loop)
		{
			m_CurTime = 0;
		}
		else
		{
			delete this;
		}
	}
}