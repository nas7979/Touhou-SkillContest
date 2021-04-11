#include "DXUT.h"
#include "cTimeLine_Flan8.h"
#include "cItem.h"
#include "cFlan.h"
#include "cTimeLine_BossPower.h"
#include "cBullet_Flan8.h"

cTimeLine_Flan8::cTimeLine_Flan8(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan8::~cTimeLine_Flan8()
{
}

void cTimeLine_Flan8::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_Ring10");
	m_Bullet[1] = IMAGE->FindImage("Bullet_LargeRing4");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect6");
	m_Owner = m_pObject->GetComponent<cFlan>();
}

void cTimeLine_Flan8::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			m_pObject->GetComponent<cTimeLine_BossPower>()->SetEnable(true);
		} break;

		case 200:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(70,0),0,1.570796 });
		} break;

		case 204:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,270),0,3.141592 });
		}break;

		case 207:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,160),0,0 });
		} break;

		case 211:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(314,480),0,4.712388 });
		} break;

		case 213:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(140,0),0,1.570796 });
		} break;

		case 216:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,340),0,3.141592 });
		} break;

		case 220:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,190),0,0 });
		} break;

		case 223:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(244,480),0,4.712388 });
		} break;

		case 226:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,50),0,3.141592 });
		} break;

		case 230:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,130),0,0 });
		} break;

		case 330:
		case 470:
		case 590:
		{
			SOUND->Play("BulletShot2");
			cObject* a = OBJECT->Create("Bullet_Flan8", m_pObject->GetPosition(), 10, Tag::None);
			a->AddComponent<cBullet_Flan8>()->SetOwner(m_Owner->AddBullet(m_pObject->GetPosition(), 125, 20 + (rand() % 140), 15, m_Bullet[1]));
		} break;

		case 370:
		{
			SOUND->Play("BulletShot2");
			cObject* a = OBJECT->Create("Bullet_Flan8", m_pObject->GetPosition(), 10, Tag::None);
			a->AddComponent<cBullet_Flan8>()->SetOwner(m_Owner->AddBullet(m_pObject->GetPosition(), 125, 20 + (rand() % 140), 15, m_Bullet[1]));
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(200);
		} break;

		case 390:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,0),0,2.356194 });
		} break;

		case 395:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,120),0,2.356194 });
		} break;

		case 400:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(384,240),0,2.356194 });
		} break;

		case 510:
		case 630:
		{
			SOUND->Play("BulletShot2");
			Vector2 PlayerPos;
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int i = -50; i <= 50; i += 50)
			{
				cObject* a = OBJECT->Create("Bullet_Flan8", m_pObject->GetPosition(), 10, Tag::None);
				a->AddComponent<cBullet_Flan8>()->SetOwner(m_Owner->AddBullet(m_pObject->GetPosition(), 125, Dir + i, 15, m_Bullet[1]));
			}
		} break;

		case 550:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,0),0,0.785398 });
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(200);
		} break;

		case 555:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,120),0,0.785398 });
		} break;

		case 560:
		{
			m_Spawners.push_back(WallSpawner{ Vector2(0,240),0,0.785398 });
		} break;

		case 670:
		{
			m_Time = 99;
		} break;

		}
	}
	float m_TimeSpeed = SYSTEM->GetTimeSpeed();
	m_Last = (int)m_Time;
	m_Time += m_TimeSpeed;

	for (auto& iter = m_Spawners.begin(); iter != m_Spawners.end();)
	{
		if ((int)(*iter).Timing == 6)
		{
			SOUND->Play("BulletShot2", 0.3f);
			cEffect* a = EFFECT->Create(m_Effect, (*iter).Pos, Vector2(1, 1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
			m_Owner->AddBullet((*iter).Pos, 0, 75, 1.05, 0, 5, m_Bullet[0]);
			(*iter).Timing = 0;
			(*iter).Pos += Vector2(20 * cos((*iter).Direction), 20 * sin((*iter).Direction));
		}
		(*iter).Timing += m_TimeSpeed;
		if ((*iter).Pos.x < 0 || (*iter).Pos.x > 384 || (*iter).Pos.y < 0 || (*iter).Pos.y > 480)
		{
			iter = m_Spawners.erase(iter);
		}
		else iter++;
	}
}

void cTimeLine_Flan8::Render()
{

}

void cTimeLine_Flan8::Release()
{

}
