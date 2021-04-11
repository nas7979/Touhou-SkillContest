#include "DXUT.h"
#include "cZako.h"
#include "cBullet.h"
#include "cBulletFriction.h"
#include "cBulletToPos.h"
#include "cItem.h"
#include "cTimeLine_Flan6.h"

cZako::cZako(cObject* Object)
	:cComponent(Object)
{
}


cZako::~cZako()
{
}

void cZako::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_pObject->AddComponent<cAnimation>();
	m_pObject->AddComponent<cPath>();

	m_pObject->GetComponent<cAnimation>()->AddAnimator("Idle", m_pObject->GetName() + "_Idle", 6);
	m_pObject->GetComponent<cAnimation>()->AddAnimator("Move", m_pObject->GetName() + "_Move", 10, true);
	m_pObject->GetComponent<cAnimation>()->SetCurrentAnimator("Move");
	m_pObject->GetComponent<cAnimation>()->SetCurrentFrame(4);
	
	m_pObject->GetComponent<cCircleCollider>()->AddListName("PlayerBullet");
	m_pObject->GetComponent<cCircleCollider>()->SetRadius(20);
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void {
		if (Other->GetName() == "PlayerBullet")
		{
			if (Other->GetComponent<cBulletToPos>() != nullptr)
			{
				m_Hp -= Other->GetComponent<cBulletToPos>()->GetDamage();
			}
			else
			{
				m_Hp -= Other->GetComponent<cBullet>()->GetDamage();
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

	m_pObject->SetName("Zako");
	m_Friction = 1;
}

void cZako::Update()
{
	if (m_Hp <= 0)
	{
		m_pObject->Destroy();
		SOUND->Play("EnemyDeath1");
		if (m_pObject->GetComponent<cTimeLine_Flan6>() == nullptr)
		{
			cEffect* a = EFFECT->Create("EnemyDeath2", m_pObject->GetPosition(), Vector2(0.1, 0.1), 1);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 255, -15);
		}
		else
		{
			cEffect* b = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
			EFFECT->AlphaSetting(b, 500, -17);
			EFFECT->SizeSetting(b, Vector2(0.25, 0.25));
		}

		for (auto iter : m_Drop)
		{
			cObject* b = OBJECT->Create(iter, m_pObject->GetPosition() + Vector2((rand() % 32) - 16,(rand() % 32) - 16), -2, Tag::Item);
			b->AddComponent<cItem>();
		}
	}
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

void cZako::Render()
{
	
}

void cZako::Release()
{

}

cObject* cZako::AddBullet(Vector2 Pos, int Speed, float Direction, int Size, string Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, -10, Tag::Bullet);
	a->AddComponent<cBullet>()->SetDirection(Direction);
	a->GetComponent<cBullet>()->SetSpeed(Speed);
	a->GetComponent<cRenderer>()->SetImage(IMAGE->FindImage(Image));
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

cObject* cZako::AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, string Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, -10, Tag::Bullet);
	a->AddComponent<cBulletFriction>()->SetDirection(Direction);
	a->GetComponent<cBulletFriction>()->SetSpeed(StartSpeed);
	a->GetComponent<cBulletFriction>()->SetEndSpeed(EndSpeed);
	a->GetComponent<cBulletFriction>()->SetFriction(Friction);
	a->GetComponent<cRenderer>()->SetImage(IMAGE->FindImage(Image));
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

cObject* cZako::AddBullet(Vector2 Pos, int Speed, float Direction, int Size, texture* Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, -10, Tag::Bullet);
	a->AddComponent<cBullet>()->SetDirection(Direction);
	a->GetComponent<cBullet>()->SetSpeed(Speed);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

cObject* cZako::AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, texture* Image)
{
	cObject* a = OBJECT->Create("EnemyBullet", Pos, -10, Tag::Bullet);
	a->AddComponent<cBulletFriction>()->SetDirection(Direction);
	a->GetComponent<cBulletFriction>()->SetSpeed(StartSpeed);
	a->GetComponent<cBulletFriction>()->SetEndSpeed(EndSpeed);
	a->GetComponent<cBulletFriction>()->SetFriction(Friction);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(Size);
	return a;
}

void cZako::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 16 < 0
		|| Pos.x - 16 > 384
		|| Pos.y + 16 < 0
		|| Pos.y - 16 > 480) m_pObject->Destroy();
}