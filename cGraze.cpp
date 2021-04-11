#include "DXUT.h"
#include "cGraze.h"
#include "cPlayer.h"
#include "cBullet.h"
#include "cBulletFriction.h"
#include "cBulletToPos.h"

cGraze::cGraze(cObject* Object)
	:cComponent(Object)
{
}


cGraze::~cGraze()
{
}

void cGraze::Init()
{
	m_pObject->AddComponent<cCircleCollider>()->SetRadius(25);
	m_pObject->GetComponent<cCircleCollider>()->AddListName("EnemyBullet");
	m_pObject->GetComponent<cCircleCollider>()->AddListTag(Tag::Item);
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void
	{
		if (m_Player->GetComponent<cCircleCollider>()->GetEnable())
		{
			bool Grazed = true;
			cBulletFriction* Friction = Other->GetComponent<cBulletFriction>();
			cBullet* Normal = Other->GetComponent<cBullet>();
			cBulletToPos* ToPos = Other->GetComponent<cBulletToPos>();
			if (Friction != nullptr)
			{
				if (!Friction->GetGrazed())
				{
					Friction->SetGrazed(true);
					Grazed = false;
				}
			}
			if (Normal != nullptr)
			{
				if (!Normal->GetGrazed())
				{
					Normal->SetGrazed(true);
					Grazed = false;
				}
			}
			if (ToPos != nullptr)
			{
				if (!ToPos->GetGrazed())
				{
					ToPos->SetGrazed(true);
					Grazed = false;
				}
			}
			if (!Grazed)
			{
				SYSTEM->AddScore(2000);
				SYSTEM->AddGraze();
				SYSTEM->AddGage(1);
				char Name[7];
				sprintf(Name, "Graze%d", (rand() % 4) + 1);
				cEffect* a = EFFECT->Create(string(Name), m_pObject->GetPosition(), Vector2(0.5, 0.5), 10);
				EFFECT->AlphaSetting(a, 200, -10);
				EFFECT->MovementSetting(a, 300 + (rand() % 100), rand() % 360, 0.94, 0);
				SOUND->Play("Graze");
			}
		}
	});
}

void cGraze::Update()
{
	m_Player = OBJECT->GetPlayer();
	if (m_Player)
	{
		if (m_Player->GetComponent<cPlayer>()->Dead)
		{
			m_pObject->GetComponent<cCircleCollider>()->SetEnable(false);
		}
		else
		{
			m_pObject->GetComponent<cCircleCollider>()->SetEnable(true);
		}
		m_pObject->SetPosition(m_Player->GetPosition());
	}
}

void cGraze::Render()
{

}

void cGraze::Release()
{

}