#pragma once
#include "cBullet.h"
class cBullet_Gravity : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Gravity;
	cBullet* m_Owner;

public:
	cBullet_Gravity(cObject* Object);
	~cBullet_Gravity();

	void SetGravity(float Gravity)
	{
		m_Gravity = Gravity;
	}
	float GetGravity()
	{
		return m_Gravity;
	}
};

