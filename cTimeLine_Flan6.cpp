#include "DXUT.h"
#include "cTimeLine_Flan6.h"
#include "cItem.h"
#include "cFlan.h"
#include "cZako.h"
#include "cTimeLine_BossPower.h"

cTimeLine_Flan6::cTimeLine_Flan6(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan6::~cTimeLine_Flan6()
{
}

void cTimeLine_Flan6::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_Rice3");
	m_Bullet[1] = IMAGE->FindImage("Bullet_LargeCircle4");
	m_Bullet[2] = IMAGE->FindImage("Bullet_LargeCircle7");
	m_Bullet[3] = IMAGE->FindImage("Bullet_LargeCircle6");
	m_Timing = 0;
	m_Pattern = 0;
	m_OnAttack = false;
	if (m_pObject->GetComponent<cFlan>())
	{
		m_Owner = m_pObject->GetComponent<cFlan>();
	}
	else
	{
		m_Owner_Zako = m_pObject->GetComponent<cZako>();
	}
}

void cTimeLine_Flan6::Update()
{
	if (m_Last != (int)m_Time)
	{
		if (m_Pattern == 0)
		{
			switch ((int)m_Time)
			{
			case 100:
			{
				m_pObject->GetComponent<cTimeLine_BossPower>()->SetEnable(true);
			} break;

			case 200:
			{
				m_Timing = 0;
				m_OnAttack = true;
				m_pObject->GetComponent<cPath>()->Clear();
				m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(150, 150));
				m_Owner->SetFriction(0.985);
				m_Owner->SetSpeed(150);
				cObject* a = OBJECT->Create("Flan", Vector2(-16, 150), -5, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(5000);
				a->GetComponent<cZako>()->AddDrop("Item3");
				a->GetComponent<cZako>()->SetSpeed(300);
				a->GetComponent<cZako>()->SetFriction(0.98);
				a->AddComponent<cTimeLine_Flan6>()->SetPattern(1);
				a->GetComponent<cTimeLine_Flan6>()->SetOnAttack(true);
				a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(96, 150));
				a = OBJECT->Create("Flan", Vector2(234, -16), -5, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(5000);
				a->GetComponent<cZako>()->AddDrop("Item3");
				a->GetComponent<cZako>()->SetSpeed(300);
				a->GetComponent<cZako>()->SetFriction(0.98);
				a->AddComponent<cTimeLine_Flan6>()->SetPattern(2);
				a->GetComponent<cTimeLine_Flan6>()->SetOnAttack(true);
				a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(234, 150));
				a = OBJECT->Create("Flan", Vector2(400, 150), -5, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(5000);
				a->GetComponent<cZako>()->AddDrop("Item3");
				a->GetComponent<cZako>()->SetSpeed(300);
				a->GetComponent<cZako>()->SetFriction(0.98);
				a->AddComponent<cTimeLine_Flan6>()->SetPattern(3);
				a->GetComponent<cTimeLine_Flan6>()->SetOnAttack(true);
				a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(288, 150));
			} break;

			case 300:
			{

				break;
			}

			}
		}
	}
	float m_TimeSpeed = SYSTEM->GetTimeSpeed();
	m_Last = (int)m_Time;
	m_Time += m_TimeSpeed;
	m_Timing += (1 - (rand() % 100) * 0.005) * m_TimeSpeed;
	if (rand() % 200 == 1 && m_OnAttack)
	{
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
		if (m_Pattern == 0)
		{
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(200);
		}
		else
		{
			m_Owner_Zako->SetFriction(0.985);
			m_Owner_Zako->SetSpeed(200);
		}
	}

	if (rand() % 500 == 250 && m_OnAttack)
	{
		if (m_Pattern == 1)
		{
			Vector2 PlayerPos;
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x)) + 6;
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 360; i += 12)
				{
					m_Owner_Zako->AddBullet(m_pObject->GetPosition(), 200, 200 - j * 50, 0.9, Dir + i, 12, m_Bullet[1]);
				}
			}
		}
		if (m_Pattern == 2)
		{
			for (int j = 0; j < 10; j++)
			{
				for (int i = 0; i < 360; i += 45)
				{
					m_Owner_Zako->AddBullet(m_pObject->GetPosition(), 220, 220 - j * 16, 0.9, i, 12, m_Bullet[2]);
				}
			}
		}
		if (m_Pattern == 3)
		{
			Vector2 PlayerPos;
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int j = 0; j < 5; j++)
			{
				for (int i = -45; i <= 45; i += 15)
				{
					m_Owner_Zako->AddBullet(m_pObject->GetPosition(), 220, 220 - j * 30, 0.9, Dir + i, 12, m_Bullet[3]);
				}
			}
		}
	}

	if ((int)m_Timing == 40 && m_OnAttack)
	{
		m_Timing = 0;
		SOUND->Play("BulletShot1", 0.6f);
		if (m_Pattern == 0)
		{
			for (int i = 0; i < 360; i += 12)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 500, 150, 0.75, i, 4, m_Bullet[0]);
			}
		}
		else
		{
			for (int i = 0; i < 360; i += 12)
			{
				m_Owner_Zako->AddBullet(m_pObject->GetPosition(), 500, 150, 0.75, i, 4, m_Bullet[0]);
			}
		}
	}
}

void cTimeLine_Flan6::Render()
{

}

void cTimeLine_Flan6::Release()
{

}
