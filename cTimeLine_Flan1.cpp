#include "DXUT.h"
#include "cTimeLine_Flan1.h"
#include "cItem.h"
#include "cFlan.h"

cTimeLine_Flan1::cTimeLine_Flan1(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan1::~cTimeLine_Flan1()
{
}

void cTimeLine_Flan1::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice3");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect2");
	m_Owner = m_pObject->GetComponent<cFlan>();
	m_Music = false;
}

void cTimeLine_Flan1::Update()
{
	if (m_Music == false && m_Last == 60)
	{
		SOUND->End("Field_Thema");
		SOUND->End("Remi_Thema");
		SOUND->Play("Flan_Thema", true);
		m_Music = true;
	}
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 150:
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

		case 180:
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

void cTimeLine_Flan1::Render()
{

}

void cTimeLine_Flan1::Release()
{

}
