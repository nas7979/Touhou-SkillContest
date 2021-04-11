#pragma once

class cCircleCollider : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:
	int m_Radius;
	vector<Tag> m_ColllistTag;
	vector<string> m_ColllistName;
	function<void(cObject* Other)> m_CollFunc = [&](cObject* Other)->void {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cCircleCollider(cObject* Object);
	~cCircleCollider();

	int GetRadius()
	{
		return m_Radius;
	}

	void SetRadius(int Radius)
	{
		m_Radius = Radius;
	}

	void AddListTag(Tag ObjectTag)
	{
		m_ColllistTag.push_back(ObjectTag);
	}

	void AddListName(string Name)
	{
		m_ColllistName.push_back(Name);
	}

	void SetCollFunc(function<void(cObject* Other)> Func)
	{
		m_CollFunc = Func;
	}
};

