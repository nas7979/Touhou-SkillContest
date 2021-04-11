#include "DXUT.h"
#include "cTimeLine_Flan11.h"
#include "cItem.h"
#include "cFlan.h"
#include "cZako.h"
#include "cTimeLine_Flan11_Zako.h"
#include "cTimeLine_BossEffect.h"

cTimeLine_Flan11::cTimeLine_Flan11(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan11::~cTimeLine_Flan11()
{
}

void cTimeLine_Flan11::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_Circle3");
	m_Effect[0] = IMAGE->FindImage("Bullet_FireEffect2");
	m_Bullet[1] = IMAGE->FindImage("Bullet_Circle7");
	m_Effect[1] = IMAGE->FindImage("Bullet_FireEffect4");
	m_Bullet[2] = IMAGE->FindImage("Bullet_Circle11");
	m_Effect[2] = IMAGE->FindImage("Bullet_FireEffect6");
	m_Bullet[3] = IMAGE->FindImage("Bullet_Circle15");
	m_Effect[3] = IMAGE->FindImage("Bullet_FireEffect7");
	m_Bullet[4] = IMAGE->FindImage("Bullet_Circle14");
	m_Effect[4] = IMAGE->FindImage("Bullet_FireEffect7");
	m_Owner = m_pObject->GetComponent<cFlan>();
	m_pObject->GetComponent<cCircleCollider>()->SetEnable(false);
	m_pObject->GetComponent<cTimeLine_BossEffect>()->SetEnable(false);
	m_pObject->SetTag(Tag::None);
}

