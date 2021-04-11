#pragma once

class cBoxCollider : public cComponent
{
	friend class cObject;
	friend class cObjectManager;
private:
	RECT m_Size;
	vector<Tag> m_ColllistTag;
	vector<string> m_ColllistName;
	function<void(cObject* Other)> m_CollFunc = [&](cObject* Other)->void {};

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	cBoxCollider(cObject* Object);
	~cBoxCollider();

	RECT GetSize()
	{
		return m_Size;
	}

	void SetSize(RECT Size)
	{
		m_Size = Size;
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

