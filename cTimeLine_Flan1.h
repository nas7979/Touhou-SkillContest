#pragma once

class cFlan;
class cTimeLine_Flan1 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	bool m_Music;
	texture* m_Bullet;
	texture* m_Effect;
	cFlan* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan1(cObject* Object);
	~cTimeLine_Flan1();

};

