#pragma once

class cBulletToPos : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	float m_Dir;
	int m_Damage;
	bool m_IsEnemy;
	cObject* m_TargetObj;
	string m_FirstTarget;
	Vector2 m_TargetPos;
	bool m_Grazed;

public:
	cBulletToPos(cObject* Object);
	~cBulletToPos();

	void IsOutMap();

	void SetSpeed(float Speed)
	{
		m_Speed = Speed * SYSTEM->GetTimeSpeed();
	}
	float GetSpeed()
	{
		return m_Speed;
	}

	void SetDirection(float Direction)
	{
		m_Dir = Direction;
	}
	float GetDirection()
	{
		return m_Dir;
	}

	void SetIsEnemy(bool IsEnemy)
	{
		m_IsEnemy = IsEnemy;
	}
	bool GetIsEnemy()
	{
		return m_IsEnemy;
	}

	void SetDamage(int Damage)
	{
		m_Damage = Damage;
	}
	int GetDamage()
	{
		return m_Damage;
	}

	void SetTarget(cObject* Target)
	{
		m_TargetObj = Target;
		if(Target != nullptr)
		m_FirstTarget = Target->GetName();
	}
	cObject* GetTargetObject()
	{
		return m_TargetObj;
	}

	void SetTarget(Vector2 Target)
	{
		m_TargetPos = Target;
	}
	Vector2 GetTargetPos()
	{
		return m_TargetPos;
	}

	void SetGrazed(bool Grazed)
	{
		m_Grazed = Grazed;
	}
	bool GetGrazed()
	{
		return m_Grazed;
	}
};

