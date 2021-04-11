#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
	Release();
}

void cInputManager::Release()
{
}

void cInputManager::Update()
{
	if (SYSTEM->GetIsReplay() == false)
	{
		for (int i = 0; i < 128; i++)
		{
			m_LastKeys[i] = m_CurKeys[i];
			m_CurKeys[i] = false;
			if (GetAsyncKeyState(i) & 0x8000)
			{
				m_CurKeys[i] = true;
				m_InputDatas.push(InputData(m_Time, i, true));
			}

			if (KeyUp(i))
			{
				m_InputDatas.push(InputData(m_Time, i, false));
			}
		}
	}
	else
	{
		while (m_InputDatas.front().Time <= m_Time)
		{
			m_CurKeys[m_InputDatas.front().Key] = m_InputDatas.front().State;
			m_InputDatas.pop();
		}
	}
}

void cInputManager::Render()
{
}

bool cInputManager::KeyPress(int Key)
{
	return m_CurKeys[Key] && !m_LastKeys[Key];
}

bool cInputManager::KeyDown(int Key)
{
	return m_CurKeys[Key] && m_LastKeys[Key];
}

bool cInputManager::KeyUp(int Key)
{
	return !m_CurKeys[Key] && m_LastKeys[Key];
}