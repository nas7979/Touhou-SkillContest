#include "DXUT.h"
#include "cTimeLine_Zako8.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako8::cTimeLine_Zako8(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako8::~cTimeLine_Zako8()
{
}

void cTimeLine_Zako8::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Circle3");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect2");
	m_Dir = 0;
	m_Rotate = 0;
	m_Looped = 0;
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako8::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 106:
		case 112:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 102:
		case 104:
		case 108:
		case 110:
		{
			for (int i = 0; i < 360; i += 60)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 500, 50 + m_Dir * 6, 0.9, i + m_Dir + m_Rotate, 5, m_Bullet);
			}
			m_Dir += 3;
			break;
		}

		case 114:
		{
			m_Dir = 0;
			m_Rotate += 20;
		}
		case 120:
		case 126:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 116:
		case 118:
		case 122:
		case 124:
		{
			for (int i = 0; i < 360; i += 60)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 500, 50 - m_Dir * 6, 0.9, i + m_Dir + m_Rotate, 5, m_Bullet);
			}
			m_Dir -= 3;
			break;
		}

		case 128:
		{
			m_Time = 99;
			m_Dir = 0;
			m_Rotate += 2;
			m_Looped++;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();

	if (m_Looped == 12)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -50));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(25);
	}
}

void cTimeLine_Zako8::Render()
{

}

void cTimeLine_Zako8::Release()
{

}
