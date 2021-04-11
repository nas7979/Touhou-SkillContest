#pragma once

class cFlan;
class cZako;
class cTimeLine_Flan6 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	int m_Pattern;
	float m_Timing;
	bool m_OnAttack;
	texture* m_Bullet[4];
	cFlan* m_Owner = nullptr;
	cZako* m_Owner_Zako = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan6(cObject* Object);
	~cTimeLine_Flan6();

	void SetPattern(int Pattern)
	{
		m_Pattern = Pattern;
	}
	void SetOnAttack(bool OnAttack)
	{
		m_OnAttack = OnAttack;
	}
};

