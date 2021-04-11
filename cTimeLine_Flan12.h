#pragma once

class cFlan;
class cTimeLine_Flan12 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	int m_Timing;
	int m_Speed;
	texture* m_Bullet;
	cFlan* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan12(cObject* Object);
	~cTimeLine_Flan12();

};

