#pragma once

class cRemi;
class cTimeLine_Remi1 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Dir;
	texture* m_Bullet[3];
	cRemi* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Remi1(cObject* Object);
	~cTimeLine_Remi1();

};

