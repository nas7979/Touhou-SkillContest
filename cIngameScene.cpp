#include "DXUT.h"
#include "cIngameScene.h"
#include "cPlayer.h"
#include "cRemi.h"
#include "cFlan.h"
#include "cZako.h"
#include "cTimeLine_Zako1.h"
#include "cTimeLine_Zako2.h"
#include "cTimeLine_Zako3.h"
#include "cTimeLine_Zako4.h"
#include "cTimeLine_Zako5.h"
#include "cTimeLine_Zako6.h"
#include "cTimeLine_Zako7.h"
#include "cTimeLine_Zako8.h"

cIngameScene::cIngameScene()
{
}


cIngameScene::~cIngameScene()
{
}

void cIngameScene::Init()
{
	m_Texture_Slow = IMAGE->FindImage("Back_Slow");
	m_Texture_Remi = IMAGE->FindImage("Back_Remi");
	m_Texture_Flan = IMAGE->FindImage("Back_Flan");
	m_Texture_Background = IMAGE->FindImage("ST1_Background");
	m_Texture_Enemy = IMAGE->FindImage("Enemy");

	cObject* m_Player = OBJECT->Create("Player", Vector2(192, 400), -5, Tag::Player);
	m_Player->AddComponent<cRenderer>();
	m_Player->AddComponent<cPlayer>();

	m_Slow_Alpha = 0;
	m_Background_y = -2520;
	m_Background_Speed = 21;
	m_Time = 0;
	m_CreatePos = Vector2(0, 0);
	SOUND->Play("Field_Thema");
	//SYSTEM->CreateFlan();
}

void cIngameScene::Release()
{
}

