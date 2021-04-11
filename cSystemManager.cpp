#include "DXUT.h"
#include "cSystemManager.h"
#include "cZako.h"
#include "cBullet.h"
#include "cBulletFriction.h"
#include "cBulletToPos.h"
#include "cItem.h"
#include "cRemi.h"
#include "cFlan.h"

cSystemManager::cSystemManager()
{
	Init();
}


cSystemManager::~cSystemManager()
{
	Release();
}

void cSystemManager::Init()
{
	m_StartLife = 6;
	m_IsReplay = false;
	Initialize();

	m_Texture_Front = IMAGE->FindImage("Front");
	m_Texture_Life = IMAGE->FindImage("Life");
	m_Texture_Gage = IMAGE->FindImage("Gage");
	m_Texture_Max = IMAGE->FindImage("Max");
	m_Texture_BossHpBar = IMAGE->FindImage("BossHpBar");
	m_Texture_Enemy_Life = IMAGE->FindImage("Enemy_Life");
	m_Texture_Num[0] = IMAGE->FindImage("0");
	m_Texture_Num[1] = IMAGE->FindImage("1");
	m_Texture_Num[2] = IMAGE->FindImage("2");
	m_Texture_Num[3] = IMAGE->FindImage("3");
	m_Texture_Num[4] = IMAGE->FindImage("4");
	m_Texture_Num[5] = IMAGE->FindImage("5");
	m_Texture_Num[6] = IMAGE->FindImage("6");
	m_Texture_Num[7] = IMAGE->FindImage("7");
	m_Texture_Num[8] = IMAGE->FindImage("8");
	m_Texture_Num[9] = IMAGE->FindImage("9");
}

void cSystemManager::Update()
{
	if (m_PowerLevel < (int)(m_Power / 32))
	{
		SOUND->Play("PowerUp");
		cEffect* a = EFFECT->Create("", OBJECT->GetPlayer()->GetPosition(), Vector2(12, 1), 5);
		EFFECT->TextSetting(a, L"PowerUp");
		EFFECT->AlphaSetting(a, 1000, -20);
		EFFECT->MovementSetting(a, 300, 270, 0.86, 0);
		EFFECT->ColorSetting(a, 255, 25, 0);
	}
	m_PowerLevel = (int)(m_Power / 32);

	if (m_Power >= 128 && m_FullPower == false)
	{
		m_Power = 128;
		m_FullPower = true;
		OBJECT->With(Tag::Item, [&](cObject* Obj)->void {
			if (Obj->GetName() == "Item1" || Obj->GetName() == "Item3")
			{
				Obj->SetName("Item2");
				Obj->GetComponent<cRenderer>()->SetImage(IMAGE->FindImage("Item2"));
			}
		});
		OBJECT->With("EnemyBullet", [&](cObject* Obj)->void {
			Obj->Destroy();
		});
	}
	else if(m_Power != 128)
	{
		m_FullPower = false;
	}

	if (m_TimeSpeed != 1)
	{
		m_Gage -= 0.15;
		if (m_Gage <= 0)
		{
			m_Gage = 0;
			SetTimeSpeed(5);
		}
	}

	if (m_Timer_Flan) m_Timer_Flan->Update();
	if (m_Timer_Result) m_Timer_Result->Update();
}

