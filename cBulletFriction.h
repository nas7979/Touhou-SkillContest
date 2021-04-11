#pragma once

class cBulletFriction : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	float m_Dir;
	float m_EndSpeed;
	float m_Friction;
	bool m_Grazed;

public:
	cBulletFriction(cObject* Object);
	~cBulletFriction();

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

	void SetEndSpeed(float EndSpeed)
	{
		m_EndSpeed = EndSpeed * SYSTEM->GetTimeSpeed();
	}
	float GetEndSpeed()
	{
		return m_EndSpeed;
	}

	void SetFriction(float Friction)
	{
		m_Friction = 1 - (1 - Friction) * SYSTEM->GetTimeSpeed();
	}
	float GetFriction()
	{
		return m_Friction;
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

