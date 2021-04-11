#include "DXUT.h"
#include "cTimeLine_Flan4.h"
#include "cItem.h"
#include "cFlan.h"

cTimeLine_Flan4::cTimeLine_Flan4(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan4::~cTimeLine_Flan4()
{
}

void cTimeLine_Flan4::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice3");
	m_Effect[0] = IMAGE->FindImage("Bullet_FireEffect2");
	m_Effect[1] = IMAGE->FindImage("Bullet_CreateEffect2");
	m_Owner = m_pObject->GetComponent<cFlan>();
	m_LaserDir = 0;
	m_LaserSpeed = 0;
	m_LaserOn = false;
	m_Timing = 0;
}

void cTimeLine_Flan4::Update()
{
	for (auto& iter = m_Laser.begin(); iter != m_Laser.end();)
	{
		(*iter)->Destroy();
		iter = m_Laser.erase(iter);
	}
	m_Laser.clear();
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			SOUND->Play("Laser1");
			m_Timing = 2;
			m_LaserOn = true;
			m_LaserDir = 200;
			m_LaserSpeed = 2.5;
			m_BulletDir = 90;
		} break;

		case 200:
		{
			m_LaserOn = false;
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(0, 64));
			m_Owner->SetFriction(0.977);
			m_Owner->SetSpeed(350);
		} break;

		case 280:
		{
			SOUND->Play("Laser1");
			m_Timing = -20;
			m_LaserOn = true;
			m_LaserDir = 90;
			m_LaserSpeed = 0;
			m_BulletDir = -90;
		} break;

		case 308:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(384, 114));
			m_Owner->SetFriction(0.983);
			m_Owner->SetSpeed(600);
		} break;

		case 360:
		{
			m_LaserOn = false;
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(384, 64));
			m_Owner->SetFriction(0.985);
			m_Owner->SetSpeed(250);
		} break;

		case 400:
		{
			SOUND->Play("Laser1");
			m_Timing = -20;
			m_LaserOn = true;
			m_LaserDir = 90;
			m_LaserSpeed = 0;
			m_BulletDir = 90;
		} break;

		case 418:
		{
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(0, 114));
			m_Owner->SetFriction(0.983);
			m_Owner->SetSpeed(600);
		} break;

		case 478:
		{
			SOUND->Play("Laser1");
			m_pObject->GetComponent<cPath>()->Clear();
			m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), Vector2(210, 120));
			m_Owner->SetFriction(0.99);
			m_Owner->SetSpeed(250);
			m_Timing = 2;
			m_LaserDir = 340;
			m_LaserSpeed = -2.5;
			m_BulletDir = -90;
		} break;

		case 578:
		{
			m_LaserOn = false;
		} break;

		case 630:
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
	m_LaserDir += m_LaserSpeed * m_TimeSpeed;

	if (m_LaserOn)
	{
		float m_Pos;
		for (m_Pos = 0; true; m_Pos += 8)
		{
			Vector2 Pos = m_pObject->GetPosition() + Vector2(m_Pos * cos(D3DXToRadian(m_LaserDir)), m_Pos * sin(D3DXToRadian(m_LaserDir)));
			if ((int)m_Pos % 48 == 8 && (int)m_Timing == 6)
			{
				cEffect* a = EFFECT->Create(m_Effect[0], Pos, Vector2(1, 1), -10);
				EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
				EFFECT->AlphaSetting(a, 500, -25);
				m_Owner->AddBullet(Pos, 25, 150, 1.03, m_LaserDir + m_BulletDir, 4, m_Bullet);
				m_Owner->AddBullet(m_pObject->GetPosition() + Vector2(m_Pos * cos(D3DXToRadian(m_LaserDir - m_LaserSpeed)), m_Pos * sin(D3DXToRadian(m_LaserDir - m_LaserSpeed))), 25, 150, 1.03, m_LaserDir + m_BulletDir, 4, m_Bullet);
			}
			if (Pos.x > 0 && Pos.x < 384 && Pos.y > 0 && Pos.y < 480)
			{
				cObject* a = m_Owner->AddBullet(Vector2(0, 0), 0, 0, 4, m_Bullet);
				a->SetPosition(m_pObject->GetPosition() + Vector2(m_Pos * cos(D3DXToRadian(m_LaserDir)), m_Pos * sin(D3DXToRadian(m_LaserDir))));
				a->GetComponent<cRenderer>()->SetEnable(false);
				m_Laser.push_back(a);
			}
			else break;
		}
		if (m_Last != (int)m_Time)
		{
			cEffect* a = EFFECT->Create(m_Effect[1], m_pObject->GetPosition() + Vector2(240 * cos(D3DXToRadian(m_LaserDir)), 240 * sin(D3DXToRadian(m_LaserDir))), Vector2(16, 1), -9);
			EFFECT->MovementSetting(a, 0, 0, 0, D3DXToRadian(m_LaserDir));
			EFFECT->SizeSetting(a, Vector2(0, -0.15));
		}
	}
	if ((int)m_Timing == 6)
	{
		m_Timing = 0;
		if(m_LaserOn) SOUND->Play("BulletShot2", 0.5f);
	}
}

void cTimeLine_Flan4::Render()
{
	
}

void cTimeLine_Flan4::Release()
{

}