void cSystemManager::Render()
{
	if (SCENE->GetCurrentSceneKey("Ingame"))
	{
		if (m_Gage > 200) m_Gage = 200;
		if (m_Power < 0) m_Power = 0;
		IMAGE->Render(m_Texture_Front, 384, 0);

		char _Num[10];
		sprintf(_Num, "%lld", m_Score);
		string _Text = string(_Num);
		int Pos = 0;
		for (int i = 0; i < 9 - _Text.size(); i++)
		{
			IMAGE->Render(m_Texture_Num[0], 464 + Pos, 64);
			Pos += 16;
		}
		for (int i = 0; i < _Text.size(); i++)
		{
			char Text[2] = { _Text[i], NULL };
			IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 464 + Pos, 64);
			Pos += 16;
		}

		IMAGE->Render(m_Texture_Gage, Vector2(464 + ((float)m_Power / 128) * 72, 152), Vector2((float)m_Power / 128, 1), 0);
		if (m_FullPower == true)
		{
			IMAGE->Render(m_Texture_Max, 464, 144);
		}
		else
		{
			sprintf(_Num, "%d", m_Power);
			_Text = string(_Num);
			for (int i = 0; i < _Text.size(); i++)
			{
				char Text[2] = { _Text[i], NULL };
				IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 464 + i * 16, 144);
			}
		}

		IMAGE->Render(m_Texture_Gage, Vector2(464 + ((float)m_Gage / 200) * 72, 120), Vector2((float)m_Gage / 200, 1), 0);
		sprintf(_Num, "%d", (int)m_Gage);
		_Text = string(_Num);
		for (int i = 0; i < _Text.size(); i++)
		{
			char Text[2] = { _Text[i], NULL };
			IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 464 + i * 16, 112);
		}

		for (int i = 0; i < m_Life - 1; i++)
		{
			IMAGE->Render(m_Texture_Life, 464 + i * 16, 96);
		}

		sprintf(_Num, "%d", m_Graze);
		_Text = string(_Num);
		for (int i = 0; i < _Text.size(); i++)
		{
			char Text[2] = { _Text[i], NULL };
			IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 464 + i * 16, 160);
		}

		cObject* Boss = OBJECT->GetBoss();
		if (Boss != nullptr)
		{
			IMAGE->Render(m_Texture_Enemy_Life, 2, 2);
			if (Boss->GetName() == "Remi")
			{
				cRemi* Remi = Boss->GetComponent<cRemi>();
				IMAGE->Render(m_Texture_BossHpBar, Vector2(86 + ((float)Remi->GetHp() / Remi->GetMaxHp()), 13), Vector2((float)Remi->GetHp() / Remi->GetMaxHp() * 262, 1), 0);

				sprintf(_Num, "%d", (int)((Remi->GetPhase() - 1) / 2));
				_Text = string(_Num);
				char Text[2] = { _Text[0], NULL };
				IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 68, 2);

				sprintf(_Num, "%d", min(99, (int)Remi->GetTimeLeft()));
				_Text = string(_Num);
				Pos = 0;
				for (int i = 0; i < 2 - _Text.size(); i++)
				{
					IMAGE->Render(m_Texture_Num[0], 350 + Pos, 2);
					Pos += 16;
				}
				for (int i = 0; i < _Text.size(); i++)
				{
					char Text[2] = { _Text[i], NULL };
					IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 350 + Pos, 2);
					Pos += 16;
				}
			}
			else
			{
				cFlan* Flan = Boss->GetComponent<cFlan>();
				IMAGE->Render(m_Texture_BossHpBar, Vector2(86 + ((float)Flan->GetHp() / Flan->GetMaxHp()), 13), Vector2((float)Flan->GetHp() / Flan->GetMaxHp() * 262, 1), 0);

				sprintf(_Num, "%d", (int)((Flan->GetPhase() - 1) / 2));
				_Text = string(_Num);
				char Text[2] = { _Text[0], NULL };
				IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 68, 2);

				sprintf(_Num, "%d", min(99, (int)Flan->GetTimeLeft()));
				_Text = string(_Num);
				Pos = 0;
				for (int i = 0; i < 2 - _Text.size(); i++)
				{
					IMAGE->Render(m_Texture_Num[0], 350 + Pos, 2);
					Pos += 16;
				}
				for (int i = 0; i < _Text.size(); i++)
				{
					char Text[2] = { _Text[i], NULL };
					IMAGE->Render(m_Texture_Num[(int)Text[0] - 48], 350 + Pos, 2);
					Pos += 16;
				}
			}
		}
	}
}

void cSystemManager::Release()
{
	if (m_Timer_Flan)
	{
		m_Timer_Flan = nullptr;
		SAFE_DELETE(m_Timer_Flan);
	}
	if (m_Timer_Result)
	{
		m_Timer_Result = nullptr;
		SAFE_DELETE(m_Timer_Result);
	}
}

