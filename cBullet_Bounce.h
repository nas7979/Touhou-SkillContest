#pragma once
#include "cBullet.h"
class cBullet_Bounce : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	int m_MaxColl;
	int m_Colled;
	bool m_CollAt[4];
	cBullet* m_Owner;

public:
	cBullet_Bounce(cObject* Object);
	~cBullet_Bounce();

	void SetMaxColl(int Max)
	{
		m_MaxColl = Max;
	}
	void SetCollAt(bool Up = false, bool Left = false, bool Down = false, bool Right = false)
	{
		m_CollAt[0] = Up;
		m_CollAt[1] = Left;
		m_CollAt[2] = Down;
		m_CollAt[3] = Right;
	}
};

