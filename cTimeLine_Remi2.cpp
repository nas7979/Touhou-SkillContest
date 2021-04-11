#include "DXUT.h"
#include "cTimeLine_Remi2.h"
#include "cItem.h"
#include "cRemi.h"
#include "cBullet_Remi2_1.h"
#include "cBulletFriction.h"

cTimeLine_Remi2::cTimeLine_Remi2(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Remi2::~cTimeLine_Remi2()
{
}

void cTimeLine_Remi2::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_LargeRing1");
	m_Owner = m_pObject->GetComponent<cRemi>();
	m_Dir = 0;
	m_Pattern = rand() % 3;
	m_Speed = 0.5;
}

void cTimeLine_Remi2::Update()
{
	if (m_Owner->GetHp() <= 0)
	{
		SetEnable(false);
		return;
	}
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 50:
		{
			SOUND->Play("Kira1");
			SOUND->Play("Power1");
			if (m_Pattern != 2)
			{
				for (int i = 0; i < 360; i += 20)
				{
					cObject * a = m_Owner->AddBullet(m_pObject->GetPosition(), 160, m_Dir + i, 15, m_Bullet);
					a->AddComponent<cBullet_Remi2_1>();
					a->GetComponent<cBullet_Remi2_1>()->SetPattern(m_Pattern);
				}
			}
			else
			{
				for (int i = 0; i < 360; i += 30)
				{
					for (int j = 0; j <= 10; j += 5)
					{
						cObject * a = m_Owner->AddBullet(m_pObject->GetPosition(), 160 + j * 5, m_Dir + i + j, 15, m_Bullet);
						a->AddComponent<cBullet_Remi2_1>();
						a->GetComponent<cBullet_Remi2_1>()->SetPattern(m_Pattern);
					}
				}
			}
		} break;

		case 210:
		{
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				cBulletFriction* Bullet = Obj->GetComponent<cBulletFriction>();
				if (Bullet)
				{
					if (Bullet->GetSpeed() == 0)
					{
						Bullet->SetSpeed(15);
					}
				}
			});
			cEffect* a = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
			EFFECT->AlphaSetting(a, 500, -17);
			EFFECT->SizeSetting(a, Vector2(0.25, 0.25));
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(200);
		} break;

		case 265:
		{
			m_Time = 49;
			m_Pattern = rand() % 3;
			if (m_Speed < 0.8)
			{
				m_Speed += 0.03;
			}
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += m_Speed * SYSTEM->GetTimeSpeed();
}

void cTimeLine_Remi2::Render()
{

}

void cTimeLine_Remi2::Release()
{

}
