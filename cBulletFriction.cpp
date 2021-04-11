#include "DXUT.h"
#include "cBulletFriction.h"

cBulletFriction::cBulletFriction(cObject* Object)
	:cComponent(Object)
{
}


cBulletFriction::~cBulletFriction()
{
}

void cBulletFriction::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_Grazed = false;
}

void cBulletFriction::Update()
{
	m_pObject->Translate(Vector2(m_Speed * cos(D3DXToRadian(m_Dir)) * DeltaTime, m_Speed * sin(D3DXToRadian(m_Dir)) * DeltaTime));
	m_pObject->SetRotate(D3DXToRadian(m_Dir - 270));
	IsOutMap();
	if ((m_Speed >= m_EndSpeed && m_Friction <= 1)  || (m_Speed <= m_EndSpeed && m_Friction > 1)) m_Speed *= m_Friction;
	else m_Speed = m_EndSpeed;
}

void cBulletFriction::Render()
{

}

void cBulletFriction::Release()
{

}

void cBulletFriction::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	if (Pos.x + 16 < 0
		|| Pos.x - 16 > 384
		|| Pos.y + 16 < 0
		|| Pos.y - 16 > 680) m_pObject->Destroy();
}
