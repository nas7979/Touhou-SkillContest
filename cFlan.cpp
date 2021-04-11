#include "DXUT.h"
#include "cFlan.h"
#include "cBullet.h"
#include "cBulletFriction.h"
#include "cBulletToPos.h"
#include "cItem.h"
#include "cTimeLine_BossEffect.h"
#include "cTimeLine_BossDeath.h"
#include "cTimeLine_BossPower.h"
#include "cTimeLine_Flan1.h"
#include "cTimeLine_Flan2.h"
#include "cTimeLine_Flan3.h"
#include "cTimeLine_Flan4.h"
#include "cTimeLine_Flan5.h"
#include "cTimeLine_Flan6.h"
#include "cTimeLine_Flan7.h"
#include "cTimeLine_Flan8.h"
#include "cTimeLine_Flan9.h"
#include "cTimeLine_Flan10.h"
#include "cTimeLine_Flan11.h"
#include "cTimeLine_Flan12.h"
#include "cFace.h"
#include "cZako.h"

cFlan::cFlan(cObject* Object)
	:cComponent(Object)
{
}


cFlan::~cFlan()
{
}

void cFlan::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_pObject->AddComponent<cAnimation>();
	m_pObject->AddComponent<cPath>();
	m_pObject->AddComponent<cTimeLine_BossEffect>();
	m_pObject->AddComponent<cTimeLine_BossPower>()->SetEnable(false);
	m_pObject->AddComponent<cTimeLine_Flan1>();

	m_pObject->GetComponent<cAnimation>()->AddAnimator("Idle", "Flan_Idle", 6);
	m_pObject->GetComponent<cAnimation>()->AddAnimator("Move", "Flan_Move", 10, true);
	m_pObject->GetComponent<cAnimation>()->SetCurrentAnimator("Move");
	m_pObject->GetComponent<cAnimation>()->SetCurrentFrame(2);

	m_pObject->GetComponent<cCircleCollider>()->AddListName("PlayerBullet");
	m_pObject->GetComponent<cCircleCollider>()->SetRadius(25);
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void {
		if (Other->GetName() == "PlayerBullet")
		{
			if (Other->GetComponent<cBulletToPos>() != nullptr)
			{
				m_Hp -= max(1, Other->GetComponent<cBulletToPos>()->GetDamage() * m_Armor);
			}
			else
			{
				m_Hp -= max(1, Other->GetComponent<cBullet>()->GetDamage() * m_Armor);
			}
			int Rand = 30 - (rand() & 60);
			cEffect* a = EFFECT->Create("BulletHit", m_pObject->GetPosition() + Vector2(-16 * cos(Other->GetRotate() - 1.570796), -16 * sin(Other->GetRotate() - 1.570796)), Vector2(0.2, 2), -5);
			EFFECT->MovementSetting(a, 350, D3DXToDegree(Other->GetRotate()) - Rand - 90, 1, Other->GetRotate() + (Rand >= 0 ? 0 : 3.141592));
			EFFECT->SizeSetting(a, Vector2(0.1, -0.1));
			EFFECT->AlphaSetting(a, 200, -10);
			Other->Destroy();

			char Name[7];
			sprintf(Name, "Graze%d", (rand() % 4) + 1);
			a = EFFECT->Create(string(Name), m_pObject->GetPosition(), Vector2(0.5, 0.5), 10);
			EFFECT->AlphaSetting(a, 200, -10);
			EFFECT->MovementSetting(a, 300 + (rand() % 100), rand() % 360, 0.94, 0);
			SYSTEM->AddScore(50);
		}
	});

	m_Friction = 0.965;
	m_Speed = 350;
	m_Hp = 11000;
	m_Armor = 1;
	m_MaxHp = 11000;
	m_Phase = 14;
	m_TimeLeft = 30;
	m_LastTime = 30;
	m_SpellBonus = 3000000;
	OBJECT->SetBoss(m_pObject);
	m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 120));
	m_Texture_Circle = IMAGE->FindImage("Enemy_Circle");
}

