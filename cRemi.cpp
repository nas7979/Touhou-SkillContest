#include "DXUT.h"
#include "cRemi.h"
#include "cBullet.h"
#include "cBulletFriction.h"
#include "cBulletToPos.h"
#include "cItem.h"
#include "cTimeLine_BossEffect.h"
#include "cTimeLine_Remi1.h"
#include "cTimeLine_Remi2.h"
#include "cTimeLine_BossDeath.h"
#include "cFace.h"

cRemi::cRemi(cObject* Object)
	:cComponent(Object)
{
}


cRemi::~cRemi()
{
}

void cRemi::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_pObject->AddComponent<cAnimation>();
	m_pObject->AddComponent<cPath>();
	m_pObject->AddComponent<cTimeLine_BossEffect>();
	m_pObject->AddComponent<cTimeLine_Remi1>();

	m_pObject->GetComponent<cAnimation>()->AddAnimator("Idle", "Remi_Idle", 10);
	m_pObject->GetComponent<cAnimation>()->AddAnimator("Move", "Remi_Move", 10, true);
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
	m_Hp = 10000;
	m_Armor = 1;
	m_MaxHp = 10000;
	m_Phase = 2;
	m_TimeLeft = 30;
	m_LastTime = 30;
	OBJECT->SetBoss(m_pObject);
	m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 120));
	m_Texture_Circle = IMAGE->FindImage("Enemy_Circle");
}

void cRemi::Update()
{
	if (m_LastTime != (int)m_TimeLeft && m_LastTime < 10)
	{
		SOUND->Play("TimeOut");
	}
	m_LastTime = (int)m_TimeLeft;
	m_TimeLeft -= 0.0166666666666667;
	if (m_TimeLeft <= 0)
	{
		if (m_Phase == 2)
		{
			m_Hp = 0;
		}
		else
		{
			m_pObject->GetComponent<cTimeLine_Remi2>()->SetEnable(false);
			m_TimeLeft = 100;
			m_Hp = 100000;
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
			});
			OBJECT->With("Face", [&](cObject* Obj)->void {
				if (Obj->GetComponent<cFace>()->GetIsEnemy())
				{
					Obj->Destroy();
				}
			});
			OBJECT->SetBoss(nullptr);
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(m_pObject->GetPosition().x, -70));
			m_Friction = 1.02;
			m_Speed = 20;
			SYSTEM->CreateFlan();
		}
	}

	if (m_Hp <= 0)
	{
		if (m_Phase != 1)
		{
			SOUND->Play("Spell");
			SYSTEM->SetBonus(true);
			cEffect* b = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
			EFFECT->AlphaSetting(b, 500, -17);
			EFFECT->SizeSetting(b, Vector2(0.25, 0.25));
			m_Armor = 0.35;
			m_Hp = 5000;
			m_MaxHp = 5000;
			m_Phase--;
			m_SpellBonus = 5000000;
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(192, 120));
			m_pObject->GetComponent<cRemi>()->SetFriction(0.99);
			m_pObject->GetComponent<cRemi>()->SetSpeed(Math::PointDistance(m_pObject->GetPosition(), Vector2(192, 120)) * 2);
			m_pObject->AddComponent<cTimeLine_Remi2>();
			cObject* a = OBJECT->Create("Face", Vector2(512, 250), -15, Tag::None);
			a->AddComponent<cRenderer>()->SetImage(IMAGE->FindImage("Face_Remi"));
			a->AddComponent<cFace>()->SetText(L"¡ºÈíÇ÷±ÍÈ¯»ó¡»");
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

			m_TimeLeft = 60;
			m_LastTime = 60;
			a = OBJECT->Create("Item3", m_pObject->GetPosition() + Vector2((rand() % 200) - 100, (rand() % 200) - 100), -2, Tag::Item);
			a->AddComponent<cItem>();
			for (int i = 0; i < 11; i++)
			{
				a = OBJECT->Create("Item1", m_pObject->GetPosition() + Vector2((rand() % 200) - 100, (rand() % 200) - 100), -2, Tag::Item);
				a->AddComponent<cItem>();
			}
		}
		else
		{
			m_pObject->Destroy();
			SYSTEM->CreateFlan();
			OBJECT->SetBoss(nullptr);
			SOUND->Play("EnemyDeath2");
			SOUND->End("Remi_Thema");
			cEffect* b = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
			EFFECT->AlphaSetting(b, 500, -17);
			EFFECT->SizeSetting(b, Vector2(0.2, 0.2));
			OBJECT->With("Face", [&](cObject* Obj)->void {
				if (Obj->GetComponent<cFace>()->GetIsEnemy())
				{
					Obj->Destroy();
				}
			});
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
				cObject* a = OBJECT->Create("Item5", Obj->GetPosition(), -11, Tag::Item);
				a->AddComponent<cItem>()->SetCollect(true);
			});
			cObject* a = OBJECT->Create("Item3", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, (rand() % 150) - 75), -2, Tag::Item);
			a->AddComponent<cItem>();
			a = OBJECT->Create("Item4", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, (rand() % 150) - 75), -2, Tag::Item);
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
				b = EFFECT->Create(IMAGE->FindImage("SpellBonus"), Vector2(192, 75), Vector2(1, 1), -20);
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
		}
	}
	m_SpellBonus -= 300;
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

void cRemi::Render()
{
	IMAGE->Render(m_Texture_Circle, m_pObject->GetPosition(), Vector2(2, 2), (int)(GetTickCount()) * 0.002, D3DCOLOR_ARGB(150, 255, 255, 255));
}

void cRemi::Release()
{

}

cObject* cRemi::AddBullet(Vector2 Pos, int Speed, float Direction, int Size, texture* Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, Image->info.Width == 64 ? -9:-10, Tag::Bullet);
	a->AddComponent<cBullet>()->SetDirection(Direction);
	a->GetComponent<cBullet>()->SetSpeed(Speed);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

cObject* cRemi::AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, texture* Image)
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

void cRemi::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 64 < 0
		|| Pos.x - 64 > 384
		|| Pos.y + 64 < 0
		|| Pos.y - 64 > 480) m_pObject->Destroy();
}