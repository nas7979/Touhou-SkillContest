#pragma once
#include "cTimer.h"
#include "cComponent.h"

using Vector2 = D3DXVECTOR2;

enum ObjectTag
{
	Player,
	Enemy,
	Boss,
	Bullet,
	Item,
	None
}typedef Tag;

class cObject
{
	friend class cObjectManager;
	friend class cComponent;
private:
	string m_Name = "";
	Vector2 m_Pos = Vector2(0,0);
	float m_Rotate = 0;
	Vector2 m_Scale = Vector2(1,1);
	int m_Depth = 0;
	bool m_Destroyed = false;
	bool m_Enable = true;
	Tag m_Tag;

	list<cComponent*> m_Components;

	void Init();
	void Update();
	void Render();
	void Release();

public:

	cObject();
	~cObject();

	template <typename T>
	T* GetComponent()
	{
		for (auto iter : m_Components)
		{
			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		if (GetComponent<T>() != nullptr)
			return nullptr;

		T* Component = new T(this);
		m_Components.push_back(Component);
		Component->Init();

		return Component;
	}

	void Translate(Vector2 Pos)
	{
		m_Pos += Pos;
	}

	void Rotate(float Degree)
	{
		m_Rotate += Degree;
	}

	void Scale(Vector2 Scale)
	{
		m_Scale += Scale;
	}

	void Destroy()
	{
		m_Destroyed = true;
	}
	bool GetDestroyed()
	{
		return m_Destroyed;
	}

	Vector2 GetPosition()
	{
		return m_Pos;
	}

	void SetPosition(Vector2 Pos)
	{
		m_Pos = Pos;
	}

	float GetRotate()
	{
		return m_Rotate;
	}

	void SetRotate(float Rotate)
	{
		m_Rotate = Rotate;
	}

	Vector2 GetScale()
	{
		return m_Scale;
	}

	void SetScale(Vector2 Scale)
	{
		m_Scale = Scale;
	}

	Tag GetTag()
	{
		return m_Tag;
	}

	void SetTag(Tag ObjectTag)
	{
		m_Tag = ObjectTag;
	}

	bool GetEnable()
	{
		return m_Enable;
	}

	void SetEnable(bool Enable)
	{
		m_Enable = Enable;
	}

	string GetName()
	{
		return m_Name;
	}

	void SetName(string Name)
	{
		m_Name = Name;
	}
};