void cTimeLine_Flan11::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			m_pObject->GetComponent<cRenderer>()->SetEnable(false);
			cObject* a = OBJECT->Create("Zako1", Vector2(192, 120), 0, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(1);
			a->AddComponent<cTimeLine_Flan11_Zako>();
		} break;

		case 900:
		{
			cObject* a = OBJECT->Create("Zako1", Vector2(0, 0), 0, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(1);
			a->AddComponent<cTimeLine_Flan11_Zako>();
		} break;

		case 960:
		{
			cObject* a = OBJECT->Create("Zako1", Vector2(384, 0), 0, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(1);
			a->AddComponent<cTimeLine_Flan11_Zako>();
		} break;

		case 1020:
		{
			cObject* a = OBJECT->Create("Zako1", Vector2(0, 480), 0, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(1);
			a->AddComponent<cTimeLine_Flan11_Zako>();
		} break;

		case 1080:
		{
			cObject* a = OBJECT->Create("Zako1", Vector2(384, 480), 0, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(1);
			a->AddComponent<cTimeLine_Flan11_Zako>();
		} break;

		case 1800:
		{
			OBJECT->With("Zako", [&](cObject* Obj)->void
			{
				Obj->Destroy();
			});
		} break;

		case 1900:
		case 3390:
		case 4650:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(0, i * 43), 80 - abs(i - 6) * 1.5, D3DXToDegree(atan2(240 - i * 43, 192)), 5, m_Bullet[0]);
				cEffect* a = EFFECT->Create(m_Effect[0], Vector2(0, i * 43), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(384, i * 43), 80 - abs(i - 6) * 1.5, D3DXToDegree(atan2(240 - i * 43, -192)), 5, m_Bullet[0]);
				cEffect* a = EFFECT->Create(m_Effect[0], Vector2(384, i * 43), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(i * 42, 0), 80 - abs(i - 5) * 1.5, D3DXToDegree(atan2(240, 192 - i * 42)), 5, m_Bullet[0]);
				cEffect* a = EFFECT->Create(m_Effect[0], Vector2(i * 42, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(i * 42, 480), 80 - abs(i - 5) * 1.5, D3DXToDegree(atan2(-240, 192 - i * 42)), 5, m_Bullet[0]);
				cEffect* a = EFFECT->Create(m_Effect[0], Vector2(i * 42, 480), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
		} break;

		case 2200:
		case 3670:
		case 4750:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(0, 16 + i * 47), 70, 0, 5, m_Bullet[1]);
				m_Owner->AddBullet(Vector2(0, 16 + i * 47), 90, 0, 5, m_Bullet[1]);
				cEffect* a = EFFECT->Create(m_Effect[1], Vector2(0, 16 + i * 47), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(384, 30 + i * 47), 70, 180, 5, m_Bullet[1]);
				m_Owner->AddBullet(Vector2(384, 30 + i * 47), 90, 180, 5, m_Bullet[1]);
				cEffect* a = EFFECT->Create(m_Effect[1], Vector2(384, 30 + i * 47), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 9; i++)
			{
				m_Owner->AddBullet(Vector2(10 + i * 44, 0), 65, 90, 5, m_Bullet[1]);
				m_Owner->AddBullet(Vector2(10 + i * 44, 0), 85, 90, 5, m_Bullet[1]);
				cEffect* a = EFFECT->Create(m_Effect[1], Vector2(10 + i * 44, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 9; i++)
			{
				m_Owner->AddBullet(Vector2(24 + i * 44, 480), 65, 270, 5, m_Bullet[1]);
				m_Owner->AddBullet(Vector2(24 + i * 44, 480), 85, 270, 5, m_Bullet[1]);
				cEffect* a = EFFECT->Create(m_Effect[1], Vector2(24 + i * 44, 480), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
		} break;

		case 2500:
		case 3940:
		case 4850:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(0, 0 + i * 47), 75, -10, 5, m_Bullet[2]);
				m_Owner->AddBullet(Vector2(0, 16 + i * 47), 75, 10, 5, m_Bullet[2]);
				cEffect* a = EFFECT->Create(m_Effect[2], Vector2(0, 8 + i * 47), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 10; i++)
			{
				m_Owner->AddBullet(Vector2(384, 16 + i * 47), 75, 170, 5, m_Bullet[2]);
				m_Owner->AddBullet(Vector2(384, 32 + i * 47), 75, 190, 5, m_Bullet[2]);
				cEffect* a = EFFECT->Create(m_Effect[2], Vector2(384, 24 + i * 47), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 9; i++)
			{
				m_Owner->AddBullet(Vector2(0 + i * 44, 0), 70, 80, 5, m_Bullet[2]);
				m_Owner->AddBullet(Vector2(16 + i * 44, 0), 70, 100, 5, m_Bullet[2]);
				cEffect* a = EFFECT->Create(m_Effect[2], Vector2(8 + i * 44, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 9; i++)
			{
				m_Owner->AddBullet(Vector2(16 + i * 44, 480), 70, 260, 5, m_Bullet[2]);
				m_Owner->AddBullet(Vector2(32 + i * 44, 480), 70, 280, 5, m_Bullet[2]);
				cEffect* a = EFFECT->Create(m_Effect[2], Vector2(24 + i * 44, 480), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
		} break;

		case 2800:
		case 4200:
		case 4950:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 14; i++)
			{
				m_Owner->AddBullet(Vector2(0, i * 35), 100 - i * 4, 0, 5, m_Bullet[3]);
				cEffect* a = EFFECT->Create(m_Effect[3], Vector2(0, i * 35), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 14; i++)
			{
				m_Owner->AddBullet(Vector2(384, 464 - i * 35), 100 - i * 4, 180, 5, m_Bullet[3]);
				cEffect* a = EFFECT->Create(m_Effect[3], Vector2(0, 464 - i * 35), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(i * 33, 0), 90 - i * 4, 90, 5, m_Bullet[3]);
				cEffect* a = EFFECT->Create(m_Effect[3], Vector2(i * 33, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(364 - i * 33, 480), 90 - i * 4, 270, 5, m_Bullet[3]);
				cEffect* a = EFFECT->Create(m_Effect[3], Vector2(364 - i * 33, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
		} break;

		case 3100:
		case 4450:
		case 5050:
		{
			SOUND->Play("BulletShot1");
			for (int i = 0; i < 14; i++)
			{
				m_Owner->AddBullet(Vector2(384, i * 35), 100 - i * 4, 180, 5, m_Bullet[4]);
				cEffect* a = EFFECT->Create(m_Effect[4], Vector2(0, i * 35), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 14; i++)
			{
				m_Owner->AddBullet(Vector2(0, 464 - i * 35), 100 - i * 4, 0, 5, m_Bullet[4]);
				cEffect* a = EFFECT->Create(m_Effect[4], Vector2(0, 464 - i * 35), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(i * 33, 480), 90 - i * 4, 270, 5, m_Bullet[4]);
				cEffect* a = EFFECT->Create(m_Effect[4], Vector2(i * 33, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
			for (int i = 0; i < 12; i++)
			{
				m_Owner->AddBullet(Vector2(364 - i * 33, 0), 90 - i * 4, 90, 5, m_Bullet[4]);
				cEffect* a = EFFECT->Create(m_Effect[4], Vector2(364 - i * 33, 0), Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
			}
		} break;

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Flan11::Render()
{

}

void cTimeLine_Flan11::Release()
{

}
