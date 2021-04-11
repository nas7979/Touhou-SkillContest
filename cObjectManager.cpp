#include "DXUT.h"
#include "cObjectManager.h"

cObjectManager::cObjectManager()
{
	Init();
}


cObjectManager::~cObjectManager()
{
	Release();
}

void cObjectManager::Init()
{
	m_Boss = nullptr;
}

void cObjectManager::Update()
{
	m_CollObjects.clear();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_Cells[j][i].clear();
		}
	}
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		if (!(*iter)->GetEnable())
		{
			iter++;
			continue;
		}
		for (auto iter : (*iter)->m_Components)
		{
			if(iter->GetEnable())
				iter->Update();
		}
		//if ((*iter)->GetComponent<cCircleCollider>()) CheckCircleCollision((*iter));

		if ((*iter)->m_Destroyed == true)
		{
			(*iter)->Release();
			SAFE_DELETE((*iter));
			iter = m_Objects.erase(iter);
		}
		else
		{
			if ((*iter)->m_Pos.x >= 0 && (*iter)->m_Pos.x <= 384 && (*iter)->m_Pos.y >= 0 && (*iter)->m_Pos.y <= 480)
			{
				m_Cells[(int)(((*iter)->m_Pos.x - 1)/ 48)][(int)(((*iter)->m_Pos.y - 1) / 48)].push_back((*iter));
				cCircleCollider* Coll = (*iter)->GetComponent<cCircleCollider>();
				if (Coll)
				{
					if ((Coll->m_ColllistTag.size() != 0 || Coll->m_ColllistName.size() != 0) && Coll->m_Enable)
					{
						m_CollObjects.push_back((*iter));
					}
				}
			}
			iter++;
		}
	}

	for (auto& iter = m_CollObjects.begin(); iter != m_CollObjects.end();)
	{
		CheckCircleCollisionTest((*iter));
		iter++;
	}
}

void cObjectManager::Render()
{
	list<cObject*> RenderList = m_Objects;
	RenderList.sort([&](cObject *  pPrev, cObject *  pNext)->bool { return pPrev->m_Depth > pNext->m_Depth; });
	for (auto& iter = RenderList.begin(); iter != RenderList.end();)
	{
		(*iter)->Render();
		for (auto iter : (*iter)->m_Components)
		{
			if (iter->GetEnable())
				iter->Render();
		}
		iter++;
	}
	RenderList.clear();
}

void cObjectManager::Release()
{
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		(*iter)->Release();
		SAFE_DELETE((*iter));
		iter++;
	}
	m_Objects.clear();
}

void cObjectManager::CheckCircleCollisionTest(cObject* Object)
{
	cCircleCollider* ThisColl = Object->GetComponent<cCircleCollider>();
	cCircleCollider* OtherColl;
	int Radius = ThisColl->m_Radius;
	Vector2 Pos = Object->m_Pos;
	int TagSize = ThisColl->m_ColllistTag.size();
	int NameSize = ThisColl->m_ColllistName.size();
	int k = 0;
	float x, y, Dir, Dist = 0;

	int Cellx = max((int)(Object->m_Pos.x / 48) - 1, 0);
	int Celly = max((int)(Object->m_Pos.y / 48) - 1, 0);

	for (int i = Celly; i < min(Celly + 3, 10); i++)
	{
		for (int j = Cellx; j < min(Cellx + 3, 8); j++)
		{
			for (auto& iter = m_Cells[j][i].begin(); iter != m_Cells[j][i].end();)
			{
				x = Pos.x - (*iter)->m_Pos.x;
				y = Pos.y - (*iter)->m_Pos.y;
				Dir = atan(y / x);
				Dist = abs(x * cos(Dir)) + abs(y * sin(Dir));
				if (Dist <= 40)
				{
					OtherColl = (*iter)->GetComponent<cCircleCollider>();
					for (k = 0; k < NameSize; k++)
					{
						if ((*iter)->m_Name == ThisColl->m_ColllistName[k])
						{
							if (Dist <= Radius + OtherColl->m_Radius)
							{
								ThisColl->m_CollFunc((*iter));
								OtherColl->m_CollFunc(Object);
							}
							goto Next;
						}
					}
					for (k = 0; k < TagSize; k++)
					{
						if ((*iter)->m_Tag == ThisColl->m_ColllistTag[k])
						{
							if (Dist <= Radius + OtherColl->m_Radius)
							{
								ThisColl->m_CollFunc((*iter));
								OtherColl->m_CollFunc(Object);
							}
							break;
						}
					}
				}
			Next:
				iter++;
			}
		}
	}
}

