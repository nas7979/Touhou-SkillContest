#pragma once

class cFlan : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	float m_Friction;
	int m_Armor;
	int m_Hp;
	int m_MaxHp;
	int m_Phase;
	float m_TimeLeft;
	int m_LastTime;
	int m_SpellBonus;
	texture* m_Texture_Circle;

	void IsOutMap();
	void Spell();
	void EndSpell();

public:
	cFlan(cObject* Object);
	~cFlan();
	cObject* AddBullet(Vector2 Pos, int Speed, float Direction, int Size, texture* Image);
	cObject* AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, texture* Image);

	float GetSpeed()
	{
		return m_Speed;
	}
	void SetSpeed(float Speed)
	{
		m_Speed = Speed * SYSTEM->GetTimeSpeed();
	}

	float GetFriction()
	{
		return m_Friction;
	}
	void SetFriction(float Friction)
	{
		m_Friction = 1 - (1 - Friction) * SYSTEM->GetTimeSpeed();
	}

	int GetHp()
	{
		return m_Hp;
	}
	void SetHp(int Hp)
	{
		m_Hp = Hp;
	}

	int GetMaxHp()
	{
		return m_MaxHp;
	}
	void SetMaxHp(int MaxHp)
	{
		m_MaxHp = MaxHp;
		m_Hp = MaxHp;
	}

	int GetPhase()
	{
		return m_Phase;
	}

	float GetTimeLeft()
	{
		return m_TimeLeft;
	}

	int GetSpellBonus()
	{
		return m_SpellBonus;
	}
};

