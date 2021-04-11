#include "DXUT.h"
#include "cTimeLine_Zako2.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako2::cTimeLine_Zako2(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako2::~cTimeLine_Zako2()
{
}

void cTimeLine_Zako2::Init()
{
	m_Time = 0;
	m_Dir = 0;
	m_Looped = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Ring3");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect2");
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako2::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 177:
		case 200:
		case 219:
		case 234:
		case 245:
		case 252:

		{
			for (int i = 0; i < 360; i += 20)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 400, 150, 0.9, i + m_Dir, 5, m_Bullet);
			}
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			m_Dir += 3;
			break;
		}
		case 189:
		case 210:
		case 227:
		case 240:
		case 249:
		case 254:
		{
			for (int i = 0; i < 360; i += 20)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 400, 150, 0.95, i + m_Dir, 5, m_Bullet);
			}
			m_Dir += 6;
			break;
		}

		case 300:
			m_Time = -1;
			m_Dir = 0;
			m_Looped++;
			break;

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();

	if (m_Looped == 2)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -50));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(25);
	}
}

void cTimeLine_Zako2::Render()
{

}

void cTimeLine_Zako2::Release()
{

}
