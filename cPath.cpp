#include "DXUT.h"
#include "cPath.h"

cPath::cPath(cObject* Object)
	:cComponent(Object)
{
}

cPath::~cPath()
{
}

void cPath::Init()
{
//	m_Path.push_back(Path{ Vector2(0,0), Vector2(m_pObject->GetPosition()) });
	m_Points.push_back(m_pObject->GetPosition());
	m_NextPoint = 0;
	m_NextPath = 0;
	m_Speed = 0;
	m_Direction = 0;
}

void cPath::Update()
{
	if (Math::PointDistance(m_pObject->GetPosition(), m_Points[m_NextPoint]) <= 1 * (m_Speed / 50) * 60 * DeltaTime || m_NextPoint == 0)
	{
		m_pObject->SetPosition(m_Points[m_NextPoint]);
		if (m_NextPoint < m_Points.size() - 1) m_NextPoint++;
		m_Direction = atan2(m_Points[m_NextPoint].y - m_pObject->GetPosition().y, m_Points[m_NextPoint].x - m_pObject->GetPosition().x);
	}
	else
	{
		m_pObject->Translate(Vector2(m_Speed * cos(m_Direction) * DeltaTime, m_Speed * sin(m_Direction) * DeltaTime));
	}
}

void cPath::Render()
{

}

void cPath::Release()
{

}

void cPath::AddPath(Vector2 ControlPos, Vector2 GoalPos)
{
	m_Path.push_back(Path{ ControlPos,GoalPos });
	if (m_pObject->GetPosition() == ControlPos)
	{
		Vector2 Pos;
		D3DXVec2Lerp(&Pos, &ControlPos, &GoalPos, 0.9);
		m_Points.push_back(ControlPos);
		m_Points.push_back(Pos);
		m_Points.push_back(GoalPos);
		return;
	}
	Vector2 P1, P2, P3;

	for (int i = 1; i <= 20; i++)
	{
		D3DXVec2Lerp(&P1, &m_pObject->GetPosition(), &m_Path[m_NextPath].ControlPos, 0.05 * i);
		D3DXVec2Lerp(&P2, &m_Path[m_NextPath].ControlPos, &m_Path[m_NextPath].GoalPos, 0.05 * i);
		D3DXVec2Lerp(&P3, &P1, &P2, 0.05 * i);
		m_Points.push_back(P3);
	}
	m_NextPath++;
}