#include "DXUT.h"
#include "cBullet_Remi2_1.h"
#include "cBulletFriction.h"

cBullet_Remi2_1::cBullet_Remi2_1(cObject* Object)
	:cComponent(Object)
{
}


cBullet_Remi2_1::~cBullet_Remi2_1()
{
}

void cBullet_Remi2_1::Init()
{
	m_Owner = m_pObject->GetComponent<cBullet>();
	m_Dir = m_Owner->GetDirection();
	m_FirstDir = m_Dir;
	m_Delay = -50;
	m_Bullet = IMAGE->FindImage("Bullet_Circle2");
}

void cBullet_Remi2_1::Update()
{
	float TimeSpeed = SYSTEM->GetTimeSpeed();
	if (m_Last != (int)m_Delay && !m_pObject->GetDestroyed())
	{
		if (m_Pattern == 0)
		{
			if (m_FirstDir - m_Dir <= 110)
			{
				m_Dir -= 1.5 * TimeSpeed;
			}
			m_Owner->SetDirection(m_Dir);

			if ((int)abs(m_Delay) % 7 == 0)
			{
				cObject* a = OBJECT->Create("EnemyBullet", m_pObject->GetPosition(), -10, Tag::Bullet);
				a->AddComponent<cBulletFriction>()->SetSpeed(0);
				a->GetComponent<cBulletFriction>()->SetDirection(m_FirstDir + m_Delay);
				a->GetComponent<cBulletFriction>()->SetFriction(1.003 + abs(m_Delay * 0.0002));
				a->GetComponent<cBulletFriction>()->SetEndSpeed(100);
				a->GetComponent<cRenderer>()->SetImage(m_Bullet);
				a->GetComponent<cCircleCollider>()->SetRadius(5);
			}
		}
		else if (m_Pattern == 1)
		{
			if (m_Dir - m_FirstDir <= 110)
			{
				m_Dir += 1.5 * TimeSpeed;
			}
			m_Owner->SetDirection(m_Dir);

			if ((int)abs(m_Delay) % 7 == 0)
			{
				cObject* a = OBJECT->Create("EnemyBullet", m_pObject->GetPosition(), -10, Tag::Bullet);
				a->AddComponent<cBulletFriction>()->SetSpeed(0);
				a->GetComponent<cBulletFriction>()->SetDirection(rand() % 360);
				a->GetComponent<cBulletFriction>()->SetFriction(1.01);
				a->GetComponent<cBulletFriction>()->SetEndSpeed(100);
				a->GetComponent<cRenderer>()->SetImage(m_Bullet);
				a->GetComponent<cCircleCollider>()->SetRadius(5);
			}
		}
		else
		{
			if ((int)abs(m_Delay) % 11 == 0)
			{
				cObject* a = OBJECT->Create("EnemyBullet", m_pObject->GetPosition(), -10, Tag::Bullet);
				a->AddComponent<cBulletFriction>()->SetSpeed(0);
				a->GetComponent<cBulletFriction>()->SetDirection(rand() % 360);
				a->GetComponent<cBulletFriction>()->SetFriction(1.01);
				a->GetComponent<cBulletFriction>()->SetEndSpeed(100);
				a->GetComponent<cRenderer>()->SetImage(m_Bullet);
				a->GetComponent<cCircleCollider>()->SetRadius(5);
			}
		}
	}
	m_Last = (int)m_Delay;
	m_Delay += TimeSpeed;
}

void cBullet_Remi2_1::Render()
{

}

void cBullet_Remi2_1::Release()
{

}
