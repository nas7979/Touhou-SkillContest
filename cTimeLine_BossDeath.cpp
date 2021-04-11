#include "DXUT.h"
#include "cTimeLine_BossDeath.h"
#include "cFlan.h"
#include "cItem.h"
#include "cFace.h"

cTimeLine_BossDeath::cTimeLine_BossDeath(cObject* Object)
	:cComponent(Object)
{
}

cTimeLine_BossDeath::~cTimeLine_BossDeath()
{
}

void cTimeLine_BossDeath::Init()
{
	m_Time = 0;
}

void cTimeLine_BossDeath::Update()
{
	for (int i = 0; i < 15; i++)
	{
		char Name[12];
		sprintf(Name, "BossEffect%d", (rand() % 4) + 1);
		cEffect* a = EFFECT->Create(string(Name), m_pObject->GetPosition(), Vector2(1.5, 1.5) * ((rand() % 20) + 1) * 0.1, -10);
		EFFECT->AlphaSetting(a, (rand() % 100) + 250, -((rand() % 10) + 15));
		EFFECT->MovementSetting(a, (rand() % 300) + 750, rand() % 360, 0.95 - (rand() % 10) * 0.008, 0);
		EFFECT->SizeSetting(a, Vector2(-0.05, -0.05));
	}
	if (m_Last != (int)m_Time)
	{
		switch ((int)m_Time)
		{
		case 0:
		case 10:
		case 20:
		case 30:
		case 40:
		case 50:
		case 60:
		case 70:
		case 80:
		{
			SOUND->Play("BulletShot1");
		} break;

		case 90:
		{
			SYSTEM->GotoWin();
			m_pObject->Destroy();
			OBJECT->SetBoss(nullptr);
			SOUND->Play("EnemyDeath2");
			SOUND->End("Flan_Thema");
			cEffect* a = EFFECT->Create(IMAGE->FindImage("Wave"), m_pObject->GetPosition(), Vector2(1, 1), 1);
			EFFECT->AlphaSetting(a, 500, -17);
			EFFECT->SizeSetting(a, Vector2(0.2, 0.2));
			OBJECT->With("Face", [&](cObject* Obj)->void {
				if (Obj->GetComponent<cFace>()->GetIsEnemy())
				{
					Obj->Destroy();
				}
			});
			OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
				Obj->Destroy();
				cObject* a = OBJECT->Create("Item5", Obj->GetPosition(), -11, Tag::Item);
				a->AddComponent<cItem>()->SetCollect(true);
			});
			if (SYSTEM->GetBonus())
			{
				SYSTEM->AddScore(m_pObject->GetComponent<cFlan>()->GetSpellBonus());
				cEffect* b = EFFECT->Create(IMAGE->FindImage("SpellBonus"), Vector2(192, 75), Vector2(1, 1), -20);
				EFFECT->AlphaSetting(b, 6000, -50);
				b = EFFECT->Create(IMAGE->FindImage("+"), Vector2(80, 100), Vector2(2, 2), -20);
				EFFECT->AlphaSetting(b, 6000, -50);
				EFFECT->ColorSetting(b, 255, 100, 100);
				char _Num[8];
				sprintf(_Num, "%d", m_pObject->GetComponent<cFlan>()->GetSpellBonus());
				string _Text = string(_Num);
				for (int i = 0; i < 7; i++)
				{
					char Text[2] = { _Text[i],NULL };
					b = EFFECT->Create(IMAGE->FindImage(&Text[0]), Vector2(112 + i * 32, 100), Vector2(2, 2), -20);
					EFFECT->AlphaSetting(b, 6000, -50);
					EFFECT->ColorSetting(b, 255, 100, 100);
				}
			}
			break;
		}

		}
	}
	m_Last = (int)m_Time;
	m_Time += SYSTEM->GetTimeSpeed();
}

void cTimeLine_BossDeath::Render()
{

}

void cTimeLine_BossDeath::Release()
{

}