void cFlan::Update()
{
	if (m_LastTime != (int)m_TimeLeft && m_LastTime < 10)
	{
		SOUND->Play("TimeOut");
	}
	m_LastTime = (int)m_TimeLeft;
	m_TimeLeft -= 0.0166666666666667;
	if (m_TimeLeft <= 0)
	{
		if (m_Phase == 3)
		{
			m_pObject->GetComponent<cRenderer>()->SetEnable(true);
			m_pObject->GetComponent<cCircleCollider>()->SetEnable(true);
			m_pObject->SetTag(Tag::Enemy);
			m_Hp = 0;
		}
		else if (m_Phase % 2 == 0)
		{
			m_Phase--;
			m_Hp = 2000;
			Spell();
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
			});
		}
		else
		{
			m_Phase--;
			m_Hp = 11000;
			EndSpell();
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
			});
			OBJECT->With("Face", [&](cObject* Obj)->void {
				if (Obj->GetComponent<cFace>()->GetIsEnemy())
				{
					Obj->Destroy();
				}
			});
		}
	}

	if (m_Hp <= 2000)
	{
		if (m_Phase % 2 == 0)
		{
			m_Phase--;
			Spell();
			m_SpellBonus = 3000000;
			if (m_TimeLeft > 0)
			{
				OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
					Obj->Destroy();
					cObject* a = OBJECT->Create("Item5", Obj->GetPosition(), -11, Tag::Item);
					a->AddComponent<cItem>()->SetCollect(true);
				});
			}
			else
			{
				OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
					Obj->Destroy();
				});
			}

			cObject* a = OBJECT->Create("Item3", m_pObject->GetPosition() + Vector2((rand() % 200) - 100, (rand() % 200) - 100), -2, Tag::Item);
			a->AddComponent<cItem>();
			for (int i = 0; i < 11; i++)
			{
				a = OBJECT->Create("Item1", m_pObject->GetPosition() + Vector2((rand() % 200) - 100, (rand() % 200) - 100), -2, Tag::Item);
				a->AddComponent<cItem>();
			}
		}
	}
	if (m_Hp <= 0)
	{
		if (m_Phase != 1)
		{
			m_Phase--;
			m_Hp = 11000;
			EndSpell();
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
				cObject* a = OBJECT->Create("Item5", Obj->GetPosition(), -11, Tag::Item);
				a->AddComponent<cItem>()->SetCollect(true);
			});
			cObject* a = OBJECT->Create("Item3", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, (rand() % 150) - 75), -2, Tag::Item);
			a->AddComponent<cItem>();
			a->AddComponent<cItem>();
			for (int i = 0; i < 11; i++)
			{
				a = OBJECT->Create("Item1", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, (rand() % 150) - 75), -2, Tag::Item);
				a->AddComponent<cItem>();
			}
			if (SYSTEM->GetBonus())
			{
				SYSTEM->AddScore(m_SpellBonus);
				SYSTEM->AddBonusCount(1);
				cEffect* b = EFFECT->Create(IMAGE->FindImage("SpellBonus"), Vector2(192, 75), Vector2(1, 1), -20);
				EFFECT->AlphaSetting(b, 6000, -50);
				b = EFFECT->Create(IMAGE->FindImage("+"), Vector2(80, 100), Vector2(2, 2), -20);
				EFFECT->AlphaSetting(b, 6000, -50);
				EFFECT->ColorSetting(b, 255, 100, 100);
				char _Num[8];
				sprintf(_Num, "%d", m_SpellBonus);
				string _Text = string(_Num);
				for (int i = 0; i < 7; i++)
				{
					char Text[2] = { _Text[i],NULL };
					b = EFFECT->Create(IMAGE->FindImage(&Text[0]), Vector2(112 + i * 32, 100), Vector2(2, 2), -20);
					EFFECT->AlphaSetting(b, 6000, -50);
					EFFECT->ColorSetting(b, 255, 100, 100);
				}
			}
			if (m_Phase == 2) m_SpellBonus = 5000000;
		}
		else
		{
			m_pObject->AddComponent < cTimeLine_BossDeath>();
		}
	}
	if(m_SpellBonus > 0 && m_SpellBonus != 5000000) m_SpellBonus -= 300;
	else m_SpellBonus = 0;
	m_Speed *= m_Friction;

	m_pObject->GetComponent<cPath>()->SetSpeed(m_Speed);
	cAnimation* Anim = m_pObject->GetComponent<cAnimation>();
	if (Anim->GetCurrentAnimatorKey() == "Move" && (m_Speed < 10 || m_pObject->GetComponent<cPath>()->GetNextPoint() == m_pObject->GetComponent<cPath>()->GetPointsSize() - 1))
	{
		Anim->SetPlaySpeed(-1);
		Anim->SetPaused(false);
		if (Anim->GetCurrentFrame() == 0)
		{
			Anim->SetCurrentAnimator("Idle");
			Anim->SetPlaySpeed(1);
			m_Speed = 0;
		}
	}
	if (m_Speed >= 10 && Anim->GetCurrentAnimatorKey() == "Idle")
	{
		Anim->SetCurrentAnimator("Move");
	}
	if (Anim->GetCurrentAnimatorKey() == "Move" && m_pObject->GetComponent<cPath>()->GetNextPoint() == 1)
	{
		if (m_pObject->GetComponent<cPath>()->GetDirection() <= D3DXToRadian(90) && m_pObject->GetComponent<cPath>()->GetDirection() >= D3DXToRadian(-90))
		{
			m_pObject->SetScale(Vector2(1, 1));
		}
		else
		{
			m_pObject->SetScale(Vector2(-1, 1));
		}
	}

	IsOutMap();
}

void cFlan::Render()
{
	if (m_pObject->GetComponent<cRenderer>()->GetEnable())
	{
		IMAGE->Render(m_Texture_Circle, m_pObject->GetPosition(), Vector2(3, 3), (int)(GetTickCount()) * 0.002, D3DCOLOR_ARGB(150, 255, 255, 255));
	}
}

void cFlan::Release()
{

}

