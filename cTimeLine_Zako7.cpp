#include "DXUT.h"
#include "cTimeLine_Zako7.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako7::cTimeLine_Zako7(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako7::~cTimeLine_Zako7()
{
}

void cTimeLine_Zako7::Init()
{
	m_Time = 0;
	m_Dir = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_Circle11");
	m_Effect[0] = IMAGE->FindImage("Bullet_FireEffect6");
	m_Bullet[1] = IMAGE->FindImage("Bullet_LargeRing2");
	m_Effect[1] = IMAGE->FindImage("Bullet_FireEffect4");
	m_Bullet[2] = IMAGE->FindImage("Bullet_Rice7");
	m_Looped = 0;
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako7::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect[0], m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 106:
		{
			for (int i = 0; i < 360; i += 36)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 300, 150, 0.99, i + m_Dir, 5, m_Bullet[0]);
			}
			m_Dir += 5;

			if(OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			
			m_Owner->AddBullet(m_pObject->GetPosition(), 200, Dir + (rand() % 20) - 10, 4, m_Bullet[2]);
		} break;

		case 112:
		{
			m_Time = 99;
			m_Looped++;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();

	if (m_Looped == 60)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -50));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(25);
	}
}

void cTimeLine_Zako7::Render()
{

}

void cTimeLine_Zako7::Release()
{

}
