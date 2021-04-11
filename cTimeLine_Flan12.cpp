#include "DXUT.h"
#include "cTimeLine_Flan12.h"
#include "cItem.h"
#include "cFlan.h"
#include "cTimeLine_BossPower.h"
#include "cBullet_Bounce.h"

cTimeLine_Flan12::cTimeLine_Flan12(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_Flan12::~cTimeLine_Flan12()
{
}

void cTimeLine_Flan12::Init()
{
	m_Time = 0;
	m_Bullet = IMAGE->FindImage("Bullet_Rice7");
	m_Owner = m_pObject->GetComponent<cFlan>();
	m_Timing = 89;
}

void cTimeLine_Flan12::Update()
{
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 100:
		{
			m_pObject->GetComponent<cTimeLine_BossPower>()->SetEnable(true);
		} break;

		case 160:
		{
			m_Speed = 250;
		}

		}

		m_Timing++;
		if (m_Timing == m_Speed)
		{
			SOUND->Play("BulletShot2");
			if(m_Speed > 40) m_Speed -= 7;
			m_Timing = 0;
			Vector2 Pos = Vector2((rand() % 300) + 42, (rand() % 150) + 50);
			for (int i = 0; i < 360; i += 4)
			{
				cObject* a = m_Owner->AddBullet(Pos, 100, i, 4, m_Bullet);
				a->AddComponent<cBullet_Bounce>()->SetCollAt(true, true, false, true);
				a->GetComponent<cBullet_Bounce>()->SetMaxColl(1);
			}
		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_Flan12::Render()
{

}

void cTimeLine_Flan12::Release()
{

}
