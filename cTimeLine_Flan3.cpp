#include "DXUT.h"
#include "cTimeLine_Flan3.h"
#include "cItem.h"
#include "cFlan.h"

cTimeLine_Flan3::cTimeLine_Flan3(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan3::~cTimeLine_Flan3()
{
}

void cTimeLine_Flan3::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice3");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect2");
	m_Owner = m_pObject->GetComponent<cFlan>();
}

void cTimeLine_Flan3::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 130:
		case 160:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(1, 1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			for (int i = 0; i < 360; i += 6)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 600, 105, 0.8, i, 4, m_Bullet);
			}
			for (int i = 0; i < 360; i += 6)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 600, 130, 0.8, i, 4, m_Bullet);
			}
		} break;

		case 170:
		{
			m_Time = 80;
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(200);
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Flan3::Render()
{

}

void cTimeLine_Flan3::Release()
{

}
