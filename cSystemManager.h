#pragma once
#include "singleton.h"

struct RankData
{
	int Score;
	string Character;
};
//singleton을 상속받았다. 어디서든 접근이 가능해짐
class cSystemManager : public singleton <cSystemManager>
{
private:

	int m_Life;
	int m_StartLife;
	int m_Missed;
	int m_BoomCount;
	int m_BonusCount;
	float m_Gage;
	unsigned long int m_Score;
	int m_Power;
	int m_Graze;
	int m_PowerLevel;
	bool m_FullPower;
	bool m_Bonus;
	float m_TimeSpeed;
	map<string, RankData> m_Ranking;
	cTimer* m_Timer_Flan = nullptr;
	cTimer* m_Timer_Result = nullptr;
	bool m_IsReplay;

	texture* m_Texture_Front;
	texture* m_Texture_Num[10];
	texture* m_Texture_Gage;
	texture* m_Texture_Max;
	texture* m_Texture_Life;
	texture* m_Texture_BossHpBar;
	texture* m_Texture_Enemy_Life;

public:
	cSystemManager();
	virtual ~cSystemManager();

	void Init();
	void Update();
	void Render();
	void Release();

	void SetTimeSpeed(float Speed);
	void CreateFlan();
	void GotoWin();
	void GotoLose();

	void Initialize();

	float GetTimeSpeed()
	{
		return m_TimeSpeed;
	}

	void SetLife(int Life)
	{
		m_Life = Life;
	}
	int GetLife()
	{
		return m_Life;
	}
	void AddLife(int Life)
	{
		m_Life += Life;
	}

	int GetStartLife()
	{
		return m_StartLife;
	}
	void SetStartLife(int Life)
	{
		m_StartLife = Life;
	}

	int GetMissed()
	{
		return m_Missed;
	}
	void SetMissed(int Missed)
	{
		m_Missed = Missed;
	}
	void AddMissed(int Missed)
	{
		m_Missed += Missed;
	}

	int GetBoomCount()
	{
		return m_BoomCount;
	}
	void SetBoomCount(int Count)
	{
		m_BoomCount = Count;
	}
	void AddBoomCount(int Count)
	{
		m_BoomCount += Count;
	}

	int GetBonusCount()
	{
		return m_BonusCount;
	}
	void SetBonusCount(int Count)
	{
		m_BonusCount = Count;
	}
	void AddBonusCount(int Count)
	{
		m_BonusCount += Count;
	}


	void SetGage(float Gage)
	{
		m_Gage = Gage;
	}
	float GetGage()
	{
		return m_Gage;
	}
	void AddGage(float Gage)
	{
		m_Gage += Gage;
	}

	void SetScore(int Score)
	{
		m_Score = Score;
	}
	unsigned long int GetScore()
	{
		return m_Score;
	}
	void AddScore(int Score)
	{
		m_Score += Score;
	}

	void SetPower(int Power)
	{
		m_Power = Power;
	}
	int GetPower()
	{
		return m_Power;
	}
	void AddPower(int Power)
	{
		m_Power += Power;
	}

	void SetGraze(int Graze)
	{
		m_Graze = Graze;
	}
	int GetGraze()
	{
		return m_Graze;
	}
	void AddGraze()
	{
		m_Graze++;
	}

	void SetBonus(bool Bonus)
	{
		m_Bonus = Bonus;
	}
	bool GetBonus()
	{
		return m_Bonus;
	}

	void SetIsReplay(bool IsReplay)
	{
		m_IsReplay = IsReplay;
	}
	bool GetIsReplay()
	{
		return m_IsReplay;
	}
};

#define SYSTEM cSystemManager::GetInstance()