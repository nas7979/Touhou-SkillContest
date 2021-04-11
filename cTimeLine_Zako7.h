#pragma once
class cZako;
class cTimeLine_Zako7 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	int m_Dir;
	int m_Looped;
	texture* m_Bullet[3];
	texture* m_Effect[2];
	Vector2 PlayerPos;
	cZako* m_Owner;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Zako7(cObject* Object);
	~cTimeLine_Zako7();
};

