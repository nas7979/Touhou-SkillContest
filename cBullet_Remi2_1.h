#pragma once
#include "cBullet.h"
class cBullet_Remi2_1 : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Dir;
	float m_FirstDir;
	float m_Delay;
	int m_Pattern;
	int m_Last;
	cBullet* m_Owner;
	texture* m_Bullet;

public:
	cBullet_Remi2_1(cObject* Object);
	~cBullet_Remi2_1();

	void SetPattern(int Pattern)
	{
		m_Pattern = Pattern;
	}
};

