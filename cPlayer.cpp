#include "DXUT.h"
#include "cPlayer.h"
#include "cBullet.h"
#include "cBulletToPos.h"
#include "cGraze.h"
#include "cItem.h"
#include "cFace.h"

cPlayer::cPlayer(cObject* Object)
	:cComponent(Object)
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	OBJECT->SetPlayer(m_pObject);
	cObject* a = OBJECT->Create("Graze", Vector2(0, 0), 0, Tag::None);
	a->AddComponent<cGraze>();
	BallPos = Vector2(0, 0);
	
	m_pObject->AddComponent<cAnimation>();
	m_pObject->GetComponent<cAnimation>()->AddAnimator("Idle", "Player_Idle", 6);
	m_pObject->GetComponent<cAnimation>()->AddAnimator("MoveSide", "Player_MoveSide", 2, true);
	m_pObject->GetComponent<cAnimation>()->SetCurrentAnimator("Idle");

	m_pObject->AddComponent<cCircleCollider>();
	m_pObject->GetComponent<cCircleCollider>()->SetRadius(2);
	m_pObject->GetComponent<cCircleCollider>()->AddListName("EnemyBullet");
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void {
		if (Other->GetName() == "EnemyBullet" && !Dead)
		{
			m_pObject->GetComponent<cCircleCollider>()->SetEnable(false);
			m_pObject->GetComponent<cRenderer>()->SetEnable(false);
			Dead = true;
			Shift = false;
			Fireable = true;
			SubFireable = true;
			Graze_Circle_Alpha = 0;
			SOUND->Play("PlayerDeath");
			cEffect* a= EFFECT->Create("Player_Idle1", m_pObject->GetPosition(), Vector2(1.5, 1.5), -10);
			EFFECT->AlphaSetting(a, 200, -5);
			EFFECT->SizeSetting(a, Vector2(-0.075, 0.075));
			a = EFFECT->Create("EnemyDeath1", m_pObject->GetPosition(), Vector2(0.5, 0.5), -10);
			EFFECT->SizeSetting(a, Vector2(0.2, 0.2));
			EFFECT->AlphaSetting(a, 200, -15);
			if(SYSTEM->GetTimeSpeed() != 1)
			{
				SYSTEM->SetTimeSpeed(5);
			}
			SYSTEM->AddLife(-1);
			SYSTEM->AddMissed(1);
			SYSTEM->SetBonus(false);

			if (SYSTEM->GetLife() == 0)
			{
				SYSTEM->GotoLose();
			}
			else
			{
				Timer_FireDelay = new cTimer(60, [&]()->void{
					m_pObject->SetPosition(Vector2(192, 400));
					cEffect* a = EFFECT->Create("Player_Idle1", m_pObject->GetPosition(), Vector2(3, 3), 1);
					EFFECT->AlphaSetting(a, 5, 3);
					EFFECT->SizeSetting(a, Vector2(-0.075, -0.075));
					Timer_FireDelay = nullptr;
					SAFE_DELETE(Timer_FireDelay);
				});
				Timer_SubFireDelay = new cTimer(87, [&]()->void {
					m_pObject->GetComponent<cRenderer>()->SetEnable(true);
					m_pObject->GetComponent<cRenderer>()->SetAlpha(125);
					Dead = false;
					Timer_SubFireDelay = nullptr;
					SAFE_DELETE(Timer_SubFireDelay);
					if (SYSTEM->GetGage() < 75) SYSTEM->SetGage(75);
					Timer_Deathbomb = new cTimer(200, [&]()->void {
						m_pObject->GetComponent<cCircleCollider>()->SetEnable(true);
						m_pObject->GetComponent<cRenderer>()->SetAlpha(255);
						Timer_Deathbomb = nullptr;
						SAFE_DELETE(Timer_Deathbomb);
					});
				});
				Timer_Deathbomb = new cTimer(8, [&]()->void {
					Deathbomb = false;
					SYSTEM->AddPower(-16);
					cObject* a = OBJECT->Create("Item3", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, -(rand() % 150)), -2, Tag::Item);
					a->AddComponent<cItem>()->SetSpeed(-600);
					for (int i = 0; i < 5; i++)
					{
						a = OBJECT->Create("Item1", m_pObject->GetPosition() + Vector2((rand() % 150) - 75, -(rand() % 150)), -2, Tag::Item);
						a->AddComponent<cItem>()->SetSpeed(-600);
					}
					Timer_Deathbomb = nullptr;
					SAFE_DELETE(Timer_Deathbomb);
				});
				Deathbomb = true;
			}
		}
	});

	Fireable = true;
	SubFireable = true;
	Shift = false;
	Dead = false;
	Slowable = true;
	Deathbomb = false;
	Graze_Circle_Alpha = 0;
	Bullet1 = IMAGE->FindImage("PlayerBullet1");
	Bullet2 = IMAGE->FindImage("PlayerBullet2");
}