void cObjectManager::CheckBoxCollision(cObject* Object)
{
	cBoxCollider* ThisColl = Object->GetComponent<cBoxCollider>();
	if (ThisColl->m_ColllistTag.size() == 0 && ThisColl->m_ColllistName.size() == 0 || ThisColl->GetEnable() == false) return;
	list<cObject*> Others;
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		if ((*iter) == Object) goto Next;
		for (int i = 0; i < ThisColl->m_ColllistTag.size(); i++)
		{
			if ((*iter)->GetTag() == ThisColl->m_ColllistTag.at(i))
			{
				Others.push_back((*iter));
				goto Next;
			}
		}
		for (int i = 0; i < ThisColl->m_ColllistName.size(); i++)
		{
			if ((*iter)->GetName() == ThisColl->m_ColllistName.at(i))
			{
				Others.push_back((*iter));
				break;
			}
		}
		Next:
		iter++;
	}
	
	for (auto& iter = Others.begin(); iter != Others.end();)
	{
		if ((*iter)->GetComponent<cBoxCollider>())
		{
			if (Math::CheckCollBoxBox(Object->GetPosition(), ThisColl->GetSize(), (*iter)->GetPosition(), (*iter)->GetComponent<cBoxCollider>()->GetSize()))
			{
				ThisColl->m_CollFunc((*iter));
				(*iter)->GetComponent<cBoxCollider>()->m_CollFunc(Object);
			}
		}
		else
		{
			if (Math::CheckCollBoxCir(Object->GetPosition(), ThisColl->GetSize(), (*iter)->GetPosition(), (*iter)->GetComponent<cCircleCollider>()->GetRadius()))
			{
				ThisColl->m_CollFunc((*iter));
				(*iter)->GetComponent<cCircleCollider>()->m_CollFunc(Object);
			}
		}
		iter++;
	}

}

void cObjectManager::CheckCircleCollision(cObject* Object)
{
	cCircleCollider* ThisColl = Object->GetComponent<cCircleCollider>();
	if (ThisColl->m_ColllistTag.size() == 0 && ThisColl->m_ColllistName.size() == 0 || ThisColl->GetEnable() == false) return;
	cCircleCollider* OtherColl;
	int Radius = ThisColl->m_Radius;
	Vector2 Pos = Object->m_Pos;
	int TagSize = ThisColl->m_ColllistTag.size();
	int NameSize = ThisColl->m_ColllistName.size();
	int i = 0;
	float x, y, Dir, Dist = 0;
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		x = Pos.x - (*iter)->m_Pos.x;
		y = Pos.y - (*iter)->m_Pos.y;
		Dir = atan(y / x);
		Dist = abs(x * cos(Dir)) + abs(y * sin(Dir));
		if (Dist <= 35)
		{
			OtherColl = (*iter)->GetComponent<cCircleCollider>();
			for (i = 0; i < NameSize; i++)
			{
				if ((*iter)->m_Name == ThisColl->m_ColllistName[i])
				{
					if (Dist <= Radius + OtherColl->m_Radius)
					{
						ThisColl->m_CollFunc((*iter));
						OtherColl->m_CollFunc(Object);
					}
					goto Next;
				}
			}
			for (i = 0; i < TagSize; i++)
			{
				if ((*iter)->m_Tag == ThisColl->m_ColllistTag[i])
				{
					if (Dist <= Radius + OtherColl->m_Radius)
					{
						ThisColl->m_CollFunc((*iter));
						OtherColl->m_CollFunc(Object);
					}
					break;
				}
			}
		}
	Next:
		iter++;
	}

}

cObject* cObjectManager::Create(string Name, Vector2 Pos, int Depth, Tag ObjectTag)
{
	cObject* Obj = new cObject();
	Obj->m_Name = Name;
	Obj->m_Pos = Pos;
	Obj->m_Depth = Depth;
	Obj->m_Tag = ObjectTag;
	Obj->Init();
	m_Objects.push_back(Obj);

	return Obj;
}

list<cObject*> cObjectManager::Find(string Name)
{
	list<cObject*> Result;

	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		if ((*iter)->m_Name == Name)
		{
			Result.push_back((*iter));
		}
		iter++;
	}

	return Result;
}

list<cObject*> cObjectManager::Find(Tag ObjectTag)
{
	list<cObject*> Result;

	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		if ((*iter)->m_Tag == ObjectTag)
		{
			Result.push_back((*iter));
		}
		iter++;
	}

	return Result;
}

void cObjectManager::With(string Name, function<void(cObject* Obj)> Func)
{
	list<cObject*> Objects = Find(Name);
	for (auto& iter = Objects.begin(); iter != Objects.end();)
	{
		Func((*iter));
		iter++;
	}
}

void cObjectManager::With(Tag ObjectTag, function<void(cObject* Obj)> Func)
{
	list<cObject*> Objects = Find(ObjectTag);
	for (auto& iter = Objects.begin(); iter != Objects.end();)
	{
		Func((*iter));
		iter++;
	}
}

void cObjectManager::With(cObject* Object, function<void(cObject* Obj)> Func)
{
	Func(Object);
}

void cObjectManager::ClearAll()
{
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
	{
		(*iter)->Destroy();
	}
	OBJECT->SetBoss(nullptr);
	OBJECT->SetPlayer(nullptr);
}