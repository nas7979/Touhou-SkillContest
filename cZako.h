#pragma once

class cZako : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	float m_Friction;
	int m_Hp;
	vector<string> m_Drop;

	void IsOutMap();

public:
	cZako(cObject* Object);
	~cZako();
	cObject* AddBullet(Vector2 Pos, int Speed, float Direction, int Size, string Image);
	cObject* AddBullet(Vector2 Pos, int StartSpeed, int EndSpeed, float Friction, float Direction, int Size, string Image);
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

	void AddDrop(string Drop)
	{
		m_Drop.push_back(Drop);
	}
};

