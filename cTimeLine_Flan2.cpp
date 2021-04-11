#include "DXUT.h"
#include "cTimeLine_Flan2.h"
#include "cItem.h"
#include "cFlan.h"

cTimeLine_Flan2::cTimeLine_Flan2(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan2::~cTimeLine_Flan2()
{
}

void cTimeLine_Flan2::Init()
{
	m_Time = 0;
	m_Bullet[0] = IMAGE->FindImage("Bullet_Ring4");
	m_Bullet[1] = IMAGE->FindImage("Bullet_Circle7");
	m_Effect[0] = IMAGE->FindImage("Bullet_FireEffect3");
	m_Effect[0] = IMAGE->FindImage("Bullet_FireEffect4");
	m_Spawner = IMAGE->FindImage("Enemy_Circle");
	m_Owner = m_pObject->GetComponent<cFlan>();
	m_Timing = 0;
}

void cTimeLine_Flan2::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 0),1.570796,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 480),4.712388,500,0.99, 1 });
			
		} break;

		case 195:
		{
			m_Spawners[0].Direction = 0;
			m_Spawners[0].Speed = 400;
			m_Spawners[1].Direction = 3.141592;
			m_Spawners[1].Speed = 400;
		} break;

		case 210:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 480),4.712388,500,0.99, 2 });
			m_Spawners.push_back(Spawner{ Vector2(384, 0),1.570796,500,0.99, 2 });
		} break;

		case 295:
		{
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
		} break;

		case 300:
		{
			m_Spawners[0].Direction = 0;
			m_Spawners[0].Speed = 400;
			m_Spawners[1].Direction = 3.141592;
			m_Spawners[1].Speed = 400;
		} break;

		case 320:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 0),1.570796,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 480),4.712388,500,0.99, 1 });
		} break;

		case 390:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 480),4.712388,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 0),1.570796,500,0.99, 1 });
		} break;

		case 400:
		{
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
		} break;

		case 420:
		{
			m_Spawners[0].Direction = 0;
			m_Spawners[0].Speed = 400;
			m_Spawners[1].Direction = 3.141592;
			m_Spawners[1].Speed = 400;
		} break;

		case 515:
		{
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
		} break;

		case 540:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 0),1.570796,500,0.99, 2 });
			m_Spawners.push_back(Spawner{ Vector2(0, 480),4.712388,500,0.99, 2 });
			m_Spawners.push_back(Spawner{ Vector2(384, 480),4.712388,500,0.99, 2 });
			m_Spawners.push_back(Spawner{ Vector2(384, 0),1.570796,500,0.99, 2 });
		} break;

		case 630:
		{
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
		} break;

		case 660:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 0),1.570796,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(0, 480),4.712388,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 480),4.712388,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 0),1.570796,500,0.99, 1 });
		} break;

		case 665:
		{
			m_Spawners.push_back(Spawner{ Vector2(0, 0),1.570796,500,0.99, 1 });
			m_Spawners.push_back(Spawner{ Vector2(384, 480),4.712388,500,0.99, 1 });
		} break;

		case 760:
		{
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
			m_Spawners.erase(m_Spawners.begin());
		} break;

		case 770:
		{
			m_Time = 99;
			break;
		}

		}
	}
	float m_TimeSpeed = SYSTEM->GetTimeSpeed();
	m_Last = (int)m_Time;
	m_Time += m_TimeSpeed;
	m_Timing += m_TimeSpeed;
	
	if (m_Last % 250 == 100)
	{
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2((rand() % 300) + 42, (rand() % 150) + 25));
		m_Owner->SetFriction(0.985);
		m_Owner->SetSpeed(200);
	}
	for (auto& iter = m_Spawners.begin(); iter != m_Spawners.end();)
	{
		if ((int)m_Timing == 12)
		{
			if ((*iter).Pattern == 1)
			{
				m_Owner->AddBullet((*iter).Pos, 90, D3DXToDegree(atan2(240 - (*iter).Pos.y, 192 - (*iter).Pos.x)), 5, m_Bullet[0]);
			}
			if ((*iter).Pattern == 2)
			{
				Vector2 PlayerPos;
				if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
				else PlayerPos = Vector2(192, 480);
				m_Owner->AddBullet((*iter).Pos, 90, D3DXToDegree(atan2(PlayerPos.y - (*iter).Pos.y, PlayerPos.x - (*iter).Pos.x)), 5, m_Bullet[1]);
			}
		}
		(*iter).Pos.x += (*iter).Speed * cos((*iter).Direction) * DeltaTime * m_TimeSpeed;
		(*iter).Pos.y += (*iter).Speed * sin((*iter).Direction) * DeltaTime * m_TimeSpeed;
		(*iter).Speed *= 1 - (1 - (*iter).Friction) * SYSTEM->GetTimeSpeed();
		if ((*iter).Pos.x < -0.1)
		{
			(*iter).Pos = Vector2(0, (*iter).Pos.y);
			(*iter).Speed = 0;
		}
		else if ((*iter).Pos.x > 384.1)
		{
			(*iter).Pos = Vector2(384, (*iter).Pos.y);
			(*iter).Speed = 0;
		}
		else if ((*iter).Pos.y < -0.1)
		{
			(*iter).Pos = Vector2((*iter).Pos.x, 0);
			(*iter).Speed = 0;
		}
		else if((*iter).Pos.y > 480.1)
		{
			(*iter).Pos = Vector2((*iter).Pos.x, 480);
			(*iter).Speed = 0;
		}
		iter++;
	}
	if ((int)m_Timing == 12) m_Timing = 0;
}

void cTimeLine_Flan2::Render()
{
	for (auto iter : m_Spawners)
	{
		IMAGE->Render(m_Spawner, iter.Pos, Vector2(1, 1), 0, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
}

void cTimeLine_Flan2::Release()
{

}
