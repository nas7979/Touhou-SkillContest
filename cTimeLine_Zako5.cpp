#include "DXUT.h"
#include "cTimeLine_Zako5.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako5::cTimeLine_Zako5(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako5::~cTimeLine_Zako5()
{
}

void cTimeLine_Zako5::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Circle9");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect5");
	m_Dir = 0;
	m_Rotate = 0;
	m_Looped = 0;
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako5::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 109:
		case 118:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 103:
		case 106:
		case 112:
		case 115:
		{
			for (int i = 0; i < 360; i += 45)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 230, 130 + m_Dir * 5, 0.98, i + m_Dir + m_Rotate, 5, m_Bullet);
			}
			m_Dir += 3;
			break;
		}

		case 121:
		{
			m_Dir = 0;
			m_Rotate += 5;
		}
		case 130:
		case 139:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 124:
		case 127:
		case 133:
		case 136:
		{
			for (int i = 0; i < 360; i += 45)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 230, 130 - m_Dir * 5, 0.98, i + m_Dir + m_Rotate, 5, m_Bullet);
			}
			m_Dir -= 3;
			break;
		}

		case 141:
		{
			m_Time = 99;
			m_Dir = 0;
			m_Rotate += 5;
			m_Looped++;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();

	if (m_Looped == 6)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -50));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(25);
	}
}

void cTimeLine_Zako5::Render()
{

}

void cTimeLine_Zako5::Release()
{

}
