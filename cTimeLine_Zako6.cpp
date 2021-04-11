#include "DXUT.h"
#include "cTimeLine_Zako6.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako6::cTimeLine_Zako6(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako6::~cTimeLine_Zako6()
{
}

void cTimeLine_Zako6::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice4");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect3");
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako6::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 10:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			int m_Dir = rand() % 60;
			for (int i = 0; i < 360; i += 40)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 150, i + m_Dir, 4, m_Bullet);
			}
		}

		case 30:
		{
			m_Time = 0;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Zako6::Render()
{

}

void cTimeLine_Zako6::Release()
{

}
