#pragma once
#include "singleton.h"

struct InputData
{
	float Time;
	short Key;
	bool State;
	InputData(float _Time, short _Key, bool _State)
	{
		Time = _Time;
		Key = _Key;
		State = _State;
	}
};

class cInputManager : public singleton<cInputManager>
{
private:

	bool m_CurKeys[128];
	bool m_LastKeys[128];
	float m_Time;
	queue<InputData> m_InputDatas;

	void Release();
public:
	cInputManager();
	virtual ~cInputManager();

	void Update();
	void Render();

	bool KeyPress(int Key);
	bool KeyDown(int Key);
	bool KeyUp(int Key);
};

#define INPUT cInputManager::GetInstance()

