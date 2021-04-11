#pragma once

class cFlan;
class cTimeLine_Flan10 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	texture* m_Bullet[3];
	cFlan* m_Owner = nullptr;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan10(cObject* Object);
	~cTimeLine_Flan10();

};

