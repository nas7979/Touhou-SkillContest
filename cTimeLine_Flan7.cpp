#include "DXUT.h"
#include "cTimeLine_Flan7.h"
#include "cItem.h"
#include "cFlan.h"

cTimeLine_Flan7::cTimeLine_Flan7(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan7::~cTimeLine_Flan7()
{
}

void cTimeLine_Flan7::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice7");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect4");
	m_Owner = m_pObject->GetComponent<cFlan>();
}

void cTimeLine_Flan7::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		case 120:
		case 140:
		case 160:
		case 180:
		{
			SOUND->Play("BulletShot1");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(1, 1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			Vector2 PlayerPos;
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int j = 0; j < 6; j++)
			{
				for (int i = 0; i < 360; i += 72)
				{
					m_Owner->AddBullet(m_pObject->GetPosition(), 600, 400 - j * 50, 0.8, Dir + i, 4, m_Bullet);
				}
			}
		} break;

		case 190:
		{
			m_Time = 90;
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

void cTimeLine_Flan7::Render()
{

}

void cTimeLine_Flan7::Release()
{

}
