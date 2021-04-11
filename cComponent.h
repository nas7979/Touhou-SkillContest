#pragma once

class cComponent
{
	friend class cObject;
	friend class cObjectManager;
protected:
	cObject* m_pObject;

private:
	bool m_Enable = true;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	cComponent(cObject* Object);
	virtual ~cComponent();

	void SetEnable(bool Enable)
	{
		m_Enable = Enable;
	}

	bool GetEnable()
	{
		return m_Enable;
	}

};

