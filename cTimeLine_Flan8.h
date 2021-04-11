#pragma once

struct WallSpawner
{
	Vector2 Pos;
	float Timing;
	float Direction;
};
class cFlan;
class cTimeLine_Flan8 : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:

	float m_Time;
	int m_Last;
	texture* m_Bullet[2];
	texture* m_Effect;
	cFlan* m_Owner = nullptr;
	list<WallSpawner> m_Spawners;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cTimeLine_Flan8(cObject* Object);
	~cTimeLine_Flan8();

};