void cSystemManager::SetTimeSpeed(float Speed)
{
	m_TimeSpeed = Speed;
	m_Bonus = false;
	OBJECT->With(Tag::Enemy, [&](cObject * Obj)->void {
		if (Obj->GetName() == "Zako")
		{
			Obj->GetComponent<cZako>()->SetSpeed(Obj->GetComponent<cZako>()->GetSpeed());
			Obj->GetComponent<cZako>()->SetFriction(Obj->GetComponent<cZako>()->GetFriction());
		}
		else if (Obj->GetName() == "Flan")
		{
			Obj->GetComponent<cFlan>()->SetSpeed(Obj->GetComponent<cFlan>()->GetSpeed());
			Obj->GetComponent<cFlan>()->SetFriction(Obj->GetComponent<cFlan>()->GetFriction());
		}
		else
		{
			Obj->GetComponent<cRemi>()->SetSpeed(Obj->GetComponent<cRemi>()->GetSpeed());
			Obj->GetComponent<cRemi>()->SetFriction(Obj->GetComponent<cRemi>()->GetFriction());
		}
		Obj->GetComponent<cAnimation>()->SetPlaySpeed(Obj->GetComponent<cAnimation>()->GetPlaySpeed());
	});
	OBJECT->With("EnemyBullet", [&](cObject * Obj)->void {
		if(Obj->GetComponent<cBullet>() != nullptr)
		Obj->GetComponent<cBullet>()->SetSpeed(Obj->GetComponent<cBullet>()->GetSpeed());
		else if(Obj->GetComponent<cBulletFriction>() != nullptr)
		{
			Obj->GetComponent<cBulletFriction>()->SetSpeed(Obj->GetComponent<cBulletFriction>()->GetSpeed());
			Obj->GetComponent<cBulletFriction>()->SetEndSpeed(Obj->GetComponent<cBulletFriction>()->GetEndSpeed());
			Obj->GetComponent<cBulletFriction>()->SetFriction(Obj->GetComponent<cBulletFriction>()->GetFriction());
		}
		else
		{
			Obj->GetComponent<cBulletToPos>()->SetSpeed(Obj->GetComponent<cBulletToPos>()->GetSpeed());
		}
	});
	OBJECT->With(Tag::Item, [&](cObject* Obj)->void {
		Obj->GetComponent<cItem>()->m_Speed *= Speed;
		Obj->GetComponent<cItem>()->m_TimeSpeed *= Speed * Speed;
	});
	EFFECT->SetTimeSpeed();
	SOUND->SetTimeSpeed();
	if (m_TimeSpeed >= 1) m_TimeSpeed = 1;
}

void cSystemManager::CreateFlan()
{
	m_Timer_Flan = new cTimer(200, [&]()->void {
		cObject* a = OBJECT->Create("Flan", Vector2(192, -32), -6, Tag::Enemy);
		a->AddComponent<cFlan>();
		m_Timer_Flan = nullptr;
		SAFE_DELETE(m_Timer_Flan);
	});
}

void cSystemManager::GotoWin()
{
	m_Timer_Result = new cTimer(180, [&]()->void {
		SCENE->ChangeScene("Win");
		switch (m_StartLife)
		{
		case 3: m_Score *= 2; break;
		case 4: m_Score *= 1.66; break;
		case 5: m_Score *= 1.33; break;
		case 7: m_Score *= 0.9; break;
		case 8: m_Score *= 0.8; break;
		case 9: m_Score *= 0.7; break;
		case 10: m_Score *= 0.6; break;
		case 100: m_Score = 0; break;
		}
		m_Timer_Result = nullptr;
		SAFE_DELETE(m_Timer_Result);
	});
}

void cSystemManager::GotoLose()
{
	m_Timer_Result = new cTimer(180, [&]()->void {
		SCENE->ChangeScene("Lose");
		switch (m_StartLife)
		{
		case 3: m_Score *= 2; break;
		case 4: m_Score *= 1.66; break;
		case 5: m_Score *= 1.33; break;
		case 7: m_Score *= 0.9; break;
		case 8: m_Score *= 0.8; break;
		case 9: m_Score *= 0.7; break;
		case 10: m_Score *= 0.6; break;
		case 100: m_Score  = 0; break;
		}
		m_Timer_Result = nullptr;
		SAFE_DELETE(m_Timer_Result);
	});
}

void cSystemManager::Initialize()
{
	m_Life = m_StartLife;
	m_Missed = 0;
	m_BonusCount = 0;
	m_BoomCount = 0;
	m_Gage = 75;
	m_Score = 0;
	m_Power = 0;
	m_TimeSpeed = 1;
	m_Graze = 0;
	m_Bonus = true;
	m_FullPower = false;
	m_PowerLevel = m_Power / 4;
}