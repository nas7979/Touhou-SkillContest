#include "DXUT.h"
#include "cTimeLine_Remi1.h"
#include "cItem.h"
#include "cRemi.h"

cTimeLine_Remi1::cTimeLine_Remi1(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Remi1::~cTimeLine_Remi1()
{
}

void cTimeLine_Remi1::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_LargeCircle4");
	m_Bullet[1] = IMAGE->FindImage("Bullet_Circle6");
	m_Bullet[2] = IMAGE->FindImage("Bullet_LargeRing1");
	m_Owner = m_pObject->GetComponent<cRemi>();
	m_Dir = 0;
}

void cTimeLine_Remi1::Update()
{
	if (m_Owner->GetPhase() != 2)
	{
		SetEnable(false);
		return;
	}
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 99:
		{
			SOUND->End("Field_Thema");
			SOUND->Play("Remi_Thema");
		} break;

		case 100:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 360; i += 45)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 180, m_Dir + i, 12, m_Bullet[0]);
			}
			Vector2 PlayerPos;
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int i = -2; i <= 2; i++)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 150 - abs(i * 4), Dir + i * 15, 5, m_Bullet[1]);
			}
			for (int i = 0; i < 360; i += 72)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 220, m_Dir * 1.2 + i, 15, m_Bullet[2]);
			}
			m_Dir += 11;
		} break;

		case 108:
		{
			for (int i = 0; i < 360; i += 45)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 180, m_Dir + i, 12, m_Bullet[0]);
			}
			m_Dir += 11;
		} break;

		case 116:
		{
			m_Time = 99;
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
	if ((int)m_Dir % 300 >= 290)
	{
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
		m_Owner->SetFriction(0.985);
		m_Owner->SetSpeed(200);
	}
}

void cTimeLine_Remi1::Render()
{

}

void cTimeLine_Remi1::Release()
{

}
