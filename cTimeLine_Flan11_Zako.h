#pragma once

class cZako;
class cTimeLine_Flan11_Zako : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	texture* m_Bullet;
	texture* m_Effect;
	cZako* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan11_Zako(cObject* Object);
	~cTimeLine_Flan11_Zako();

};

