#pragma once
class cFlan;
class cTimeLine_Flan4 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Timing;
	float m_LaserDir;
	float m_LaserSpeed;
	int m_BulletDir;
	bool m_LaserOn;
	texture* m_Bullet;
	texture* m_Effect[2];
	cFlan* m_Owner = nullptr;
	list<cObject*> m_Laser;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan4(cObject* Object);
	~cTimeLine_Flan4();

};

