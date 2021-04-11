#pragma once

struct Path
{
	Vector2 ControlPos;
	Vector2 GoalPos;
};

class cPath : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:
	vector<Path> m_Path;
	vector<Vector2> m_Points;
	int m_NextPoint;
	int m_NextPath;
	float m_Speed;
	float m_Direction;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cPath(cObject* Object);
	~cPath();

	vector<Path>* GetPath()
	{
		return (&m_Path);
	}

	float GetSpeed()
	{
		return m_Speed;
	}
	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}

	float GetDirection()
	{
		return m_Direction;
	}
	void SetDirection(float Direction)
	{
		m_Direction = Direction;
	}

	void Clear()
	{
		m_Path.clear();
		m_NextPath = 0;
		m_Points.clear();
		m_NextPoint = 0;
	}

	int GetNextPoint()
	{
		return m_NextPoint;
	}

	int GetPointsSize()
	{
		return m_Points.size();
	}

	void AddPath(Vector2 ContolPos, Vector2 GoalPos);
};

