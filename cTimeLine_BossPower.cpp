#include "DXUT.h"
#include "cTimeLine_BossPower.h"
#include "cItem.h"

cTimeLine_BossPower::cTimeLine_BossPower(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_BossPower::~cTimeLine_BossPower()
{
}

void cTimeLine_BossPower::Init()
{
	m_Time = 0;
}

void cTimeLine_BossPower::Update()
{
	for (int i = 0; i < 6; i++)
	{
		char Name[12];
		sprintf(Name, "BossEffect%d", (rand() % 4) + 1);
		float Dir = D3DXToRadian(rand() % 360);
		Vector2 Pos = m_pObject->GetPosition() + Vector2((200 + (rand() % 50)) * cos(Dir), (200 + (rand() % 50)) * sin(Dir));
		Vector2 Size = Vector2(10, 10);
		cEffect* a = EFFECT->Create(string(Name), Pos, Size, -10);
		EFFECT->AlphaSetting(a, 1, ((rand() % 2) + 1));
		EFFECT->MovementSetting(a, 100, D3DXToDegree(atan2(m_pObject->GetPosition().y - Pos.y, m_pObject->GetPosition().x - Pos.x)), 1.03, 0);
		EFFECT->SizeSetting(a, -(Size * 0.02));
	}
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 1:
		{
			SOUND->Play("Power1");
		} break;
		case 100:
		{
			m_Time = -1;
			SetEnable(false);
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_BossPower::Render()
{

}

void cTimeLine_BossPower::Release()
{

}
