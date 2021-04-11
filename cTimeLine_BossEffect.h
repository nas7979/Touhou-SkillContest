#pragma once

class cTimeLine_BossEffect : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Dir;
	float m_Pos;


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_BossEffect(cObject* Object);
	~cTimeLine_BossEffect();
};

