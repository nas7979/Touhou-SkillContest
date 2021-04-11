#include "DXUT.h"
#include "cBullet_Bounce.h"

cBullet_Bounce::cBullet_Bounce(cObject* Object)
	:cComponent(Object)
{
}


cBullet_Bounce::~cBullet_Bounce()
{
}

void cBullet_Bounce::Init()
{
	m_Owner = m_pObject->GetComponent<cBullet>();
	m_Colled = 0;
	m_MaxColl = 3;
}

void cBullet_Bounce::Update()
{
	if (m_Colled < m_MaxColl)
	{
		int Size = m_pObject->GetComponent<cRenderer>()->GetImage()->info.Width * 0.5;
		if (m_pObject->GetPosition().y - Size <= 0 && m_CollAt[0])
		{
			m_Owner->SetDirection(m_Owner->GetDirection() * -1);
			m_Colled++;
		}
		else if ((m_pObject->GetPosition().x - Size <= 0 && m_CollAt[1]) || (m_pObject->GetPosition().x + Size >= 384 && m_CollAt[3]))
		{
			if(m_Owner->GetDirection() <= 180) m_Owner->SetDirection(90 - (m_Owner->GetDirection() - 90));
			else m_Owner->SetDirection(270 + (270 - m_Owner->GetDirection()));
			m_Colled++;
		}
	}
}

void cBullet_Bounce::Render()
{

}

void cBullet_Bounce::Release()
{

}
