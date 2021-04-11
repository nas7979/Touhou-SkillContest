#pragma once

class cTimeLine_BossDeath : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_BossDeath(cObject* Object);
	~cTimeLine_BossDeath();
};

