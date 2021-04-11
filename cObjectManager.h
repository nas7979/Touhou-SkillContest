#pragma once
#include "singleton.h"
#include "cObject.h"
#include "cComponent.h"

class cObjectManager : public singleton <cObjectManager>
{
	friend class cComponent;
private:
	list<cObject*> m_Objects;
	list<cObject*> m_CollObjects;
	list<cObject*> m_Cells[8][10];
	cObject* m_Player;
	cObject* m_Boss;

	void CheckBoxCollision(cObject* Object);
	void CheckCircleCollision(cObject* Object);
	void CheckCircleCollisionTest(cObject* Object);

public:
	cObjectManager();
	virtual ~cObjectManager();
	void Init();
	void Update();
	void Render();
	void Release();
	void ClearAll();

	cObject* Create(string Name, Vector2 Pos, int Depth, Tag ObjectTag);
	list<cObject*> Find(string Name);
	list<cObject*> Find(Tag ObjectTag);
	void With(string Name, function<void(cObject* Obj)> Func);
	void With(Tag ObjectTag, function<void(cObject* Obj)> Func);
	void With(cObject* Obj, function<void(cObject* Obj)> Func);
	cObject* GetPlayer()
	{
		return m_Player;
	}
	void SetPlayer(cObject* Player)
	{
		m_Player = Player;
	}

	cObject* GetBoss()
	{
		return m_Boss;
	}
	void SetBoss(cObject* Boss)
	{
		m_Boss = Boss;
	}
};

#define OBJECT cObjectManager::GetInstance()