#include "DXUT.h"
#include "cTimeLine_Zako3.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako3::cTimeLine_Zako3(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako3::~cTimeLine_Zako3()
{
}

void cTimeLine_Zako3::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Ring4");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect3");
	m_Dir = 0;
	m_Rotate = 1;
	m_Looped = 0;
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako3::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 110:
		case 120:
		case 130:
		case 140:
		case 150:
		case 160:
		case 170:
		{
			for (int i = 0; i < 360; i += 30)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 400, 150 + m_Dir, 0.9, i + m_Dir * m_Rotate, 5, m_Bullet);
			}
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			m_Dir += 5;
			break;
		}

		case 300:
		{
			m_Time = -1;
			m_Dir = 0;
			m_Looped++;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();

	if (m_Looped == 2)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(Vector2(m_pObject->GetPosition().x, 250), Vector2((m_Rotate == 1 ? -50 : 434), 250));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(30);
	}
}

void cTimeLine_Zako3::Render()
{

}

void cTimeLine_Zako3::Release()
{

}
