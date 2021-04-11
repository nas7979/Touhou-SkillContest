#include "DXUT.h"
#include "cBullet.h"

cBullet::cBullet(cObject* Object)
	:cComponent(Object)
{
}


cBullet::~cBullet()
{
}

void cBullet::Init()
{
	m_pObject->AddComponent<cRenderer>();
	m_pObject->AddComponent<cCircleCollider>();
	m_IsEnemy = true;
	m_Grazed = false;
}

void cBullet::Update()
{
	m_pObject->Translate(Vector2(m_Speed * cos(D3DXToRadian(m_Dir)) * DeltaTime, m_Speed * sin(D3DXToRadian(m_Dir)) * DeltaTime));
	m_pObject->SetRotate(D3DXToRadian(m_Dir - 270));
	IsOutMap();
}

void cBullet::Render()
{
	
}

void cBullet::Release()
{

}

void cBullet::IsOutMap()
{
	Vector2 Pos = m_pObject->GetPosition();
	int Size = m_pObject->GetComponent<cRenderer>()->GetImage()->info.Width * 0.5;
	if (Pos.x + Size < 0
		|| Pos.x - Size > 384
		|| Pos.y + Size < 0
		|| Pos.y - Size > 480) m_pObject->Destroy();
}