cObject* cFlan::AddBullet(Vector2 Pos, int Speed, float Direction, int Size, texture* Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, Image->info.Width == 64 ? -9 : -10, Tag::Bullet);
	a->AddComponent<cBullet>()->SetDirection(Direction);
	a->GetComponent<cBullet>()->SetSpeed(Speed);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

cObject* cFlan::AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, texture* Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, Image->info.Width == 64 ? -9 : -10, Tag::Bullet);
	a->AddComponent<cBulletFriction>()->SetDirection(Direction);
	a->GetComponent<cBulletFriction>()->SetSpeed(StartSpeed);
	a->GetComponent<cBulletFriction>()->SetEndSpeed(EndSpeed);
	a->GetComponent<cBulletFriction>()->SetFriction(Friction);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

void cFlan::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 64 < 0
		|| Pos.x - 64 > 384
		|| Pos.y + 64 < 0
		|| Pos.y - 64 > 480) m_pObject->Destroy();
}

void cFlan::Spell()
{
	SOUND->Play("Spell");
	SYSTEM->SetBonus(true);
	cEffect* b = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
	EFFECT->AlphaSetting(b, 500, -17);
	EFFECT->SizeSetting(b, Vector2(0.25, 0.25));
	m_Armor = 0.35;
	m_pObject->GetComponent<cPath>()->Clear();
	m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 120));
	m_Friction = 0.99;
	m_Speed = Math::PointDistance(m_pObject->GetPosition(), Vector2(192, 120)) * 2;
	wstring Name;
	switch (m_Phase)
	{
	case 13:
		m_TimeLeft = 55;
		Name = L"금기 『크랜베리 트랩』";
		m_pObject->GetComponent<cTimeLine_Flan1>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan2>();
		break;

	case 11:
		m_TimeLeft = 55;
		Name = L"금기 『레바테인』";
		m_pObject->GetComponent<cTimeLine_Flan3>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan4>();
		break;
	case 9:
		m_TimeLeft = 65;
		Name = L"금기 『포 오브 어 카인드』";
		m_pObject->GetComponent<cTimeLine_Flan5>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan6>();
		break;
	case 7:
		m_TimeLeft = 65;
		Name = L"금기 『카고메 카고메』";
		m_pObject->GetComponent<cTimeLine_Flan7>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan8>();
		break;
	case 5:
		m_TimeLeft = 70;
		Name = L"금탄 『카타디옵트릭스』";
		m_pObject->GetComponent<cTimeLine_Flan9>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan10>();
		break;
	case 3:
		m_TimeLeft = 85;
		Name = L"비탄 『그리고 아무도 없게 될까?』";
		m_pObject->AddComponent<cTimeLine_Flan11>();
		break;
	}

	cObject* a = OBJECT->Create("Face", Vector2(512, 250), -15, Tag::None);
	a->AddComponent<cRenderer>()->SetImage(IMAGE->FindImage("Face_Flan"));
	a->AddComponent<cFace>()->SetText(Name);
}

void cFlan::EndSpell()
{
	m_TimeLeft = 30;
	m_Armor = 1;
	cEffect* b = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
	EFFECT->AlphaSetting(b, 500, -17);
	EFFECT->SizeSetting(b, Vector2(0.2, 0.2));
	OBJECT->With("Face", [&](cObject* Obj)->void {
		if (Obj->GetComponent<cFace>()->GetIsEnemy())
		{
			Obj->Destroy();
		}
	});
	switch (m_Phase)
	{
	case 12:
		m_pObject->GetComponent<cTimeLine_Flan2>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan3>();
		break;
	case 10:
		m_pObject->GetComponent<cTimeLine_Flan4>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan5>();
		break;
	case 8:
		OBJECT->With("Zako", [&](cObject* Obj)->void {
			Obj->GetComponent<cZako>()->SetHp(0);
		});
		m_pObject->GetComponent<cTimeLine_Flan6>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan7>();
		break;
	case 6:
		m_pObject->GetComponent<cTimeLine_Flan8>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan9>();
		OBJECT->With("Bullet_Flan8",[&](cObject* Obj)->void{
			Obj->Destroy();
		});
		break;
	case 4:
		m_pObject->GetComponent<cTimeLine_Flan10>()->SetEnable(false);
		m_Phase--;
		Spell();
		OBJECT->With(Tag::Bullet, [&](cObject* Obj)->void
		{
			Obj->Destroy();
		});
		break;
	case 2:
		m_pObject->GetComponent<cTimeLine_Flan11>()->SetEnable(false);
		m_pObject->AddComponent<cTimeLine_Flan12>();
		m_Phase--;
		m_TimeLeft = 10000;
		m_MaxHp = 6000;
		m_Hp = 6000;
		m_Armor = 0.35;
		cObject* a = OBJECT->Create("Face", Vector2(512, 250), -15, Tag::None);
		a->AddComponent<cRenderer>()->SetImage(IMAGE->FindImage("Face_Flan"));
		a->AddComponent<cFace>()->SetText(L"QED『495년의 파문』");
		break;
	}
}