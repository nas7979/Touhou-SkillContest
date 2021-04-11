#include "DXUT.h"
#include "cTimeLine_Zako4.h"
#include "cItem.h"
#include "cZako.h"

cTimeLine_Zako4::cTimeLine_Zako4(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Zako4::~cTimeLine_Zako4()
{
}

void cTimeLine_Zako4::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Been15");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect7");
	m_Owner = m_pObject->GetComponent<cZako>();
}

void cTimeLine_Zako4::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 5:
		case 75:
		case 145:
		{
			if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
			else PlayerPos = Vector2(192, 480);
			SOUND->Play("BulletShot2");
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(0.1, 0.1), -10);
			EFFECT->SizeSetting(a, Vector2(0.15, 0.15));
			EFFECT->AlphaSetting(a, 500, -25);
		}
		case 10:
		case 15:
		case 80:
		case 85:
		case 150:
		case 155:
		{
			float Dir = D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x));
			for (int i = 0; i < 360; i += 40)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 800, 400, 0.8, Dir + i, 4, m_Bullet);
			}
			break;
		}

		case 180:
		{
			m_Owner->SetFriction(1.008);
			m_Owner->SetSpeed(65);
		} break;
		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Zako4::Render()
{

}

void cTimeLine_Zako4::Release()
{

}
