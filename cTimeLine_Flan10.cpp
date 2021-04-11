#include "DXUT.h"
#include "cTimeLine_Flan10.h"
#include "cItem.h"
#include "cFlan.h"
#include "cTimeLine_BossPower.h"
#include "cBullet_Bounce.h"

cTimeLine_Flan10::cTimeLine_Flan10(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan10::~cTimeLine_Flan10()
{
}

void cTimeLine_Flan10::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_LargeRing2");
	m_Bullet[1] = IMAGE->FindImage("Bullet_LargeCircle4");
	m_Bullet[2] = IMAGE->FindImage("Bullet_Ring6");
	m_Owner = m_pObject->GetComponent<cFlan>();
}

void cTimeLine_Flan10::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			m_pObject->GetComponent<cTimeLine_BossPower>()->SetEnable(true);
		} break;

		case 160:
		{
			SOUND->Play("BulletShot2");
			for (int i = 224; i <= 316; i += 23)
			{
				cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 250, i, 15, m_Bullet[0]);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, true);
				for (int j = 0; j < 8; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 230 - j * 10, i + (rand() % 4) - 2, 15, m_Bullet[1]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, true);
				}
				for (int j = 0; j < 15; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 150 - j * 5, i + (rand() % 6) - 3, 15, m_Bullet[2]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, true);
				}
			}
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 150));
			m_Owner->SetFriction(0.8);
			m_Owner->SetSpeed(600);
		} break;

		case 230:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(300, 120));
			m_Owner->SetFriction(0.98);
			m_Owner->SetSpeed(200);
		} break;

		case 300:
		{
			SOUND->Play("BulletShot2");
			for (int i = 314; i <= 406; i += 23)
			{
				cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 250, i, 15, m_Bullet[0]);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, false, false, true);
				for (int j = 0; j < 8; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 230 - j * 10, i + (rand() % 4) - 2, 15, m_Bullet[1]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, false, false, true);
				}
				for (int j = 0; j < 15; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 150 - j * 5, i + (rand() % 6) - 3, 15, m_Bullet[2]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, false, false, true);
				}
			}
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(270, 120));
			m_Owner->SetFriction(0.8);
			m_Owner->SetSpeed(600);
		} break;

		case 360:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(84, 120));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(300);
		} break;

		case 430:
		{
			SOUND->Play("BulletShot2");
			for (int i = 134; i <= 226; i += 23)
			{
				cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 250, i, 15, m_Bullet[0]);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
				for (int j = 0; j < 8; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 230 - j * 10, i + (rand() % 4) - 2, 15, m_Bullet[1]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
				}
				for (int j = 0; j < 15; j++)
				{
					cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 150 - j * 5, i + (rand() % 6) - 3, 15, m_Bullet[2]);
					a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
				}
			}
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(114, 120));
			m_Owner->SetFriction(0.8);
			m_Owner->SetSpeed(600);
		} break;

		case 490:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(32, 150));
			m_Owner->SetFriction(0.97);
			m_Owner->SetSpeed(200);
		} break;

		case 560:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(352, 150));
			m_Owner->SetFriction(1);
			m_Owner->SetSpeed(175);
		}

		case 585:
		case 610:
		case 635:
		case 660:
		{
			SOUND->Play("BulletShot2");
			cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 250, 270, 15, m_Bullet[0]);
			a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
			for (int j = 0; j < 8; j++)
			{
				cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 230 - j * 10, 270 + (rand() % 4) - 2, 15, m_Bullet[1]);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
			}
			for (int j = 0; j < 15; j++)
			{
				cObject* a = m_Owner->AddBullet(m_pObject->GetPosition(), 150 - j * 5, 270 + (rand() % 6) - 3, 15, m_Bullet[2]);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, false);
			}
		} break;

		case 700:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 120));
			m_Owner->SetFriction(0.98);
			m_Owner->SetSpeed(250);
			m_Time = 20;
		} break;

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Flan10::Render()
{

}

void cTimeLine_Flan10::Release()
{

}
