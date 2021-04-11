#include "DXUT.h"
#include "cItem.h"
#include "cZako.h"
#include "cTimeLine_Flan11_Zako.h"

cTimeLine_Flan11_Zako::cTimeLine_Flan11_Zako(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan11_Zako::~cTimeLine_Flan11_Zako()
{
}

void cTimeLine_Flan11_Zako::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Circle7");
	m_Effect = IMAGE->FindImage("Bullet_FireEffect4");
	m_Owner = m_pObject->GetComponent<cZako>();
	m_pObject->GetComponent<cRenderer>()->SetEnable(false);
	m_pObject->GetComponent<cCircleCollider>()->SetEnable(false);
	Vector2 PlayerPos;
	if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
	else PlayerPos = Vector2(192, 480);
	m_pObject->GetComponent<cPath>()->SetDirection(D3DXToDegree(atan2(PlayerPos.y - m_pObject->GetPosition().y, PlayerPos.x - m_pObject->GetPosition().x)));
	m_pObject->SetTag(Tag::None);
}

void cTimeLine_Flan11_Zako::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 10:
		{
			cEffect* a = EFFECT->Create(m_Effect, m_pObject->GetPosition(), Vector2(1, 1), -10);
			EFFECT->SizeSetting(a, Vector2(0.1, 0.1));
			EFFECT->AlphaSetting(a, 500, -30);
			for (int i = -1; i <= 1; i++)
			{
				m_Owner->AddBullet(m_pObject->GetPosition(), 40, D3DXToDegree(m_pObject->GetComponent<cPath>()->GetDirection()) + i * 25 + 180 + (rand() % 6) - 3, 5, m_Bullet);
			}
			m_Time = -1;
		} break;

		}
	}

	if (rand() % 100 == 50)
	{
		Vector2 PlayerPos;
		if (OBJECT->GetPlayer()) PlayerPos = OBJECT->GetPlayer()->GetPosition();
		else PlayerPos = Vector2(192, 480);
		m_pObject->GetComponent<cPath>()->Clear();
		m_pObject->GetComponent<cPath>()->AddPath(m_pObject->GetPosition(), PlayerPos);
		m_pObject->GetComponent<cZako>()->SetFriction(0.98);
		m_pObject->GetComponent<cZako>()->SetSpeed(Math::PointDistance(m_pObject->GetPosition(), PlayerPos));
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Flan11_Zako::Render()
{

}

void cTimeLine_Flan11_Zako::Release()
{

}
