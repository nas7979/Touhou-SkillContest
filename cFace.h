#pragma once

class cFace : public cComponent
{
	friend class cObject;
	friend class cSystemManager;
private:

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool m_IsEnemy;
	float m_Speed;
	wstring m_Text;
	float m_TextY;
	float m_TextX;
	float m_TextSpeed;
	texture* m_Texture_SpellName[2];

public:
	cFace(cObject* Object);
	~cFace();

	void SetImage(string Image)
	{
		m_pObject->GetComponent<cRenderer>()->SetImage(IMAGE->FindImage(Image));
	}
	void SetIsEnemy(bool IsEnemy)
	{
		m_IsEnemy = IsEnemy;
	}
	bool GetIsEnemy()
	{
		return m_IsEnemy;
	}
	void SetText(wstring Text)
	{
		m_Text = Text;
	}
};

