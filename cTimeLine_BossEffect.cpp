#include "DXUT.h"
#include "cTimeLine_BossEffect.h"
#include "cItem.h"

cTimeLine_BossEffect::cTimeLine_BossEffect(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_BossEffect::~cTimeLine_BossEffect()
{
}

void cTimeLine_BossEffect::Init()
{
	m_Time = 0;
	m_Dir = 0.8;
	m_Pos = 20;
}

void cTimeLine_BossEffect::Update()
{
	if (m_Dir >= 2.1) m_Dir = 0.8;
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 0:
		case 4:
		case 8:
		case 12:
		case 16:
		case 20:
		{
			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 5; i++)
				{
					char Name[12];
					sprintf(Name, "BossEffect%d", (rand() % 4) + 1);
					cEffect* a = EFFECT->Create(string(Name), m_pObject->GetPosition() + Vector2(m_Pos * cos(m_Dir - 1.570796),m_Pos * sin(m_Dir - 1.570796)) + Vector2((rand() % 20) - 10, (rand() % 20) - 10), Vector2(3 - m_Pos * 0.016, 3 - m_Pos * 0.016), 10);
					EFFECT->AlphaSetting(a, (rand() % 100) + 50, -((rand() % 5) + 2));
					EFFECT->MovementSetting(a, (rand() % 20) + 20, 90, 1.03, 0);
					m_Pos += 2;
				}
				m_Dir *= -1;
			}
			m_Dir -= m_Pos / 2500;
		} break;

		case 24:
		{
			m_Pos = 20;
			m_Dir += 0.36;
			m_Time = -1;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_BossEffect::Render()
{

}

void cTimeLine_BossEffect::Release()
{

}