void cPlayer::Update()
{
	if (!Dead)
	{
		if (m_pObject->GetPosition().y <= 150)
		{
			OBJECT->With(Tag::Item, [&](cObject* Obj)->void {
				Obj->GetComponent<cItem>()->SetCollect(true);
			});
		}
		if (GetAsyncKeyState(VK_SHIFT) * 0x8000)
		{
			Shift = true;
		}
		else
		{
			Shift = false;
		}

		int m_Speed = (320 - Shift * 150) * max(SYSTEM->GetTimeSpeed(), 0.5);
		cAnimation* Animation = m_pObject->GetComponent<cAnimation>();
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (m_pObject->GetPosition().x > 0) m_pObject->Translate(Vector2(-m_Speed, 0) * DeltaTime);
			else m_pObject->SetPosition(Vector2(0, m_pObject->GetPosition().y));
			if (Animation->GetCurrentAnimatorKey() == "Idle")
			{
				Animation->SetCurrentAnimator("MoveSide");
				m_pObject->SetScale(Vector2(1, 1));
			}
			else if (Animation->GetCurrentAnimatorKey() == "MoveSide" &&  m_pObject->GetScale().x == -1)
			{
				Animation->SetPlaySpeed(-1);
				Animation->SetPaused(false);
				if (Animation->GetCurrentFrame() == 0)
				{
					Animation->SetPlaySpeed(1);
					m_pObject->SetScale(Vector2(1, 1));
				}
			}
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (m_pObject->GetPosition().x < 384) m_pObject->Translate(Vector2(m_Speed, 0) * DeltaTime);
			else m_pObject->SetPosition(Vector2(384, m_pObject->GetPosition().y));
			if (Animation->GetCurrentAnimatorKey() == "Idle")
			{
				Animation->SetCurrentAnimator("MoveSide");
				m_pObject->SetScale(Vector2(-1, 1));
			}
			else if (Animation->GetCurrentAnimatorKey() == "MoveSide" && m_pObject->GetScale().x == 1)
			{
				Animation->SetPlaySpeed(-1);
				Animation->SetPaused(false);
				if (Animation->GetCurrentFrame() == 0)
				{
					Animation->SetPlaySpeed(1);
					m_pObject->SetScale(Vector2(-1, 1));
				}
			}
		}
		if (!GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_LEFT))
		{
			if (Animation->GetCurrentAnimatorKey() == "MoveSide")
			{
				Animation->SetPlaySpeed(-1);
				Animation->SetPaused(false);
				if (Animation->GetCurrentFrame() == 0)
				{
					Animation->SetCurrentAnimator("Idle");
					Animation->SetPlaySpeed(1);
				}
			}
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (m_pObject->GetPosition().y > 0) m_pObject->Translate(Vector2(0, -m_Speed) * DeltaTime);
			else m_pObject->SetPosition(Vector2(m_pObject->GetPosition().x, 0));
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (m_pObject->GetPosition().y < 480) m_pObject->Translate(Vector2(0, m_Speed) * DeltaTime);
			else m_pObject->SetPosition(Vector2(m_pObject->GetPosition().x, 480));
		}

		if (GetAsyncKeyState('Z') & 0x8000 && Fireable == true)
		{
			Fire();
		}
	}
	else
	{
		OBJECT->With(Tag::Bullet, [&](cObject* Obj)->void {
			Obj->Destroy();
		});
	}

	if (GetAsyncKeyState('X') & 0x8000 && Slowable && (!Dead || Deathbomb))
	{
		if (Deathbomb == true && SYSTEM->GetGage() >= 25)
		{
			m_pObject->GetComponent<cCircleCollider>()->SetEnable(true);
			m_pObject->GetComponent<cRenderer>()->SetEnable(true);
			Dead = false;
			Deathbomb = false;
			Timer_SubFireDelay = nullptr;
			SAFE_DELETE(Timer_SubFireDelay);
			Timer_FireDelay = nullptr;
			SAFE_DELETE(Timer_FireDelay);
			Timer_Deathbomb = nullptr;
			SAFE_DELETE(Timer_Deathbomb);
			SYSTEM->AddLife(1);
			SYSTEM->AddBoomCount(1);
		}
		Slowable = false;
		if (SYSTEM->GetTimeSpeed() == 1)
		{
			if (SYSTEM->GetGage() >= 25)
			{
				SYSTEM->AddGage(-25);
				SYSTEM->SetTimeSpeed(0.2);
				SYSTEM->AddBoomCount(1);
				SOUND->Play("PlayerSpell");
				OBJECT->With(Tag::Bullet, [&](cObject* Obj)->void {
					if (Math::PointDistance(m_pObject->GetPosition(), Obj->GetPosition()) <= 32)
					{
						Obj->Destroy();
						cObject* a = OBJECT->Create("Item5", Obj->GetPosition(), -2, Tag::Item);
						a->AddComponent<cItem>()->SetCollect(true);
					}
				});
				cObject* a = OBJECT->Create("Face", Vector2(-128, 250), -11, Tag::None);
				a->AddComponent<cRenderer>()->SetImage(IMAGE->FindImage("Face_Saku"));
				a->AddComponent<cFace>()->SetIsEnemy(false);
				a->GetComponent<cFace>()->SetText(L"½ÃºÎ¡ºÇÁ¶óÀÌºø ½ºÄù¾î¡»");
			}
		}
		else
		{
			SYSTEM->SetTimeSpeed(5);
			SOUND->Play("Kira1");
		}
	}
	if (Timer_FireDelay) Timer_FireDelay->Update();
	if (Timer_SubFireDelay) Timer_SubFireDelay->Update();
	if (Timer_Deathbomb) Timer_Deathbomb->Update();
	D3DXVec2Lerp(&BallPos, &Vector2(0, 0), &Vector2(16, -24), Graze_Circle_Alpha / 255);
}

