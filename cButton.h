#pragma once

class cButton : public cComponent
{
	friend class cObject;
	friend class cSystemManager;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool m_Selected;
	int m_Size;
	wstring m_Text;
	D3DCOLOR m_Color;

public:
	cButton(cObject* Object);
	~cButton();

	void SetSelected(bool Selected)
	{
		m_Selected = Selected;
	}
	bool GetSelected()
	{
		return m_Selected;
	}
	void SetString(wstring Text)
	{
		m_Text = Text;
	}
};