void cIngameScene::Update()
{
	float TimeSpeed = SYSTEM->GetTimeSpeed();
	if (m_Background_y != 0)
	{
		m_Background_y += m_Background_Speed * DeltaTime * TimeSpeed;;
		if (m_Background_y >= -750)
		{
			m_Background_Speed += 10 * TimeSpeed;
			if (m_Background_y > 0)
			{
				m_Background_y = 0;
			}
		}
	}


	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 140:
		case 180:
		case 220:
		case 260:
		case 300:
		case 340:
		case 380:
		case 420:
		{
			for (int i = 0; i < 2; i++)
			{
				cObject* a = OBJECT->Create("Zako1", Vector2(50 + i * 40, -16), -1, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(10);
				a->GetComponent<cZako>()->SetSpeed(150);
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cPath>()->AddPath(Vector2(50 + i * 40,200),Vector2(434,400));
				a->AddComponent<cTimeLine_Zako1>();
			}
		} break;

		case 500:
		case 540:
		case 580:
		case 620:
		case 660:
		case 700:
		case 740:
		case 780:
		{
			for (int i = 0; i < 2; i++)
			{
				cObject* a = OBJECT->Create("Zako1", Vector2(334 + i * -40, -16), -1, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(10);
				a->GetComponent<cZako>()->SetSpeed(150);
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cPath>()->AddPath(Vector2(334 + i * -40, 200), Vector2(-50, 400));
				a->AddComponent<cTimeLine_Zako1>();
			}
		} break;

		case 1000:
		case 1020:
		case 1040:
		case 1060:
		case 1080:
		case 1100:
		case 1120:
		case 1140:
		{
			m_CreatePos.x += 48;
			cObject* a = OBJECT->Create("Zako2", Vector2(m_CreatePos.x, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(100);
			a->GetComponent<cZako>()->SetSpeed(200);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(Vector2(m_CreatePos.x, 500), Vector2(-50, 200));
			a->AddComponent<cTimeLine_Zako4>();
		} break;

		case 1300:
		case 1320:
		case 1340:
		case 1360:
		case 1380:
		case 1400:
		case 1420:
		case 1440:
		case 1460:
		{
			m_CreatePos.x -= 48;
			cObject* a = OBJECT->Create("Zako2", Vector2(m_CreatePos.x, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(100);
			a->GetComponent<cZako>()->SetSpeed(200);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(Vector2(m_CreatePos.x, 500), Vector2(434, 200));
			a->AddComponent<cTimeLine_Zako4>();
		} break;

		case 1700:
		{
			cObject* a = OBJECT->Create("Zako4", Vector2(192, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(2200);
			a->GetComponent<cZako>()->SetSpeed(250);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item6");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(192, 150));
			a->AddComponent<cTimeLine_Zako2>();
		} break;

		case 1900:
		case 2700:
		{
			for (int i = 0; i < 2; i++)
			{
				cObject* a = OBJECT->Create("Zako5", Vector2(75 + i * 234, -16), -1, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(850);
				a->GetComponent<cZako>()->SetSpeed(300);
				a->GetComponent<cZako>()->SetFriction(0.97);
				a->GetComponent<cZako>()->AddDrop("Item3");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(75 + i * 234, 300));
				a->AddComponent<cTimeLine_Zako3>()->SetRotate(i == 0 ? 1 : -1);
			}
		} break;

		case 2200:
		{
			for (int i = -1; i < 2; i++)
			{
				cObject* a = OBJECT->Create("Zako1", Vector2(192 + i * 75, -16), -1, Tag::Enemy);
				a->AddComponent<cZako>()->SetHp(600);
				a->GetComponent<cZako>()->SetSpeed(200 - abs(i) * 75);
				a->GetComponent<cZako>()->SetFriction(0.97);
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cZako>()->AddDrop("Item1");
				a->GetComponent<cPath>()->AddPath(Vector2(192 + i * 75, -16), Vector2(192 + i * 75, 400));
				a->AddComponent<cTimeLine_Zako1>();
			}
		} break;

		case 2500:
		{
			cObject* a = OBJECT->Create("Zako4", Vector2(192, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(2250);
			a->GetComponent<cZako>()->SetSpeed(250);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item3");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(192, 150));
			a->AddComponent<cTimeLine_Zako5>();
		} break;

		case 2900:
		{
			cObject* a = OBJECT->Create("Zako4", Vector2(192, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(5000);
			a->GetComponent<cZako>()->SetSpeed(250);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item3");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(192, 150));
			a->AddComponent<cTimeLine_Zako8>();
		} break;

		case 3400:
		case 3420:
		case 3440:
		case 3460:
		case 3480:
		case 3500:
		case 3520:
		case 3540:
		case 3560:
		case 3580:
		case 3600:
		case 3620:
		case 3640:
		case 3660:
		case 3680:
		case 3700:
		case 3720:
		case 3740:
		case 3760:
		case 3780:
		case 3800:
		case 3820:
		case 3840:
		case 3860:
		case 3880:
		case 3900:
		case 3920:
		case 3940:
		case 3960:
		case 3980:
		case 4000:
		{
			cObject* a = OBJECT->Create("Zako6", Vector2(-16, rand() % 250), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(10);
			a->GetComponent<cZako>()->SetSpeed(500);
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(414, rand() % 250));
			a->AddComponent<cTimeLine_Zako6>();
		} break;

		case 3410:
		case 3430:
		case 3450:
		case 3470:
		case 3490:
		case 3510:
		case 3530:
		case 3550:
		case 3570:
		case 3590:
		case 3610:
		case 3630:
		case 3650:
		case 3670:
		case 3690:
		case 3710:
		case 3730:
		case 3750:
		case 3770:
		case 3790:
		case 3810:
		case 3830:
		case 3850:
		case 3870:
		case 3890:
		case 3910:
		case 3930:
		case 3950:
		case 3970:
		case 3990:
		case 4010:
		{
			cObject* a = OBJECT->Create("Zako6", Vector2(400, rand() % 250), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(10);
			a->GetComponent<cZako>()->SetSpeed(500);
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(-30, rand() % 250));
			a->AddComponent<cTimeLine_Zako6>();
		} break;

		case 4200:
		{
			cObject* a = OBJECT->Create("Zako4", Vector2(192, -16), -1, Tag::Enemy);
			a->AddComponent<cZako>()->SetHp(12500);
			a->GetComponent<cZako>()->SetSpeed(250);
			a->GetComponent<cZako>()->SetFriction(0.97);
			a->GetComponent<cZako>()->AddDrop("Item6");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cZako>()->AddDrop("Item1");
			a->GetComponent<cPath>()->AddPath(a->GetPosition(), Vector2(192, 150));
			a->AddComponent<cTimeLine_Zako7>();
		} break;

		case 5300:
		{
			cObject* a = OBJECT->Create("Remi", Vector2(192, -16), -6, Tag::Enemy);
			a->AddComponent<cRemi>();
		} break;


		}
	}
	m_Last = (int)m_Time;
	m_Time += TimeSpeed;

}

void cIngameScene::Render()
{
	IMAGE->Render(m_Texture_Background, 0, m_Background_y);

	cObject* Boss = OBJECT->GetBoss();
	if (Boss)
	{
		if (Boss->GetComponent<cRemi>())
		{
			if (Boss->GetComponent<cRemi>()->GetPhase() == 1)
			{
				IMAGE->Render(m_Texture_Remi, Vector2(192, 240), Vector2(2.5, 2.5), (int)(GetTickCount()) * 0.0005);
			}
		}
		else
		{
			if (Boss->GetComponent<cFlan>()->GetPhase() % 2 == 1)
			{
				IMAGE->Render(m_Texture_Flan, Vector2(192, 240), Vector2(2.5, 2.5), 0);
			}
		}
	}

	if (SYSTEM->GetTimeSpeed() != 1)
	{
		if (m_Slow_Alpha != 255) m_Slow_Alpha += 17;
		else if(OBJECT->GetPlayer()) OBJECT->GetPlayer()->GetComponent<cPlayer>()->SetSlowable(true);
	}
	else
	{
		if (m_Slow_Alpha != 0) m_Slow_Alpha -= 17;
		else if (OBJECT->GetPlayer()) OBJECT->GetPlayer()->GetComponent<cPlayer>()->SetSlowable(true);
	}
	if (m_Slow_Alpha != 0)
	{
		IMAGE->Render(m_Texture_Slow, Vector2(192, 240), Vector2(2.5, 2.5), (int)(GetTickCount()) * 0.0005, D3DCOLOR_ARGB((int)m_Slow_Alpha, 255, 255, 255));
	}

	if (Boss)
	{
		IMAGE->Render(m_Texture_Enemy, Boss->GetPosition().x - 24, 464);
	}
}
