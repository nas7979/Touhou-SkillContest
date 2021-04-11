#include "DXUT.h"
#include "cTimeLine_Zako1.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako1::cTimeLine_Zako1(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako1::~cTimeLine_Zako1()
{
}

void cTimeLine_Zako1::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Ring7");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect4");
	m_Owner = m_pObject->GetComponent<cZako>();
	m_Looped = 0;
	if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
	else PlayerPos = Vector2(192, 480);
}

void cTimeLine_Zako1::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 0:
		{
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
		}
		case 20:
		case 40:
		{
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int i = -15; i <= 15; i += 15)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 600, 300, 0.95, Dir + i, 5, m_Bullet);
			}
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			break;
		}

		case 200:
		{
			m_Time = -1;
			m_Looped++;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
	if (m_Looped == 3)
	{
		m_Time = 1000;
		m_Looped++;
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -50));
		m_Owner->SetFriction(1.01);
		m_Owner->SetSpeed(30);
	}
}

void cTimeLine_Zako1::Render()
{

}

void cTimeLine_Zako1::Release()
{

}
