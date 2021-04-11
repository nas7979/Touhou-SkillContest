#pragma once

class cItem : public cComponent
{
	friend class cObject;
	friend class cSystemManager;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Speed;
	float m_TimeSpeed;
	bool m_Collect;

public:
	cItem(cObject* Object);
	~cItem();

	void SetCollect(bool Collect)
	{
		m_Collect = Collect;
	}
	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}

};

