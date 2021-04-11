#pragma once
struct Spawner
{
	Vector2 Pos;
	float Direction;
	float Speed;
	float Friction;
	int Pattern;
};
class cFlan;
class cTimeLine_Flan2 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	float m_Timing;
	texture* m_Bullet[2];
	texture* m_Effect[2];
	texture* m_Spawner;
	cFlan* m_Owner = nullptr;
	vector<Spawner> m_Spawners;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan2(cObject* Object);
	~cTimeLine_Flan2();

};

