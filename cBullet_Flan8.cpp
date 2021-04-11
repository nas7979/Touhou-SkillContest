#include "DXUT.h"
#include "cBullet_Flan8.h"
#include "cBulletFriction.h"

cBullet_Flan8::cBullet_Flan8(cObject* Object)
	:cComponent(Object)
{
}


cBullet_Flan8::~cBullet_Flan8()
{
}

void cBullet_Flan8::Init()
{
	m_pObject->AddComponent<cCircleCollider>()->SetRadius(32);
	m_pObject->GetComponent<cCircleCollider>()->AddListName("EnemyBullet");
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void
	{
		if (Other->GetComponent<cBulletFriction>())
		{
			float Dist = Math::PointDistance(m_pObject->GetPosition(), Other->GetPosition());
			if (Other->GetComponent<cBulletFriction>()->GetSpeed() == 0)
			{
				Other->GetComponent<cBulletFriction>()->SetDirection(D3DXToDegree(atan2(Other->GetPosition().y - m_pObject->GetPosition().y, Other->GetPosition().x - m_pObject->GetPosition().x)));
				Other->GetComponent<cBulletFriction>()->SetSpeed(10 - Dist * 0.2);
			}
		}
	});
}

void cBullet_Flan8::Update()
{
	m_pObject->SetPosition(m_Owner->GetPosition());
	IsOutMap();
}

void cBullet_Flan8::Render()
{

}

void cBullet_Flan8::Release()
{

}

void cBullet_Flan8::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 8 < 0
		|| Pos.x - 8 > 384
		|| Pos.y + 8 < 0
		|| Pos.y - 8 > 480) m_pObject->Destroy();
}