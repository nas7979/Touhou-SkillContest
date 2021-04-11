#pragma once
class cZako;
class cTimeLine_Zako8 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Dir;
	int m_Rotate;
	int m_Looped;
	texture* m_Bullet;
	texture* m_Effect;
	Vector2 PlayerPos;
	cZako* m_Owner;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Zako8(cObject* Object);
	~cTimeLine_Zako8();

	void SetBullet(string Image)
	{
		m_Bullet = IMAGE->FindImage(Image);
	}
	void SetEffect(string Image)
	{
		m_Effect = IMAGE->FindImage(Image);
	}
};