void cPlayer::Render()
{
	if (Shift)
	{
		if (Graze_Circle_Alpha != 255) Graze_Circle_Alpha += 51;
		IMAGE->Render(IMAGE->FindImage("HitPoint"), m_pObject->GetPosition(), Vector2(1, 1), 0);
	}
	else
	{
		if (Graze_Circle_Alpha != 0) Graze_Circle_Alpha -= 51;
	}
	if (Graze_Circle_Alpha != 0)
	{
		IMAGE->Render(IMAGE->FindImage("Graze_Circle"), m_pObject->GetPosition(), Vector2(1, 1), (int)(GetTickCount()) * 0.002, D3DCOLOR_ARGB((int)Graze_Circle_Alpha, 255, 255, 255));
	}

	if (!Dead)
	{
		IMAGE->Render(IMAGE->FindImage("PlayerBall"), m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), Vector2(1, 1), 0);
		IMAGE->Render(IMAGE->FindImage("PlayerBall"), m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), Vector2(1, 1), 0);
	}
}

void cPlayer::Release()
{
	if (Timer_FireDelay)
	{
		Timer_FireDelay = nullptr;
		SAFE_DELETE(Timer_FireDelay);
	}
	if (Timer_SubFireDelay)
	{
		Timer_SubFireDelay = nullptr;
		SAFE_DELETE(Timer_SubFireDelay);
	}
	if (Timer_Deathbomb)
	{
		Timer_Deathbomb = nullptr;
		SAFE_DELETE(Timer_Deathbomb);
	}
}

