#pragma once
class cZako;
class cTimeLine_Zako4 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	Vector2 PlayerPos;
	texture* m_Bullet;
	texture* m_Effect;
	cZako* m_Owner;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Zako4(cObject* Object);
	~cTimeLine_Zako4();

	void SetBullet(string Image)
	{
		m_Bullet = IMAGE->FindImage(Image);
	}
	void SetEffect(string Image)
	{
		m_Effect = IMAGE->FindImage(Image);
	}
};

