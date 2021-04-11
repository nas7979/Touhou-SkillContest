#pragma once

class cRemi;
class cTimeLine_Remi2 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Dir;
	int m_Pattern;
	float m_Speed;
	texture* m_Bullet;
	cRemi* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Remi2(cObject* Object);
	~cTimeLine_Remi2();

};