cObject* cPlayer::AddBullet(Vector2 Pos, float Direction, int Damage, texture* Image)
{
	cObject* a = OBJECT->Create("PlayerBullet", Pos, 5, Tag::Bullet);
	a->AddComponent<cBullet>()->SetIsEnemy(false);
	a->GetComponent<cBullet>()->SetDamage(Damage);
	a->GetComponent<cBullet>()->SetDirection(Direction);
	a->GetComponent<cBullet>()->SetSpeed(1000 / SYSTEM->GetTimeSpeed());
	a->GetComponent<cRenderer>()->SetAlpha(100);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(12);
	a->SetScale(Vector2(2, 2));
	return a;
}

cObject* cPlayer::AddBullet(Vector2 Pos, float Direction, int Damage, texture* Image, cObject* Target)
{
	cObject* a = OBJECT->Create("PlayerBullet", Pos, 5, Tag::Bullet);
	a->AddComponent<cBulletToPos>()->SetIsEnemy(false);
	a->GetComponent<cBulletToPos>()->SetDamage(Damage);
	a->GetComponent<cBulletToPos>()->SetDirection(Direction);
	a->GetComponent<cBulletToPos>()->SetSpeed(1000 / SYSTEM->GetTimeSpeed());
	a->GetComponent<cBulletToPos>()->SetTarget(Target);
	a->GetComponent<cRenderer>()->SetAlpha(100);
	a->GetComponent<cRenderer>()->SetImage(Image);
	a->GetComponent<cCircleCollider>()->SetRadius(12);
	a->SetScale(Vector2(2, 2));
	return a;
}

