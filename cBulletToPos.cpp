#include "DXUT.h"
#include "cBulletToPos.h"

cBulletToPos::cBulletToPos(cObject* Object)
	:cComponent(Object)
{
}


cBulletToPos::~cBulletToPos()
{
}

void cBulletToPos::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_IsEnemy = true;
	m_TargetObj = nullptr;
	m_Grazed = false;
	m_Dir = 0;
	m_TargetPos = Vector2(m_pObject->GetPosition().x, -100);
	m_FirstTarget = "";
}

void cBulletToPos::Update()
{
	m_Dir = atan2(m_TargetPos.y - m_pObject->GetPosition().y, m_TargetPos.x - m_pObject->GetPosition().x);
	if (m_TargetObj != nullptr)
	{
		m_TargetPos = m_TargetObj->GetPosition();
		if (m_TargetObj->GetDestroyed() || m_TargetObj->GetName() != m_FirstTarget)
		{
			m_TargetObj = nullptr;
			m_FirstTarget = "";
			m_TargetPos = Vector2(1000 * cos(m_Dir), 1000 * sin(m_Dir));
		}
	}
	m_pObject->Translate(Vector2(m_Speed * cos(m_Dir) * DeltaTime, m_Speed * sin(m_Dir) * DeltaTime));
	m_pObject->SetRotate(m_Dir - D3DXToRadian(270));
	IsOutMap();
}

void cBulletToPos::Render()
{

}

void cBulletToPos::Release()
{

}

void cBulletToPos::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 16 < 0
		|| Pos.x - 16 > 384
		|| Pos.y + 16 < 0
		|| Pos.y - 16 > 480) m_pObject->Destroy();
}
