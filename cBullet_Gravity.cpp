#include "DXUT.h"
#include "cBullet_Gravity.h"

cBullet_Gravity::cBullet_Gravity(cObject* Object)
	:cComponent(Object)
{
}


cBullet_Gravity::~cBullet_Gravity()
{
}

void cBullet_Gravity::Init()
{
	m_Owner = m_pObject->GetComponent<cBullet>();
}

void cBullet_Gravity::Update()
{
	m_Owner->SetSpeed(m_Owner->GetSpeed() + m_Gravity * SYSTEM->GetTimeSpeed());
}

void cBullet_Gravity::Render()
{

}

void cBullet_Gravity::Release()
{

}
