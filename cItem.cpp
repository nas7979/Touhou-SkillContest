#include "DXUT.h"
#include "cItem.h"
#include "cPlayer.h"

cItem::cItem(cObject* Object)
	:cComponent(Object)
{
}


cItem::~cItem()
{
}

void cItem::Init()
{
	if (SYSTEM->GetPower() == 128)
	{
		if(m_pObject->GetName() == "Item1" || m_pObject->GetName() == "Item3")
		m_pObject->SetName("Item2");
	}
	else
	{
		if (m_pObject->GetName() == "Item2")
		m_pObject->SetName("Item1");
	}
	if (m_pObject->GetName() == "Item5")
	{
		cEffect* a = EFFECT->Create("", m_pObject->GetPosition(), Vector2(12, 1), 5);
		EFFECT->TextSetting(a, L"1000");
		EFFECT->AlphaSetting(a, 1000, -20);
		EFFECT->MovementSetting(a, 300, 270, 0.86, 0);
	}

	m_pObject->AddComponent<cRenderer>()->SetImage(IMAGE->FindImage(m_pObject->GetName()));
	m_pObject->AddComponent<cCircleCollider>()->SetRadius(5);
	m_pObject->GetComponent<cCircleCollider>()->SetCollFunc([&](cObject* Other)->void
	{
		if (m_pObject->GetName() == "Item2")
		{
			int Score = 50000 + (500 - m_pObject->GetPosition().y) * 100 + (m_pObject->GetPosition().y <= 150 ? 150000 : 0);
			SYSTEM->AddScore(Score);

			cEffect* a = EFFECT->Create("", Other->GetPosition(), Vector2(12, 1), 5);
			wchar_t Text[7];
			swprintf(Text, L"%d", Score);
			EFFECT->TextSetting(a, wstring(Text));
			EFFECT->AlphaSetting(a, 1000, -20);
			EFFECT->MovementSetting(a, 300, 270, 0.86, 0);
			if (Score >= 200000) EFFECT->ColorSetting(a, 255, 255, 0);
		}
		else if (m_pObject->GetName() == "Item1")
		{
			SYSTEM->AddPower(1);
			SYSTEM->AddScore(10);
			cEffect* a = EFFECT->Create("", Other->GetPosition(), Vector2(12, 1), 5);
			EFFECT->TextSetting(a, L"10");
			EFFECT->AlphaSetting(a, 1000, -20);
			EFFECT->MovementSetting(a, 300, 270, 0.86, 0);
		}
		else if (m_pObject->GetName() == "Item3")
		{
			SYSTEM->AddPower(8);
			SYSTEM->AddScore(10);
			cEffect* a = EFFECT->Create("", Other->GetPosition(), Vector2(12, 1), 5);
			EFFECT->TextSetting(a, L"10");
			EFFECT->AlphaSetting(a, 1000, -20);
			EFFECT->MovementSetting(a, 300, 270, 0.86, 0);
		}
		else if (m_pObject->GetName() == "Item6")
		{
			SYSTEM->AddGage(50);
		}
		else if (m_pObject->GetName() == "Item5")
		{
			SYSTEM->AddScore(3000);
		}
		else if (m_pObject->GetName() == "Item4")
		{
			SYSTEM->AddLife(1);
			SOUND->Play("Extend");
		}
		SOUND->Play("Item");
		m_pObject->Destroy();
	});
	m_Speed = -300 * SYSTEM->GetTimeSpeed();
	m_TimeSpeed = 10 * SYSTEM->GetTimeSpeed() * SYSTEM->GetTimeSpeed();
	m_Collect = false;
}

void cItem::Update()
{
	float TimeSpeed = SYSTEM->GetTimeSpeed();
	if (!m_Collect)
	{
		if (m_pObject->GetPosition().y > 490)
		{
			m_pObject->Destroy();
		}
		m_pObject->Translate(Vector2(0, m_Speed * DeltaTime));
		if (m_Speed <= 225 * TimeSpeed)
			m_Speed += m_TimeSpeed;
	}
	else
	{
		cObject* Player = OBJECT->GetPlayer();
		if (!Player->GetComponent<cPlayer>()->GetDead())
		{
			Vector2 Pos = m_pObject->GetPosition();
			Vector2 PlayerPos = Player->GetPosition();
			float m_Dir = atan2(PlayerPos.y - Pos.y, PlayerPos.x - Pos.x);
			m_pObject->Translate(Vector2(500 * cos(m_Dir), 500 * sin(m_Dir)) * DeltaTime * TimeSpeed);
		}
		else
		{
			m_Collect = false;
		}
	}
}

void cItem::Render()
{
	if (m_pObject->GetPosition().y <= 0)
	{
		string Name = m_pObject->GetName() + "Marker";
		IMAGE->Render(IMAGE->FindImage(Name), Vector2(m_pObject->GetPosition().x, 10), Vector2(1, 1), 0);
	}
}

void cItem::Release()
{

}