void cPlayer::Fire()
{
	Fireable = false;
	Timer_FireDelay = new cTimer(4, [&]()->void {
		Fireable = true;
		Timer_FireDelay = nullptr;
		SAFE_DELETE(Timer_FireDelay);
	});
	SOUND->Play("PlayerShot");

	int Power = SYSTEM->GetPower();
	int Damage = 12 + Power * 0.035 - Shift * Power * 0.04;
	cObject* Near = Math::Nearest(m_pObject->GetPosition(), Tag::Enemy);
	if (Near != nullptr)
	{
		if (abs(m_pObject->GetPosition().x - Near->GetPosition().x) > 150) Near = nullptr;
	}

	switch (Power / 32)
	{
	case 0:
		if (!Shift)
		{
			for (int i = -8; i <= 8; i += 16)
			{
				AddBullet(m_pObject->GetPosition() - Vector2(i, 0), 270, Damage, Bullet1);
			}
		}
		else
		{
			for (int i = -8; i <= 8; i += 16)
			{
				AddBullet(m_pObject->GetPosition() - Vector2(i, 0), 270, Damage, Bullet1, Near);
			}
		}
		if (SubFireable)
		{
			if (!Shift)
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 240, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 300, Damage, Bullet2);
			}
			else
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
			}
			SubFireable = false;
			Timer_SubFireDelay = new cTimer(12, [&]()->void {
				SubFireable = true;
				Timer_SubFireDelay = nullptr;
				SAFE_DELETE(Timer_SubFireDelay);
			});
		}
		break;

	case 1:
		if (!Shift)
		{
			for (int i = -8; i <= 8; i += 16)
			{
				AddBullet(m_pObject->GetPosition() - Vector2(i, 0), 270, Damage, Bullet1);
			}
		}
		else
		{
			for (int i = -8; i <= 8; i += 16)
			{
				AddBullet(m_pObject->GetPosition() - Vector2(i, 0), 270, Damage, Bullet1, Near);
			}
		}
		if (SubFireable)
		{
			if (!Shift)
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 240, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 250, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 290, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 300, Damage, Bullet2);
			}
			else
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 265, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 275, Damage, Bullet2, Near);
			}
			SubFireable = false;
			Timer_SubFireDelay = new cTimer(12, [&]()->void {
				SubFireable = true;
				Timer_SubFireDelay = nullptr;
				SAFE_DELETE(Timer_SubFireDelay);
			});
		}
		break;

	case 2:
		if (!Shift)
		{
			for (int i = -5; i <= 5; i += 5)
			{
				AddBullet(m_pObject->GetPosition(), 270 + i, Damage, Bullet1);
			}
		}
		else
		{
			for (int i = -5; i <= 5; i += 5)
			{
				AddBullet(m_pObject->GetPosition(), 270 + i, Damage, Bullet1, Near);
			}
		}
		if (SubFireable)
		{
			if (!Shift)
			{
				for (int i = 0; i < 30; i += 10)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 240 + i, Damage, Bullet2);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 300 - i, Damage, Bullet2);
				}
			}
			else
			{
				for (int i = 0; i <= 8; i += 4)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 265 + i, Damage, Bullet2, Near);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 275 - i, Damage, Bullet2, Near);
				}
			}
			SubFireable = false;
			Timer_SubFireDelay = new cTimer(12, [&]()->void {
				SubFireable = true;
				Timer_SubFireDelay = nullptr;
				SAFE_DELETE(Timer_SubFireDelay);
			});
		}
		break;

	case 3:
		if (!Shift)
		{
			AddBullet(m_pObject->GetPosition(), 270, Damage, Bullet1);
			AddBullet(m_pObject->GetPosition() - Vector2(0, -10), 262, Damage, Bullet1);
			AddBullet(m_pObject->GetPosition() - Vector2(0, -10), 278, Damage, Bullet1);
		}
		else
		{
			for (int i = -5; i <= 5; i += 5)
			{
				AddBullet(m_pObject->GetPosition(), 270 + i, Damage, Bullet1, Near);
			}
		}
		if (SubFireable)
		{
			if (!Shift)
			{
				for (int i = 0; i < 40; i += 10)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 235 + i, Damage, Bullet2);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 305 - i, Damage, Bullet2);
				}
			}
			else
			{
				for (int i = 0; i <= 9; i += 3)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 265 + i, Damage, Bullet2, Near);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 275 - i, Damage, Bullet2, Near);
				}
			}
			SubFireable = false;
			Timer_SubFireDelay = new cTimer(12, [&]()->void {
				SubFireable = true;
				Timer_SubFireDelay = nullptr;
				SAFE_DELETE(Timer_SubFireDelay);
			});
		}
		else
		{
			if (!Shift)
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 265, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 275, Damage, Bullet2);
			}
			else
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
			}
		}
		break;

	case 4:
		if (!Shift)
		{
			for (int i = -8; i <= 8; i += 8)
			{
				AddBullet(m_pObject->GetPosition(), 270 + i, Damage, Bullet1);
			}
		}
		else
		{
			for (int i = -8; i <= 8; i += 8)
			{
				AddBullet(m_pObject->GetPosition(), 270 + i, Damage, Bullet1, Near);
			}
		}
		if (SubFireable)
		{
			if (!Shift)
			{
				for (int i = 0; i < 40; i += 10)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 235 + i, Damage, Bullet2);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 305 - i, Damage, Bullet2);
				}
				AddBullet(m_pObject->GetPosition(), 254, Damage, Bullet1);
				AddBullet(m_pObject->GetPosition(), 286, Damage, Bullet1);
			}
			else
			{
				for (int i = 0; i <= 9; i += 3)
				{
					AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 265 + i, Damage, Bullet2, Near);
					AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 275 - i, Damage, Bullet2, Near);
				}
				AddBullet(m_pObject->GetPosition(), 265, Damage, Bullet1, Near);
				AddBullet(m_pObject->GetPosition(), 275, Damage, Bullet1, Near);
			}
			SubFireable = false;
			Timer_SubFireDelay = new cTimer(8, [&]()->void {
				SubFireable = true;
				Timer_SubFireDelay = nullptr;
				SAFE_DELETE(Timer_SubFireDelay);
			});
		}
		else
		{
			if (!Shift)
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 275, Damage, Bullet2);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 265, Damage, Bullet2);
			}
			else
			{
				AddBullet(m_pObject->GetPosition() + Vector2(-24 + BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
				AddBullet(m_pObject->GetPosition() + Vector2(+24 - BallPos.x, BallPos.y), 270, Damage, Bullet2, Near);
			}
		}
		break;
	}
}