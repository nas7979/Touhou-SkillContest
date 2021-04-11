#pragma once
#include "cBullet.h"
class cBullet_Flan8 : public cComponent
{
	friend class cObject;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	cObject* m_Owner;

	void IsOutMap();

public:
	cBullet_Flan8(cObject* Object);
	~cBullet_Flan8();

	void SetOwner(cObject* Owner)
	{
		m_Owner = Owner;
	}

};

